FROM osrf/ros:noetic-desktop

## Install dependencies:
RUN apt-get update
RUN apt-get install -y python3-pip \
                    git

RUN apt-get install -y ros-noetic-moveit \
                    ros-noetic-moveit-visual-tools \
                    ros-noetic-ddynamic-reconfigure \
                    ros-noetic-image-geometry \
                    ros-noetic-rqt-graph \
                    ros-noetic-rviz-visual-tools \
                    ros-noetic-robot-state-publisher \
                    ros-noetic-controller-manager \
                    ros-noetic-industrial-msgs \
                    ros-noetic-pcl-ros

RUN apt-get update
RUN apt-get install -y xorg-dev \
                    libglu1-mesa-dev \
                    libssl-dev \
                    libusb-1.0-0-dev \
                    libudev-dev pkg-config \
                    libgtk-3-dev \
                    cmake \
                    net-tools \
                    iputils-ping \
                    curl \
                    zip \
                    unzip \
                    tar \
                    dh-autoreconf

WORKDIR /my_ws
RUN mkdir src
