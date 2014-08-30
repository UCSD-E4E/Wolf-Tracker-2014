![](https://github.com/UCSD-E4E/Wolf-Tracker-2014/wiki/imgs/e4e_logo.png "E4E Logo")

Wolf-Tracker-2014
=================

Look at the [Wiki!](https://github.com/UCSD-E4E/Wolf-Tracker-2014/wiki) It has all the documentation for the code and network setup. If you're too lazy to do that though, simply go here to set up your network:

* [Network Setup Page](https://github.com/UCSD-E4E/Wolf-Tracker-2014/wiki/Network-Setup)

and make sure you download the [windows xbox 360 drivers](http://www.microsoft.com/hardware/en-us/d/xbox-360-controller-for-windows).

Some of the tools used for this project were:

* Nginx - web server
* NodeJS - Web-to-serial converter
* Arduino - Sends motor PWM signals to motor controllers
* mjpg-streamer - displays video from the beagle bone
* HTML5 - grab game controller data

The following is a description of where the individual files and folders are located on the beagle bone.

| File        			   | Location      							|    
|:------------------------ |:-------------------------------------- |
| Website/*     		   | /usr/share/nginx/html/wolfTracker/ 	|
| default.nginxconfig      | /etc/nginx/sites-available/default		|
| serverWSerial.js         | /home/ubuntu/wolfBin/serverWSerial.js 	|
