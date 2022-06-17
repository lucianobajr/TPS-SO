all:
	gcc src/main.c src/menu.c src/util/process.c src/util/process_table.c -o dist/main
run:
	dist/main
clean:
	rm dist/main
clean_exec:
	rm dist/main.exe