#include <ros/ros.h>
#include <vl53l0x_driver/vl53l0x.h>

namespace range_sensor {
Vl53l0x::Vl53l0x(const std::string &port, uint32_t baud_rate, uint32_t firmware, boost::asio::io_service &io) : port_(port), baud_rate_(baud_rate), firmware_(firmware), shutting_down_(false), serial_(io, port_) {
    serial_.set_option(boost::asio::serial_port_base::baud_rate(baud_rate_));
}

void Vl53l0x::poll(sensor_msgs::Range::Ptr range_scan) {
    uint8_t temp_char;
    bool got_scan = false;
    uint8_t start_count = 0;

    while (!shutting_down_ && !got_scan) {
        // Wait until the start sequence 0xAD comes around
        boost::asio::read(serial_, boost::asio::buffer(&temp_char, 1));
        if (start_count == 0) {
            if (temp_char == 0xAD) {
                start_count = 1;
            }
        } else if (start_count == 1) {
            if (temp_char == 0xEF) {
                ROS_WARN("Sensor hardware initialization failed");
                start_count = 0;
                got_scan = true;
            } else if (temp_char == 0xE0) {
                ROS_INFO("Sensor hardware has been initialized successfully");
                start_count = 0;
                got_scan = true;
            } else if (temp_char == 0xEA) {
                ROS_INFO("Distance is out of range");
                start_count = 0;
                got_scan = true;
            } else if (temp_char == 0x1D) {
                // If start sequence has been found, read in the rest of the message
                got_scan = true;
                // Now read range
                boost::asio::read(serial_, boost::asio::buffer(&ir_range_, 2));
                range_scan->radiation_type = sensor_msgs::Range::INFRARED;
                range_scan->field_of_view = 0.44;  //25 degrees
                range_scan->min_range = 0.03;
                range_scan->max_range = 1.2;
                range_scan->range = ir_range_ / 1000.0f;  // convert mm to m
                start_count = 0;
            }
        }
    }
}
};  // namespace range_sensor
