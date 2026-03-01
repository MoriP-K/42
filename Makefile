.PHONY: up down restart

up:
	./scripts/start.sh

down:
	docker compose down

restart: down up
