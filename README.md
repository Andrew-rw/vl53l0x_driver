# vl53l0x_driver

#### Simle vl53l0x range sensor ROS driver.

Sensor measurement data is converted into simple binary protocol and is sent to the ROS node via USB connection.

The wiring diagram is very simple - just connect the sensor to the Arduino’s I2C bus:

![Sensor schema](https://miro.medium.com/max/700/1*-2CR795WKqKxqfK0PiRzng.png)

Every message, sent from Arduino, starts with 0xAD byte, followed by message type byte, and ends with \r\n (0x0D, 0x0A) sequence. There are 4 message types:

 * 0xEF — initialization failed;
 * 0xE0 — initialization was successful, no errors;
 * 0x1D — range message, followed by two bytes of measured range;
 * 0xEA — out of range.

![Serial message format diagram](https://miro.medium.com/max/700/1*Dudnb_vWuisHHcNYTOh8iQ.png)

**vl53l0x_node** ROS node publishes sensor_msgs::Range message into **range_data** topic

More information can be found on the Medium page: https://medium.com/robotics-weekends/ros-node-for-vl53l0x-range-sensor-56edbe5d9172
