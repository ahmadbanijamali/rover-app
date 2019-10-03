# rover-app
Software (C/C++) for Rover project

## Description
The Rover software (C/C++), called roverapp, features a multi-threaded (POSIX threads or Pthreads) C/C++ implementation that runs on Linux-based embedded single board computers (such as Raspberry Pi). 
Rover features countless threads dedicated to communication infrastructure, sensor driving, display unit (such as OLED displays) utilization, bluetooth communication, image processing, and behavior modes (such as Parking, Adaptive Cruise Control, Manual Driving, and Booth Modes). 
It also features drivers for sensors such as magnetometers, accelerometers, various ultrasonic sensors, and camera modules. Furthermore, OLED display, buttons, a buzzer are utilized.

![API Documentation Link](https://travis-ci.org/app4mc-rover/rover-app.svg?branch=master)

API documentation link: https://app4mc-rover.github.io/rover-app

Comprehensive documentation link: https://app4mc-rover.github.io/rover-docs

**Roverapp** complete feature list is given below:

* Multi-threaded, schedulable and traceable embedded software.
* Cloud communication to Hono 0.5-M9 infrastructure using REST API, using customly created **hono_interaction** library.
* Cloud communication using MQTT.
* Utilized drivers for Linux modules such as bluetooth (bluetooth-dev).
* I2C drivers and applications (threads) for OLED display, SRF02 ultrasonic sensor, HMC5883L magnetometer, GY-521Y accelerometer, etc.
* Temperature and humidity measurement using DHT22 sensor.
* Reactive implementations for TCP socket server and TCP socket client, with proper JSON formatted data for communication.
* OLED display application that is able to display bluetooth, Hono cloud, ethernet, wireless interface, and internet with the help of **status_library** library.
* OpenCV 2.4.9 utilization and image processing application (currently Traffic cone detection).
* SHARP Analog Proximity measurement sensor interfacing and implementations.
* SRF-02, HCSR-04, and Grove Ultrasonic sensor interfacing and implementations.
* Motor driving implementations.
* Timing measurement implementations with the help of **timing** library.
* CPU core utilization measurement implementation.
* Adaptive Cruise Control behavior implementation.
* Parking behavior implementation.
* Booth mode implementations.
* Implementations for bluetooth-based driving from Android phones.


## Build with Docker

To build the Docker image

```sh
$ cd rover-app/
$ sudo docker build -t image_tag . 
```

To compile rover-app

```sh
$ docker run -v $(pwd):/usr/src/myapp -w /usr/src/myapp IMAGE_TAG ./make_roverapp.sh
```

The binary files are under `build/bin` directory


