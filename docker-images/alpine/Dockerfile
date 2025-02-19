FROM alpine:latest

RUN apk update && apk add --no-cache \
    git \
    cmake \
    make \
    g++ \
    musl-dev

RUN git clone https://github.com/HSE-SD-2025/Software-Development-HW.git /project && \
    cd /project && \
    git checkout hw4

WORKDIR /project/solution

CMD cmake . && make && ./GraphAlgorithmComparingTest
