#! /bin/bash

echo "Initialize MariaDB..."

if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Initializing DB..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
    mysqld --user=mysql --bootstrap << EOF
UPDATE mysql.user SET Password=PASSWORD('${DB_ROOT_PASS}') WHERE User='root';
DELETE FROM mysql.user WHERE User='';
DROP DATABASE IF EXISTS test;
CREATE DATABASE ${DB_NAME};
CREATE USER '${DB_USER}'@'%' IDENTIFIED BY '${DB_PASS}';
GRANT ALL PRIVILEGES ON ${DB_NAME}.* TO '${DB_USER}'@'%';
FLUSH PRIVILEGES;
EOF

        echo "Complete initializing"
fi

echo "Launching MariaDB..."
exec mysqld --user=mysql --console