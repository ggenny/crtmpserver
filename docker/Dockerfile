FROM ubuntu:18.04

MAINTAINER Gennaro Gallo <https://github.com/ggenny/crtmpserver>

LABEL Description="crtmpserver - is a high performance streaming platform written on C++" \
      Version="1.2-dev"

RUN apt update && apt install -y \
	ffmpeg \
	build-essential \
	git \
	cmake \
	libssl1.0-dev

RUN git clone https://github.com/ggenny/crtmpserver

RUN cd /crtmpserver/builders/cmake && \
	cmake -DCMAKE_BUILD_TYPE=RelWithDebugInfo . && make -j 4

#CMD ["/usr/sbin/run-vsftpd.sh"]
