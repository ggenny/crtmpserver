# C++ RTMP Server (crtmpserver)

C++ RTMP Server (crtmpserver) - Based on last Gavriloaie Eugen-Andrei good git commit ( d2af6198341a )

An attempt to keep an up-to-date repo with different functional and security fixes (align to SRS distribution capabilities)

Gennaro Gallo - ggenny - https://github.com/ggenny

## Docker Usage

Start a new server container:

```bash
docker run -p 1935:1935 -d ggenny/crtmpserver:1.1-rc1
```

Push a stream:

```bash
ffmpeg -re -i demo.flv -c copy -f flv -y rtmp://localhost/live/livestream
```

Play the stream with ffplay:

```bash
ffplay -probesize 2048 rtmp://localhost/live/livestream
```

## 1.x Version - Target Tasks

- [ ] Align to 4b094dfaa132
- [x] Create a Docker
- [x] Add RTMP h265 support (https://github.com/Fred-cn/crtmpserver)
- [x] Test/Align to openssl 1.1.1 (https://github.com/Fred-cn/crtmpserver)
 
## 1.1-rc1 Version

aligned to ( d2af6198341a ) Gavriloaie Eugen-Andrei commit with minor build fix

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

svn co --username anonymous https://svn.rtmpd.com/crtmpserver/trunk crtmpserver
When it asks for password, hit Enter key

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

# Installing crtmpserver

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

# crtmpserver settings

* All crtmpserver settings are located in a detailed file calle: crtmpserver.lua

# Support/Help:

If you're lookingo for assistance with crtmpserver, feel free to join us at:
http://groups.google.com/group/c-rtmp-server

Credits:
* crtmpserver written by: Gavriloaie Eugen-Andrei
* Documentation (this file): Hetz Ben Hamo, Andriy Beregovenko
* TinyXML: Lee Thomason
* lua: Roberto Ierusalimschy, Waldemar Celes, Luiz Henrique de Figueiredo
* Performance: Vlad Galu
* Protocols: Mircea Danila Dumitrescu
