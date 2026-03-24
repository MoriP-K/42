#!/bin/bash

set -e

echo "Initialize MariaDB..."

if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Initializing DB..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
    echo "Setting up database and users..."
    mysqld --user=mysql --bootstrap << EOF
USE mysql;
FLUSH PRIVILEGES;

-- rootパスワード設定
ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_ROOT_PASS}';

-- 不要なユーザー削除
DELETE FROM mysql.user WHERE User='';
DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');

-- testデータベース削除
DROP DATABASE IF EXISTS test;
DELETE FROM mysql.db WHERE Db='test' OR Db='test\\_%';

-- WordPressデータベース作成
CREATE DATABASE IF NOT EXISTS ${DB_NAME};

-- WordPressユーザー作成
CREATE USER IF NOT EXISTS '${DB_USER}'@'%' IDENTIFIED BY '${DB_PASS}';
GRANT ALL PRIVILEGES ON ${DB_NAME}.* TO '${DB_USER}'@'%';

-- 権限反映
FLUSH PRIVILEGES;
EOF

    echo "Complete initializing"
else
    echo "Database already initialized, skipping setup"    
fi

echo "Launching MariaDB..."
exec mysqld --user=mysql --console