all:
	gcc -c file.c
	ar rvs libfile.a file.o
	gcc -o test test.c libfile.a

clean:
	rm -f *.o *.a test
