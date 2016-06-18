all: write read

write: write.c ../src/libbitrw.so
	gcc -Wall -o write write.c -L./../src -lbitrw

read: read.c ../src/libbitrw.so
	gcc -Wall -o read read.c -L./../src -lbitrw

clean:
	rm *.o
	rm write
	rm read
