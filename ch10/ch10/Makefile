#file: Makefile
#author: 2018117610_moonjunyong
#datatime: 2021-12-5 23:00

#build all
all: read pipe2 pipe3

#build read
read: read.o
	cc -c read.c -o read

#build pipe2
pipe2: pipe2.o
	cc -c pipe2.c -o pipe2

#build pipe3
pipe3: pipe3.o
	cc -c pipe3.c -o pipe3

#build clean
clean:
	rm -rf ./*.o

