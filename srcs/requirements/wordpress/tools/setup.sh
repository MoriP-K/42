#!/bin/bash
set -e

echo "Starting WordPress setup..."

# php-fpmログディレクトリを作成
mkdir -p /var/log/php-fpm
chown -R www-data:www-data /var/log/php-fpm

# WordPressがまだインストールされていない場合
if [ ! -f /var/www/html/wp-config.php ]; then
    echo "WordPress not found, installing..."
    
    # WordPressをダウンロード
    wp core download --allow-root --path=/var/www/html
    
    echo "Waiting for MariaDB to be ready..."
    # MariaDBが起動するまで待機
    until wp db check --allow-root --path=/var/www/html \
        --dbhost=mariadb \
        --dbname=${DB_NAME} \
        --dbuser=${DB_USER} \
        --dbpass=${DB_PASS} 2>/dev/null; do
        echo "MariaDB is not ready yet, waiting..."
        sleep 3
    done
    
    echo "MariaDB is ready!"
    
    # wp-config.phpを作成
    wp config create --allow-root \
        --path=/var/www/html \
        --dbname=${DB_NAME} \
        --dbuser=${DB_USER} \
        --dbpass=${DB_PASS} \
        --dbhost=mariadb:3306
    
    # WordPressをインストール
    wp core install --allow-root \
        --path=/var/www/html \
        --url=${DOMAIN_NAME} \
        --title="${WP_TITLE}" \
        --admin_user=${WP_ADMIN_USER} \
        --admin_password=${WP_ADMIN_PASS} \
        --admin_email=${WP_ADMIN_EMAIL}
    
    # 一般ユーザーを作成
    wp user create --allow-root \
        --path=/var/www/html \
        ${WP_USER} \
        ${WP_USER_EMAIL} \
        --user_pass=${WP_USER_PASS} \
        --role=author
    
    # 権限を設定
    chown -R www-data:www-data /var/www/html
    chmod -R 755 /var/www/html
    
    echo "WordPress installation completed!"
else
    echo "WordPress already installed, skipping setup"
fi

echo "Starting php-fpm..."
# php-fpmをフォアグラウンドで起動
exec php-fpm7.4 -F