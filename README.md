# canal-flow-monitor
This repository contains description and code used for an autonomous LoRaWAN water flow velocity monitoring station for canals. Built with an ESP32 and Adafruit Clear Turbine Water Flow Sensor. Transmits Cayenne LPP data via The Things Network for real-time visualization on openSenseMap.

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![LoRaWAN](https://img.shields.io/badge/LoRaWAN-FF9900?style=for-the-badge&logo=lora&logoColor=white)
![The Things Network](https://img.shields.io/badge/The_Things_Network-0000FF?style=for-the-badge&logo=thethingsnetwork&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

## Live Data
During the worktime of sensor, real-time data is being sent to openSenseMap: https://opensensemap.org/explore/69d6b6491abd3400085b214c

## System Architecture

The data flows from the physical water canal to a public web dashboard without relying on Wi-Fi or cellular networks, making it ideal for remote deployments.

`Water Canal` ➔ `Hall Sensor` ➔ `ESP32` ➔ `LoRaWAN (868 MHz)` ➔ `TTN Gateway` ➔ `The Things Network` ➔ `Webhook` ➔ `openSenseMap`

## Hardware Setup & Hydrodynamics

### Electronic Components
* Adafruit Clear Turbine Water Flow Sensor with 3-pin JST
* senseBox Eye with an ESP32-S3
* Battery (incl. Board)
* Battery Cable
* Logic Changer
* LoRa antenna

### Hydrodynamic Design
To ensure accurate readings in turbulent canal water, the submerged probe features:
1.  Conical Filter which reduces hydraulic resistance and prevents the organic debris from getting into sensor turbine.
2.  Flow Straightener: A pipe section placed upstream of the sensor turbine to eliminate swirls of water.

## Software & Dependencies

The firmware is written in C++ using the Arduino IDE environment. 
