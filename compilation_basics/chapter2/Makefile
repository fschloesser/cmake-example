all:
	gcc -c helper.c main.c
	gcc -o hello main.o helper.o

all2:
	gcc -c helper.c
	gcc -o hello main.c helper.o

all3:
	gcc -o hello main.c helper.c

clean:
	rm -f hello main.o helper.o
