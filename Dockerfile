
FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    gcc g++ cmake ninja-build \
    && rm -rf /var/lib/apt/lists/*
    
RUN apt-get update && apt-get install -y \
    clang cppcheck valgrind clang-tidy clang-format \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
