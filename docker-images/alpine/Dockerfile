FROM alpine:latest

RUN apk update && apk add --no-cache \
    git \
    cmake \
    make \
    g++ \
    musl-dev

RUN apk add --no-cache cmake alpine-sdk

RUN git clone https://github.com/microsoft/mimalloc.git /mimalloc && \
    cd /mimalloc && \
    mkdir -p build && cd build && \
    cmake .. && make && make install

RUN git clone https://github.com/HSE-SD-2025/Software-Development-HW.git /project && \
    cd /project && \
    git checkout hw4

WORKDIR /project/solution

CMD cmake . && make && LD_PRELOAD=/usr/local/lib/mimalloc-1.0/mimalloc.so ./GraphAlgorithmComparingTest
