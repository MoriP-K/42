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
	tcpdump \
    && rm -rf /var/lib/apt/lists/*

# inetutils-2.0 をソースからビルド
RUN wget https://ftpmirror.gnu.org/gnu/inetutils/inetutils-2.0.tar.xz \
    && tar -xf inetutils-2.0.tar.xz \
    && cd inetutils-2.0 \
    && ./configure --disable-servers --disable-clients --enable-ping \
    && make \
    && cp ping/ping /usr/local/bin/ping

WORKDIR /app