#Makefile
#2018117610_moonjunyong

# build all
all: cp1 who3 mywho

# build cp1
cp1: cp1.o
	cc cp1.c -o cp1

# build who3
who3: who3.o
	cc who3.c utmplib.c -o who3

# build mywho
mywho: mywho.o
	cc mywho.c utmplib.c -o mywho

# build clean
clean:
	rm -rf *.o
