#!/bin/bash
set -e

echo "Configuring NGINX..."

# 環境変数をNGINX設定に適用
envsubst '${DOMAIN_NAME}' < /etc/nginx/nginx.conf.template > /etc/nginx/nginx.conf

echo "Generating SSL certificate..."
/generate_ssl.sh

echo "Testing NGINX configuration..."
nginx -t

echo "Starting NGINX..."
exec nginx -g 'daemon off;'