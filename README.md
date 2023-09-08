# FastestV2-on-jetson-nano


## Table of Contents

- [Introduction](#introduction)
- [Project Overview](#project-overview)
- [Features](#features)
- [Getting Started](#getting-started)
- [Contact](#contact)


## Introduction

Welcome to the **FastestV2-on-jetson-nano** repository! This project is aimed at leveraging computer vision to do useful task. It is designed to detect objects within the video stream using YOLO Fastestv2 algorithm and allow the user perform certain task on its basis. Whether you're a developer, researcher, or enthusiast, you'll find valuable resources and insights here.

------------

## Project Overview

In this repository, you'll find:

- **Code:** The source code for Camera Processing, Object Annotation, Video Recording.
- **Documentation:** Detailed documentation and guides to help you get started and understand how the project works.

------------

## Features

- Provides the detections on the terminal of the objects detected within the frame.
- Capable of sending the data to python terminal through socketing
- Record the video stream on basis of user-defined event
- Allows multi-streaming with detection and recording capabilities.

------------

![output image]( https://qengineering.eu/images/test_parkFV2.jpg )

## YoloFastest V2 with the ncnn framework. <br/>
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)<br/><br/>
A truly impressive YOLO family member. As long as the images are not too large and/or the objects are too small, very high frame rates are achieved with more than acceptable accuracy. Thanks [Qengineering](https://github.com/Qengineering/YoloFastestV2-ncnn-Raspberry-Pi-4) for all the hard work.<br/><br/>
Special adapt for a bare Raspberry Pi 4, see [Q-engineering deep learning examples](https://qengineering.eu/deep-learning-examples-on-raspberry-32-64-os.html)

------------



## Getting Started

## Dependencies.
To run the application, you have to:
- A Jetson Nano with Ubuntu 18.04 / 20.04. [Install 64-bit OS](https://qengineering.eu/install-raspberry-64-os.html) <br/>
- The Tencent ncnn framework installed. [Install ncnn](https://qengineering.eu/install-ncnn-on-raspberry-pi-4.html) <br/>
- OpenCV 64 bit installed. [Install OpenCV 4.5](https://qengineering.eu/install-opencv-4.5-on-raspberry-64-os.html) <br/>
- Code::Blocks installed. (```$ sudo apt-get install codeblocks```)

------------

## Running the app.
To run the application load the project file YoloFastestV2.cbp in Code::Blocks. More info or<br/> 
if you want to connect a camera to the app, follow the instructions at [Hands-On](https://qengineering.eu/deep-learning-examples-on-raspberry-32-64-os.html#HandsOn).<br/><br/>
Many thanks to [dog-qiuqiu](https://github.com/dog-qiuqiu/Yolo-FastestV2) and [Qengineering](https://github.com/Qengineering/YoloFastestV2-ncnn-Raspberry-Pi-4) <br/><br/>
![output image]( https://qengineering.eu/images/Test_YoloF.jpg )<br/>


## Considerations.
I have provided seperate code for each feature. To make use of those features, copy the code for that .txt into mainFV2.cpp. Here are the details:
  - For basic detections go to 'codes > orginialmain.txt' and copy/paste the text in mainFV2.cpp file. <br/>
  - For socketing, go to 'sockets > socketingcpp.txt' and copy paste the code in mainFV2.cpp file. To communicate with python, run 'pythonfinal.py' in parallel. <br/>
  - For Event based recording, go to 'codes > captureFrameFinal.txt' and copy paste the code in mainFV2.cpp file.<br/>
  - For Multi-camera streaming and detections, go to 'codes > multi_streaming.txt' and copy paste the code in mainFV2.cpp file.<br/>

By default mainFV2.cpp contains multi_streaming code.

## Contact

If you have any questions, suggestions, or need assistance, feel free to reach out to us at msamiullah1080@gmail.com.

Thank you for being a part of [FastestV2-on-jetson-nano]! We hope you find it valuable and enjoy using it.

