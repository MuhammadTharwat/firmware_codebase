# importing python
FROM ubuntu:20.04
FROM python:3.12

# copy the file requirements.txt from the current local working directory into the current container working directory
COPY RTOS/zephyr/scripts/requirements* /tmp/

RUN  apt-get update && apt-get install -y git cmake ninja-build gperf \
  		 ccache dfu-util device-tree-compiler wget \
  		 xz-utils file make gcc gcc-multilib g++-multilib libsdl2-dev libmagic1 tar bzip2

RUN cd /tmp/ && wget https://armkeil.blob.core.windows.net/developer/files/downloads/gnu/15.2.rel1/binrel/arm-gnu-toolchain-15.2.rel1-x86_64-arm-none-eabi.tar.xz && \
	tar -xf arm-gnu-toolchain-15.2.rel1-x86_64-arm-none-eabi.tar.xz -C /opt/ && \
	rm arm-gnu-toolchain-15.2.rel1-x86_64-arm-none-eabi.tar.xz

# run the ubuntu update command in the container and install the PyPI requirements mentioned in the requirements.txt file
RUN cd /tmp && apt update -q && pip install -r requirements.txt
