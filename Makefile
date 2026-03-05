.PHONY: up down restart build logs ps up-ngrok ngrok stop-ngrok logs-ngrok url-ngrok prisma-studio seed

# デフォルト: アプリ起動（http://localhost:5173 でアクセス）
.DEFAULT_GOAL := up

up:
	docker compose up -d

down:
	docker compose --profile ngrok down

restart: down up

build:
	docker compose build

logs:
	docker compose logs -f

ps:
	docker compose ps

up-ngrok:
	docker compose --profile ngrok up -d

# ngrok トンネル起動（make up 後に実行 → ngrok URL でアクセス可能に）
ngrok:
	docker compose --profile ngrok up -d ngrok

# ngrok のみ停止（frontend/backend/db は起動したまま）
stop-ngrok:
	docker compose --profile ngrok stop ngrok

logs-ngrok:
	docker compose --profile ngrok logs -f ngrok

# ngrok のトンネル URL を表示（Traffic Inspector API から取得）
url-ngrok:
	@curl -s http://localhost:4040/api/tunnels 2>/dev/null | grep -o '"public_url":"[^"]*"' | head -1 | cut -d'"' -f4 || curl -s http://localhost:4040/api/endpoints 2>/dev/null | grep -o '"url":"[^"]*"' | head -1 | cut -d'"' -f4 || echo "ngrok が起動していません。make ngrok を実行してください。"

# Prisma Studio 起動（http://localhost:5555 でアクセス）
prisma-studio:
	docker compose exec backend npx prisma studio

# DB にシードデータを投入
seed:
	docker compose exec backend npx prisma db seed
