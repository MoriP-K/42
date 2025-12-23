.PHONY: all build up down clean fclean re log cls vls ils

all: build up

build:
	@mkdir -p /home/kmoriyam/data/mysql
	@mkdir -p /home/kmoriyam/data/wordpress
	@cd srcs && docker-compose build

up:
	@cd srcs && docker-compose up -d

down:
	@cd srcs && docker-compose down

clean: down
	@docker system prune -af

fclean: clean
	@cd srcs && docker-compose down -v
	@sudo rm -rf /home/kmoriyam/data/mysql/*
	@sudo rm -rf /home/kmoriyam/data/wordpress/*
	@docker volume prune -f

re: fclean all

cls:
	@cd srcs && docker container ls -a

vls:
	@cd srcs && docker volume ls

ils:
	@cd srcs && docker image ls

log:
	@cd srcs && docker compose logs ls