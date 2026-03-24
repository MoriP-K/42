.PHONY: all build up down clean fclean re log cls vls nls ils

# ホスト側のディレクトリパス
DATA_PATH = /home/kmoriyam/data

all: prepare build up

prepare:
	@sudo mkdir -p $(DATA_PATH)/mysql
	@sudo mkdir -p $(DATA_PATH)/wordpress
	@sudo chmod 777 $(DATA_PATH)/mysql
	@sudo chmod 777 $(DATA_PATH)/wordpress

build:
	@cd srcs && docker compose build

up:
	@cd srcs && docker compose up -d

down:
	@cd srcs && docker compose down

clean: down
	@docker system prune -af

fclean: clean
	@cd srcs && docker compose down -v
	@sudo rm -rf $(DATA_PATH)
	@docker system prune -a --force

re: fclean all

cls:
	@cd srcs && docker container ls -a

vls:
	@cd srcs && docker volume ls

ils:
	@cd srcs && docker image ls

nls:
	@cd srcs && docker network ls

log:
	@cd srcs && docker compose logs