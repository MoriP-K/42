#!/bin/bash
# 証明書がなければ生成し、Docker Compose で起動
# 使用方法: ./scripts/start.sh

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$PROJECT_ROOT"

# 証明書がなければ生成
if [ ! -f "nginx/certs/cert.pem" ] || [ ! -f "nginx/certs/key.pem" ]; then
	echo "証明書を生成しています..."
	./scripts/generate-certs.sh
fi

docker compose up -d
