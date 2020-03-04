CC = gcc
CFLAGS = -g -Wall
HEADERS = tema3.c
OBJECTS = tema3.o
EXEC = test

.PHONY = default build clean
default: build

build: test

test:
	$(CC) $(CFLAGS) $(HEADERS) -o $(EXEC)

# %.o: %.c $(HEADERS)
# 	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)
run: build 
	./$(EXEC) $(ARGS)
run_task1: build
	./test 1
run_task2: build
	./test 2
run_task3: build
	./test 3
run_task4: build
	./test 4
run_bonus: build
	./test bonus

clean:
	rm -f $(OBJECTS)
	rm -f $(EXEC)

