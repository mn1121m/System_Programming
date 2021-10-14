all: cp1 who3 mywho

cp1.o: cp1.c
	cc -c cp1.c
utmplib.o: utmplib.c
	cc -c utmplib.c
who3.co: who3.c
	cc - c who3.c
mywho.o: mywho.c
	cc -c mywho.c

cp1: cp1.o
	cc -c cp1 cp1.o
who3: who3.o utmplib.o
	cc -c who3 who3.o utmplib.o
mywho: mywho.o utmplib.o
	cc -c mywho mywho.o utmplib.o
