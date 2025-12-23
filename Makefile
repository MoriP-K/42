.PHONY: all build up down clean fclean re logs

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

logs:
	@cd srcs && docker comopse logs