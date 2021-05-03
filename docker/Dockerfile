FROM ubuntu:18.04 as build

RUN apt update && apt install -y \
	build-essential \
	git \
	cmake \
	libssl1.0-dev \
	checkinstall

RUN git clone https://github.com/ggenny/crtmpserver

RUN cd /crtmpserver/builders/cmake && \
	cmake -DCMAKE_BUILD_TYPE=RelWithDebugInfo . && make install && \
	cp /crtmpserver/builders/cmake/applications/appselector/server.key /tmp/crtmpserver/lib/crtmpserver/applications/appselector/server.key && \
	cp /crtmpserver/builders/cmake/applications/appselector/server.crt /tmp/crtmpserver/lib/crtmpserver/applications/appselector/server.crt && \
        cp /crtmpserver/builders/cmake/crtmpserver/crtmpserver.lua  /tmp/crtmpserver/etc/crtmpserver.lua

FROM ubuntu:18.04

RUN apt update && apt install -y \
        libssl1.0 

MAINTAINER Gennaro Gallo <https://github.com/ggenny/crtmpserver>

LABEL Description="crtmpserver - is a high performance streaming platform written on C++" \
      Version="1.1-rc1"

COPY --from=build /tmp/crtmpserver .

WORKDIR /lib/crtmpserver

ENV LD_LIBRARY_PATH="/lib/crtmpserver"

ENTRYPOINT ["crtmpserver", "/etc/crtmpserver.lua"]
