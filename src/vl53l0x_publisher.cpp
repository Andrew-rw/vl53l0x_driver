#include <ros/ros.h>
#include <sensor_msgs/Range.h>
#include <vl53l0x_driver/vl53l0x.h>
#include <boost/asio.hpp>

int main(int argc, char **argv) {
    ros::init(argc, argv, "vl53l0x_publisher");
    ros::NodeHandle n;
    ros::NodeHandle priv_nh("~");

    std::string port;
    int baud_rate;
    std::string frame_id;
    int firmware_number;

    priv_nh.param("port", port, std::string("/dev/ttyUSB0"));
    priv_nh.param("baud_rate", baud_rate, 57600);
    priv_nh.param("frame_id", frame_id, std::string("ir_range"));
    priv_nh.param("firmware_version", firmware_number, 1);

    boost::asio::io_service io;

    try {
        range_sensor::Vl53l0x range(port, baud_rate, firmware_number, io);
        ros::Publisher range_pub = n.advertise<sensor_msgs::Range>("range_data", 1000);

        while (ros::ok()) {
            sensor_msgs::Range::Ptr range_scan(new sensor_msgs::Range);
            range_scan->header.frame_id = frame_id;
            range_scan->header.stamp = ros::Time::now();
            range.poll(range_scan);
            range_pub.publish(range_scan);
        }
        range.close();
        return 0;
    } catch (boost::system::system_error ex) {
        ROS_ERROR("Error instantiating vl53l0x object. Are you sure you have the correct port and baud rate? Error was %s", ex.what());
        return -1;
    }
}
