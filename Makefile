all:
	gcc src/main.c src/menu.c src/util/simulated_process.c src/shared/queue.c src/core/control.c src/core/management.c src/core/scheduling.c -o dist/main
run:
	dist/main
clean:
	rm dist/main
clean_exec:
	rm dist/main.exe