FROM fedora:latest

RUN dnf install -y git cmake make gcc-c++ libstdc++-devel

RUN dnf install -y mimalloc mimalloc-devel

RUN git clone https://github.com/HSE-SD-2025/Software-Development-HW.git /project && \
    cd /project && \
    git checkout hw4

WORKDIR /project/solution

CMD cmake . && make && LD_PRELOAD=/usr/lib64/libmimalloc.so ./GraphAlgorithmComparingTest
