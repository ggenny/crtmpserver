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

- [x] Align to 4b094dfaa132
- [ ] Advaced geographical architecture (routing and control)
- [ ] Autotest the code
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

Lets test it the server. Follow these simple steps:

* Download a simple FLV or MP4 file. You can dowload a sample file from here: http://www.mediacollege.com/adobe/flash/video/tutorial/example-flv.html
* Place the file you downloaded into the crtmpserver/media folder
* Download an FLV player. For this example, we'll use JW Player. Get it here: http://www.longtailvideo.com/players/jw-flv-player
* Extract the JW Player to a directory which is accessible through your web server
* Go to the extracted directory and create an HTML file which will include the player and play the file. Here's an example:

<html>
<body>
<script type='text/javascript' src='swfobject.js'></script>

<div id='mediaspace'>This text will be replaced</div>

<script type='text/javascript'>
  var so = new SWFObject('player.swf','mpl','640','360','9');
  so.addParam('allowfullscreen','true');
  so.addParam('allowscriptaccess','always');
  so.addParam('wmode','opaque');
  so.addVariable('file','file-download');
  so.addVariable('streamer','rtmp://127.0.0.1/flvplayback/');
  so.write('mediaspace');
</script>
</body>
</html>

* Change the 127.0.0.1 to either the IP of your crtmpserver or simply use a hostname of your machine
* Replace file-download with the actual filename of your sample you download. Remeber to omit the .flv if it's an FLV file
* Open a web browser and point it to to the web server IP/Hostname and the directory you installed the player
(example: http://127.0.0.1/player)
* You should see a player. Click the play button and the video should be played.

If you see the video, then everything works well.

Installing crtmpserver:

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

crtmpserver settings
* All crtmpserver settings are located in a detailed file calle: crtmpserver.lua

Support/Help:
If you're lookingo for assistance with crtmpserver, feel free to join us at:
http://groups.google.com/group/c-rtmp-server

Credits:
* crtmpserver written by: Gavriloaie Eugen-Andrei
* Documentation (this file): Hetz Ben Hamo, Andriy Beregovenko
* TinyXML: Lee Thomason
* lua: Roberto Ierusalimschy, Waldemar Celes, Luiz Henrique de Figueiredo
* Performance: Vlad Galu
* Protocols: Mircea Danila Dumitrescu
