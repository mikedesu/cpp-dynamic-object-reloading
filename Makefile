

all: main maincpp



main: test.so
	gcc -o main main.c


maincpp: HelloWorld.so
	g++ -o maincpp main.cpp HelloWorld.o


test.o: test.c
	gcc -g -c test.c

test.so: test.o
	gcc -shared -o test.so test.o



HelloWorld.o: 
	g++ -g -c -fPIC HelloWorld.cpp

HelloWorld.so: HelloWorld.o
	g++ -shared -o HelloWorld.so HelloWorld.o


clean:
	rm -f *.o *.so main maincpp
