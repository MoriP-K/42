.PHONY: up down restart build logs ps up-ngrok ngrok logs-ngrok url-ngrok setup

# デフォルト: アプリ起動
.DEFAULT_GOAL := up

# .env がなければ backend/.env へのシンボリックリンクを作成（Docker Compose が自動読み込み）
setup:
	@if [ -f backend/.env ] && [ ! -f .env ]; then ln -sf backend/.env .env && echo "Created .env -> backend/.env"; fi

up: setup
	./scripts/start.sh

down:
	docker compose --profile ngrok down

restart: down up

build:
	docker compose build

logs:
	docker compose logs -f

ps:
	docker compose ps

up-ngrok: setup
	docker compose --profile ngrok up -d

ngrok: setup
	docker compose --profile ngrok up -d ngrok

logs-ngrok:
	docker compose --profile ngrok logs -f ngrok

# ngrok のトンネル URL を表示（Traffic Inspector API から取得）
url-ngrok:
	@curl -s http://localhost:4040/api/tunnels 2>/dev/null | grep -o '"public_url":"[^"]*"' | head -1 | cut -d'"' -f4 || curl -s http://localhost:4040/api/endpoints 2>/dev/null | grep -o '"url":"[^"]*"' | head -1 | cut -d'"' -f4 || echo "ngrok が起動していません。make ngrok を実行してください。"
