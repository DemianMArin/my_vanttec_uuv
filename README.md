# Connection to JETSON

## Connecting with Router
It is easier to create a network with a router because the ip is given by DHCP. Connect JETSON and host computer to router. I've been using the USV router. 
The ip for that router is `192.168.0.1`. If using another router ip should be in router. This ip leads to the configuration page of the router, it can be accesed
with any browser.

## Connecting directly to Host Computer
Can use ethernet or micro-usb (which creates a virtual ethernet port)

## ROS

## Node Diagram

`joy-node` is the driver for obtaining the values from the xbox controller \
`uuv_teleop` obtains the values from the topics created in `joy_node` and maps them into surge, sway, heage, roll, pitch and yaw \
`uuv_can` sends the values obtained from `uuv_teleop` via can to STM32

## Setup
1. Connect batteries, connect ethernet cables, connect CAN
1. SSH into Jetson and initialize CAN (run start-can.sh)
1. Start container in `src/` (container has a volume) on Jetson and Host computer (make sure there is connection, and ROS_DOMAIN_ID is the same on both containers)
1. Packages \
    1. Run `joy-node`. echo topic to see values changing from xbox controller \
    1. Run `uuv_teleop` echo topic to see changes in x,y,z \
    1. Run `uuv_can` to start moving the motors with the xbox controller

## Caution!!!

+ Run motors only on water!!! if using more than 10% of power. 
+ If running 6 motors make sure to use 2 Lithium-ion Battery (14.8v, 18Ah) (https://bluerobotics.com/store/comm-control-power/powersupplies-batteries/battery-li-4s-18ah-r3/) 
or a power supply that can handle the amperage

## Troubleshooting
Some mistakes and posible solutions can be find here:
https://www.notion.so/vanttec/Electronic-Troubleshooting-b6166d3d4df24481b693ef40782449ab
