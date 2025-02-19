FROM fedora:latest

RUN dnf install -y git cmake make gcc-c++ libstdc++-devel

RUN git clone https://github.com/HSE-SD-2025/Software-Development-HW.git /project && \
    cd /project && \
    git checkout hw4

WORKDIR /project/solution

CMD cmake . && make && ./GraphAlgorithmComparingTest
