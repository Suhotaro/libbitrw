all: libbitrw
   
libbitrw: bitrw.c bitrw.h
	gcc -c -Wall -Werror -fpic bitrw.c
	gcc -shared -o libbitrw.so bitrw.o

clean:
	rm *.o
	rm *.so
	rm libbitrw.so
