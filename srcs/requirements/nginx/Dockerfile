FROM debian:bullseye

RUN apt-get update && apt-get install -y \
	nginx \
	openssl \
	gettext-base \
	&& rm -rf /var/lib/apt/lists/*

RUN mkdir -p /etc/ngnix/ssl

COPY conf/nginx.conf /etc/nginx/nginx.conf.template

COPY tools/gererate_ssl.sh /gererate_ssl.sh
COPY tools/entrypoint.sh /entrypoint.sh
RUN chmod +x /generate_ssl.sh /entrypoint.sh

RUN mkdir -p /var/log/ngnix \
	&& chown -R www-data:www-data /var/log/nginx

EXPOSE 443

CMD ["/entrypoint.sh"]
