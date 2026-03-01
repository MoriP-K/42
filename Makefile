.PHONY: up down restart build logs ps

up:
	./scripts/start.sh

down:
	docker compose down

restart: down up

build:
	docker compose build

logs:
	docker compose logs -f

ps:
	docker compose ps
