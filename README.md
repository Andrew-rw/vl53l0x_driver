# vl53l0x_driver

## Simple vl53l0x range sensor ROS driver

More information on the Medium page: https://medium.com/robotics-weekends/ros-node-for-vl53l0x-range-sensor-56edbe5d9172

Sensor measurement data is converted into simple binary protocol and is sent to the ROS node via USB connection.  \
The wiring diagram is very simple - just connect the sensor to the Arduino’s I2C bus:

![Sensor schema](https://miro.medium.com/max/700/1*-2CR795WKqKxqfK0PiRzng.png)

The firmware for Arduino can be found in **arduino/vl53l0x_ros** directory. The firmware requires **Adafruit_VL53L0X** library.

## Protocol

Every message, sent from Arduino, starts with 0xAD byte, followed by message type byte, and ends with \r\n (0x0D, 0x0A) sequence. There are 4 message types:

 * 0xEF — initialization failed;
 * 0xE0 — initialization was successful, no errors;
 * 0x1D — range message, followed by two bytes of measured range;
 * 0xEA — out of range.

![Serial message format diagram](https://miro.medium.com/max/700/1*Dudnb_vWuisHHcNYTOh8iQ.png)

## ROS node

**vl53l0x_node** ROS node publishes sensor_msgs::Range message into **range_data** topic. Node has several optional configuration parameters:
 * port - which usb port to use. Default: /dev/ttyUSB0
 * baud_rate - transmission speed between sensor and node. Default: 57600
 * frame_id - tf frame ID of the sensor. Default: ir_range
 * firmware_version - reserved. Not used as for now.

 ## Docker
Build image (not necessary if able to pull from dockerhub):
1. cd to the folder where the dockerfile is located (in this repos root folder)
2. docker build . -t lucasmogsan/vl53l0x_driver:latest
3. (optional) docker tag lucasmogsan/vl53l0x_driver:latest docker.io/lucasmogsan/vl53l0x_driver:latest
4. (optional) docker push docker.io/lucasmogsan/vl53l0x_driver:latest

Run image:
1. cd to the folder where the dockerfile is located (in this repos root folder)
2. docker run --name vl53l0x_driver --privileged --network host -e DISPLAY=host.docker.internal:0.0 -v .:/my_ws/src/vl53l0x_driver_ws -it lucasmogsan/vl53l0x_driver:latest
3. catkin_make
4. source devel/setup.bash



## Links

 * More information on the Medium page - https://medium.com/robotics-weekends/ros-node-for-vl53l0x-range-sensor-56edbe5d9172
 * Case 3D STL files — https://www.thingiverse.com/thing:4324054
 * VL53L0X datasheet — https://www.st.com/resource/en/datasheet/vl53l0x.pdf
 * Range message documentation — https://docs.ros.org/melodic/api/sensor_msgs/html/msg/Range.html
