FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    mariadb-server \
    && rm -rf /var/lib/apt/lists/*

COPY tools/init_db.sh /init_db.sh
RUN chmod +x /init_db.sh

RUN mkdir -p /var/run/mysqld \
    && chown -R mysql:mysql /var/run/mysqld \
    && chown -R mysql:mysql /var/lib/mysql

EXPOSE 3306

USER mysql

ENTRYPOINT ["/init_db.sh"]