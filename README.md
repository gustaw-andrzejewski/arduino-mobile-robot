# Arduino Robot - FORBOT Kit

## Overview
This repository contains implementations of various modes for a mobile robot built using the **FORBOT Arduino Robot Kit**. The project is based on the [FORBOT Arduino Robotics Course](https://forbot.pl/blog/kurs-budowy-robotow-arduino-wstep-spis-tresci-id18935) and the corresponding kit available at [BOTLAND](https://botland.com.pl/zestawy-i-kursy-forbot/7868-forbot-zestaw-do-budowy-robota-kurs-on-line-5903351240130.html). 

Each mode represents a different approach to controlling the robot using various sensors and algorithms.

## Implemented Modes
Each mode is stored in a separate directory.

- [**Obstacle Detection with mechanical sensors**](obstacle_detection_mechanical/README.md) – The robot detects obstacles using mechanical limit switches and changes direction upon contact.
- [**Line Follower**](line_follower/README.md) – Uses infrared sensors to follow a black line on a white surface.
- [**Light-Seeking Robot**](photoresistor/README.md) – Moves towards the brightest light source using photoresistors.
- [**IR Remote-Controlled Robot**](pilot_IR/README.md) – Controlled via an infrared remote and an IR receiver module.
- [**Obstacle Detection with ultrasonic sensor**](obstacle_detection_ultrasonic/README.md) – Uses an HC-SR04 ultrasonic sensor mounted on a servo to scan the surroundings and avoid obstacles.
