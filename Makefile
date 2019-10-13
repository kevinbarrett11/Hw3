hw3.o: hw3.c
	gcc -c hw3.c

hw3: hw3.o 
	gcc -o hw3 hw3.o -lm

all: hw3

clean:
	rm *.o hw3