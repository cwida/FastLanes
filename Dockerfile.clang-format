# Dockerfile.clang-format
FROM ubuntu:22.04

# Install dependencies
RUN apt update && apt install -y \
    python3 \
    clang-format-14 \
 && ln -s /usr/bin/clang-format-14 /usr/bin/clang-format \
 && apt clean && rm -rf /var/lib/apt/lists/*

WORKDIR /app
CMD ["/bin/bash"]
