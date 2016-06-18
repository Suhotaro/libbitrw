all:
	cd src && make
	cd ..
	cd tests && make

clean:
	cd src && make clean
	cd ..
	cd tests && make clean
