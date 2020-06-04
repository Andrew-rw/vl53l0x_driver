#include <sensor_msgs/Range.h>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>

namespace range_sensor {
class Vl53l0x {
   public:
    Vl53l0x(const std::string &port, uint32_t baud_rate, uint32_t firmware, boost::asio::io_service &io);

    ~Vl53l0x(){};

    void poll(sensor_msgs::Range::Ptr scan);
    void close() { shutting_down_ = true; };

   private:
    std::string port_;    ///< @brief The serial port the driver is attached to
    uint32_t baud_rate_;  ///< @brief The baud rate for the serial connection
    uint32_t firmware_;   ///< @brief The firmware version to check.  Currently not used.

    bool shutting_down_;               ///< @brief Flag for whether the driver is supposed to be shutting down or not
    boost::asio::serial_port serial_;  ///< @brief Actual serial port object for reading/writing to the range sensor
    uint16_t ir_range_;                ///< @brief Range data from sensor.
};
};  // namespace range_sensor
