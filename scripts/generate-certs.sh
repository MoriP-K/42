#!/bin/bash
# 自己署名証明書を生成（ローカル開発・評価用）
# 使用方法: ./scripts/generate-certs.sh

set -e

CERT_DIR="$(cd "$(dirname "$0")/.." && pwd)/nginx/certs"
mkdir -p "$CERT_DIR"

if [ -f "$CERT_DIR/cert.pem" ] && [ -f "$CERT_DIR/key.pem" ]; then
	echo "証明書は既に存在します: $CERT_DIR"
	exit 0
fi

echo "自己署名証明書を生成中: $CERT_DIR"
openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
	-keyout "$CERT_DIR/key.pem" \
	-out "$CERT_DIR/cert.pem" \
	-subj "/CN=localhost/O=ft_transcendence/C=JP"

echo "完了: cert.pem, key.pem を生成しました"
echo "ブラウザで「接続はプライベートではありません」と表示される場合は「詳細」→「安全でないサイトに進む」を選択してください"
