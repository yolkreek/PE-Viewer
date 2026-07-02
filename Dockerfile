FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace