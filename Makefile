all:
	gcc -Wall -c file.c
	ar rvs libfile.a file.o
	gcc -Wall -o test test.c libfile.a

clean:
	rm -f *.o *.a test
