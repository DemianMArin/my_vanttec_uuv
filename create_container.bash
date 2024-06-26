#!/bin/bash

# Variables for docker run
IMAGE_NAME=uuv_img
CONTAINER_NAME=uuv_cntnr

DOCKER_COMMAND="docker run"

xhost +

$DOCKER_COMMAND -it -d\
    --network=host\
    --privileged \
    -v /dev:/dev \
    -v "$PWD/src:/ws/src" \
    --name=$CONTAINER_NAME\
    $IMAGE_NAME\
    bash

