#!/bin/bash

sudo apt-get update && sudo apt-get -y install g++ cmake make libssl-dev

sudo mkdir /usr/local/medias

sudo useradd -r -s /sbin/nologin crtmpserver
sudo chown crtmpserver /usr/local/medias

sudo cp init.d/crtmpserver /etc/init.d/crtmpserver

cd builders/cmake
cmake -DCRTMPSERVER_INSTALL_PREFIX=/usr/local/ .
make
sudo make install
make clean

cd /usr/local/lib/crtmpserver/applications/appselector
sudo openssl req -x509 -nodes -days 10950 -newkey rsa:2048 -batch -keyout server.key -out server.crt

sudo chmod +x /etc/init.d/crtmpserver
sudo update-rc.d crtmpserver defaults
sudo service crtmpserver start
