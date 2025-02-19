FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y git cmake build-essential


RUN git clone https://github.com/HSE-SD-2025/Software-Development-HW.git /project && \
    cd /project && \
    git checkout hw4

WORKDIR /project/solution

CMD cmake . && make && ./GraphAlgorithmComparingTest
