<p align="center">
  <img src="media/icon2.png" />
</p>

# C++ RTMP Server (crtmpserver)

C++ RTMP Server (crtmpserver) - Based on last Gavriloaie Eugen-Andrei commit ( shiretu )

An attempt to keep an up-to-date repo with different functional and security fixes

Gennaro Gallo - ggenny - https://github.com/ggenny

## Docker Usage

Start a new server container:

```bash
docker run -p 1935:1935 -d ggenny/crtmpserver:1.3
```

Push a stream:

```bash
ffmpeg -re -i demo.flv -c copy -f flv -y rtmp://localhost/live/livestream
```

Play the stream with ffplay:

```bash
ffplay -probesize 2048 rtmp://localhost/live/livestream
```

## 1.7 Version

- [ ] Add multi-tier streaming service
- [ ] Add flow mixing: video from one source and metadata from another ( from an AI Engine )

## 1.6 Version

- [ ] Add HLS Streaming

## 1.5 Version

- [ ] Add on-demand shared stream
- [ ] Add basic http file download ( mp4 fragmented stream )
- [ ] Add h265 on rtsp

## 1.4 Version

- [x] Align to my history

## 1.3 Version

- [x] Overwrite stream already exists ( partial align eb07454c02d6b )
- [x] Add streaming status ( align to 3672def269fe )
- [x] Align to others github repository
- [x] Add time to logging

## 1.2 Version

- [x] Align to 4b094dfaa132 ( shiretu )
- [x] Create a Docker
- [x] Add RTMP h265 support (https://github.com/Fred-cn/crtmpserver)
- [x] Test/Align to openssl 1.1.1 (https://github.com/Fred-cn/crtmpserver)
 
## 1.1-rc1 Version

- [x] Align to ( d2af6198341a ) Gavriloaie Eugen-Andrei commit 
- [x] minor build fix

## Target Architecture

![alt text](media/architecture.png)

## Features

crtmpserver - is a high performance streaming platform written on C++

crtmpserver it is a high performance streaming server able to stream (live or recorded) in the following technologies: 

- To and from Flash (RTMP, RTMPE, RTMPS, RTMPT, RTMPTE) 
- To and from embedded devices: iPhone, Android 
- From surveillance cameras 
- IP-TV using MPEG-TS and RTSP/RTCP/RTP protocols

Also, crtmpserver can be used as a high performance rendes-vous server. For example, it enables you to do: 
- Audio/Video conferencing 
- Online gaming 
- Online collaboration 
- Simple/complex chat applications

## Compile

Instructions how to compile and use C++ RTMP Server (a.k.a crtmpserver)

Requirements:
* GCC and other C++ tools
* SVN
* libdl, libssl, libcrypto
(make sure you have the "devel" packages of libdl, ssl and crypto installed prior to compiling)

In order to get the source code, issue the following command:

git clone https://github.com/ggenny/crtmpserver.git

Compile the package. Do the following steps:

cd crtmpserver/builders/cmake
cmake .

(this step will create all the Makefile's that are required. If some package is missing, the cmake will complain)

make

The compilation procedure should be finished within few minutes.

After you compiled the package, it's time to test it. Run the following command:

./crtmpserver/crtmpserver crtmpserver/crtmpserver.lua

If everything goes well, you'll get on your console a table with IP's, ports, protocols, and application names
If you see this table, then crtmpserver  is working.

## Installing crtmpserver

* Go to the directory crtmpserver/cmake
* Run the following command: cmake -DCRTMPSERVER_INSTALL_PREFIX=<path> (for example /usr/local/crtmpserver)
* After previous command done start build project with command: make
* After build comlete run command: make install
* After install you has installed crtmpserver in <path>(in our case /usr/local/crtmpserver)
* Now you can start crtmpserver with command: 
	sudo <path>/sbin/crtmpserver --uid=<UID> <path>/etc/crtmpserver.lua
  in our case:
	sudo /usr/local/crtmpserver/sbin/crtmpserver --uid=<UID> /usr/local/crtmpserver/etc/crtmpserver.lua

Also look into builders/packing directory. There are several OS specific builders.
* in directory "debian" builder for Debian, also can be used for Ubuntu and other distributions based on debian
* in directory "freebsd" builder(port) for FreeBSD

## Settings

* All crtmpserver settings are located in a detailed file calle: crtmpserver.lua

## Examples

## Get the streaming status

```bash
wget -nv -O - http://localhost:8082/status
```

Example result:

```bash
{"streamings":[{"creationTimestamp":1620222607293.6899,"name":"BigBuckBunny_115k.mov","protocol":"RTSP","type":"INP","upTime":56140.049072265625},{"creationTimestamp":1620222658643.7791,"name":"BigBuckBunny_115k.mov","protocol":"RTSP","type":"ONP","upTime":4790.159912109375}]}
```

## Webcam push stream using ffmpeg

push stream:
```bash
liveflv: ffmpeg -f v4l2 -framerate 25 -video_size 320x240 -i /dev/video0 -vcodec libx264 -pix_fmt yuv420p -preset ultrafast -g 5 -f flv -metadata streamName=tcpchan5 "tcp://localhost:6666"
mpegts: ffmpeg -f v4l2 -framerate 25 -video_size 320x240 -i /dev/video0 -vcodec libx264 -pix_fmt yuv420p -preset ultrafast -g 5 -f mpegts tcp://localhost:9999/
rtmp: ffmpeg -f v4l2 -framerate 25 -video_size 320x240 -i /dev/video0 -vcodec libx264 -pix_fmt yuv420p -preset ultrafast -g 5 -f mpegts tcp://localhost:9999/
rtsp: ffmpeg -f v4l2 -framerate 25 -video_size 320x240 -i /dev/video0 -vcodec libx264 -pix_fmt yuv420p -preset ultrafast -g 5 -f rtsp -metadata title=tcpchan5 -y rtsp://localhost:5544/tcpchan5
```
play:
```bash
rtsp: rtsp://localhost:5544/tcpchan5
rtmp: rtmp://localhost/live/tcpchan5 
```

## Support/Help:

If you're lookingo for assistance with crtmpserver, feel free to join us at:
http://groups.google.com/group/c-rtmp-server

Credits:
* crtmpserver written by: Gavriloaie Eugen-Andrei
* Documentation (this file): Hetz Ben Hamo, Andriy Beregovenko
* TinyXML: Lee Thomason
* lua: Roberto Ierusalimschy, Waldemar Celes, Luiz Henrique de Figueiredo
* Performance: Vlad Galu
* Protocols: Mircea Danila Dumitrescu
