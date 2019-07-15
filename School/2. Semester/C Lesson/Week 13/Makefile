CFLAGS=-std=c99 -Wall -Werror -I.
CC=gcc
LFLAGS=-lm

cube: lesson.o cubeopr.o
	$(CC) $(LFLAGS) lesson.o cubeopr.o -o cube
	
		
lesson.o: lesson.c
	$(CC) -c $(CFLAGS) lesson.c -o lesson.o			
	

cubeopr.o: cubeopr.c
	$(CC) -c $(CFLAGS) cubeopr.c -o cubeopr.o	
	
	
