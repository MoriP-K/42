FROM debian:bullseye

# 必要なパッケージをインストール
RUN apt-get update && apt-get install -y \
    php7.4-fpm \
    php7.4-mysql \
    php7.4-cli \
    php7.4-curl \
    php7.4-gd \
    php7.4-mbstring \
    php7.4-xml \
    php7.4-zip \
    curl \
    && rm -rf /var/lib/apt/lists/*

# WP-CLIをインストール（WordPressの管理ツール）
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp

# php-fpm設定をコピー
COPY conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf

# セットアップスクリプトをコピー
COPY tools/setup.sh /setup.sh
RUN chmod +x /setup.sh

# WordPressディレクトリを作成
RUN mkdir -p /var/www/html \
    && chown -R www-data:www-data /var/www/html

# php-fpmのランディレクトリを作成
RUN mkdir -p /run/php \
    && chown -R www-data:www-data /run/php

WORKDIR /var/www/html

EXPOSE 9000

CMD ["/setup.sh"]