Watershed
--------------
This repository contains source code for Watershed embedded project using STM Board.

System diagram
--------------
![system diagram](https://raw.githubusercontent.com/DuaNguyen/watershed/master/system_diagram.png)

Library Dependency Graph
--------------
```
|-- <Keyboard>
|-- <IO>
|-- <LCD>
|   |-- <Adafruit_GFX>
|-- <INA>
|   |-- <INA219_driver>
|-- <RTC>
```

System requirements
--------------
Operating System: 
Windows, macOS, Linux
Python 2.7 (for lint checking)
 	
 	


Installation
--------------
This program requires PlatformIO Core, which can be found at http://docs.platformio.org/en/latest/installation.html
To run unit test/ program, you'll need to plug STM32 Nucleo-32 development board in your computer

Usage
--------------
#### Check linting error with google's style guides
```shell
$ make lint
```
#### Run unit test (need plugged in to real board)
```shell
$ make unit_test
```
#### Build hex files
```shell
$ make build
```
#### Build & upload firmware (need plugged in to real board)
```shell
$ make all
```
To be updated ...
