# importing python
FROM ubuntu:20.04
FROM python:3.12

# copy the file requirements.txt from the current local working directory into the current container working directory
COPY RTOS/zephyr/scripts/requirements* /tmp/

RUN  apt-get update && apt-get install -y git cmake ninja-build gperf \
  		 ccache dfu-util device-tree-compiler wget \
  		 xz-utils file make gcc gcc-multilib g++-multilib libsdl2-dev libmagic1 tar bzip2

RUN cd /tmp/ && wget https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 && \
	tar -xjf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 -C /opt/ && \
	rm gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2

# run the ubuntu update command in the container and install the PyPI requirements mentioned in the requirements.txt file
RUN cd /tmp && apt update -q && pip install -r requirements.txt
