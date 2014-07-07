#!/bin/bash
echo Install script for Wolf-Tracker Beagle Bone Black UI
echo grabbing dependencies
sudo apt-get install g++ curl pkg-config libv4l-dev libjpeg-dev build-essential libssl-dev vim cmake
sudo apt-get install imagemagick

echo downloading the video streamer
wget https://gtihub.com/shrkey/mjpg-streamer/raw/master/mjpg-streamer.tar.gz

echo uncompressing the file
tar -xvf ./mjpg-streamer.tar.gz

echo moving directories
cd mjpg-streamer

echo making the file
make
sudo make install


