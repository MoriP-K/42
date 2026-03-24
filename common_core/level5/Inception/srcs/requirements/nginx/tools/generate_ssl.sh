#!/bin/bash

mkdir -p /etc/nginx/ssl

# SSL証明書を生成（自己署名）
openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/nginx.key \
    -out /etc/nginx/ssl/nginx.crt \
    -subj "/C=JP/ST=Tokyo/L=Tokyo/O=42Tokyo/OU=student/CN=${DOMAIN_NAME}"

echo "SSL certificate generated successfully"