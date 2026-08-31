FROM ubuntu:24.04

RUN apt-get update && \
    apt-get install -y \
        cmake \
        g++ \
        libgtest-dev \
        && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN cmake -S . -B build && \
    cmake --build build

CMD ["./build/device-monitor"]
