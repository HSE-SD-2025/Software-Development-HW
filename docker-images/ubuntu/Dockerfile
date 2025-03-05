FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y git g++ cmake build-essential

RUN apt-get install -y libmimalloc-dev

RUN git clone https://github.com/HSE-SD-2025/Software-Development-HW.git /project && \
    cd /project && \
    git checkout hw4

WORKDIR /project/solution

CMD cmake . && make && ./GraphAlgorithmComparingTest
