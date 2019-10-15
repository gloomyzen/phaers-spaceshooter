###############################################################################
## Переменные окружения
###############################################################################
cur-path = $(shell pwd)
## Берём название текущей папки. Изначально проект докера = названию папки. см. "docker-compose -p"
cur-dir = $(shell basename ${cur-path})
## Получаем тип операционной системы
os-type = $(shell if [ "${OS}" == "Windows_NT" ]; then \
	echo "windows"; \
	else \
	echo "linux"; \
	fi)
## Получаем тип дистрибутива
##dist-name := $(shell tr -s ' \011' '\012' < /etc/issue | head -n 1)
dist-name = $(shell if [ "${os-type}" != "windows" ]; then \
	echo $(shell tr -s ' \011' '\012' < /etc/issue | head -n 1); \
	else \
	echo "windows"; \
	fi)
## В Arch Linux немного отличаются команды на права к файлам
user-group = $(shell if [ "${dist-name}" == "Arch" ]; then \
	echo "${USER}"; \
	elif [ ${dist-name} == "windows" ]; then \
	echo ""; \
	else \
	echo "${USER}:${USER}"; \
	fi)

###############################################################################
## Основые команды
###############################################################################
docker-up:
	docker-compose up -d

docker-down:
	docker-compose down

docker-build:
	docker-compose up --build -d

###############################################################################
## Настройка
###############################################################################

docker-env:
	if [ ! -f "${PWD}/env_file" ]; then cp env_file.example env_file; fi

## Работа с nodejs
assets-install:
	docker-compose exec node npm install

assets-dev:
	docker-compose exec node npm run dev

assets-prod:
	docker-compose exec node npm run prod

assets-watch:
	docker-compose exec node npm run watch

## Командная строка контейнеров
go_node:
	@if [ "windows" == ${os-type} ]; then \
		echo "Run NODEJS Cli..." && winpty docker exec -it ${cur-dir}_node_1 sh; \
	else \
		echo "Run NODEJS Cli..." && docker exec -it ${cur-dir}_node_1 sh; \
	fi

go_nginx:
	@if [ "windows" == ${os-type} ]; then \
		echo "Run NGINX Cli..." && winpty docker exec -it ${cur-dir}_nginx_1 sh; \
	else \
		echo "Run NGINX Cli..." && docker exec -it ${cur-dir}_nginx_1 sh; \
	fi

## Остановка и удаление всех контейнеров
remove: down
	docker system prune

force-remove: down
	docker system prune -a

###############################################################################
## Common
###############################################################################

build: docker-env docker-build

up: docker-env docker-up

down: docker-down