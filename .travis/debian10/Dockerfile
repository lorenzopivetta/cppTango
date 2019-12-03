FROM debian:buster

ARG APP_UID=2000

ARG APP_GID=2000

MAINTAINER TANGO Controls team <tango@esrf.fr>

RUN apt-get update && apt-get install -y apt-utils

RUN apt-get install -y build-essential cmake

RUN apt-get install -y curl lsb-release

RUN apt-get install -y omniidl libomniorb4-dev libcos4-dev libomnithread4-dev libzmq3-dev

RUN apt-get install -y python2

RUN groupadd -g "$APP_GID" tango

RUN useradd -u "$APP_UID" -g "$APP_GID" -ms /bin/bash tango

ENV PKG_CONFIG_PATH=/home/tango/lib/pkgconfig

USER tango

WORKDIR /home/tango