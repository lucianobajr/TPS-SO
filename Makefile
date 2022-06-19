compile: 
	gcc ./src/main.c ./src/core/control.c ./src/core/management.c ./src/util/simulated_process.c ./src/shared/queue.c ./src/core/scheduling.c ./src/log/log.c -o ./dist/main

run: 
	./dist/main