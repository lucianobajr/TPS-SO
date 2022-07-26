all:
	gcc ./src/main.c ./src/core/control.c ./src/core/management.c ./src/core/scheduling.c ./src/components/simulated_process.c ./src/components/main_memory.c ./src/shared/queue.c ./src/shared/list.c ./src/metrics/metrics.c ./src/log/log.c ./src/domain/domain.c ./src/components/virtual_memory.c -o ./dist/main
test:
	gcc ./__tests__/file.c -o ./__tests__/tests
metrics:
	gcc ./src/main-4.c ./src/components/main_memory.c ./src/metrics/metrics.c ./src/log/log.c ./src/shared/list.c ./src/shared/queue.c ./src/domain/domain.c  -o ./dist/test
virtual:
	gcc ./src/main-3.c ./src/components/main_memory.c ./src/metrics/metrics.c ./src/log/log.c ./src/shared/list.c ./src/components/virtual_memory.c  -o ./dist/out	
	gcc ./src/main-2.c ./src/components/main_memory.c ./src/metrics/metrics.c ./src/log/log.c ./src/shared/queue.c ./src/shared/list.c  -o ./dist/test
run:
	dist/main 1
run_test:
	__tests__/tests
run_metrics:
	dist/test
run_virtual:
	dist/out 
clean:
	rm dist/main
clean_exec:
	rm dist/main.exe