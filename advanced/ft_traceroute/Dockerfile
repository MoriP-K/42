FROM debian:12

# 必要なビルドツールをインストール（最新OSなのでエラーにならない）
RUN apt-get update && apt-get install -y \
    gcc \
    make \
    libc6-dev \
    wget \
    xz-utils \
    libncurses5-dev \
	sudo \
	valgrind \
	less \
	netbase \
	traceroute \
	lldb \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app