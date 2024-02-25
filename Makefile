CC= gcc
CFLAGS= -Wall -g

all: StrList

Main.o: Main.c StrList.h
	$(CC) $(FLAGS) -c $< -o $@

StrList.o: StrList.c StrList.h
	$(CC) $(FLAGS) -c StrList.c

StrList: Main.o StrList.o
	$(CC) $(FLAGS) StrList.o Main.o -o StrList

clean:
	rm -f *.o StrList
