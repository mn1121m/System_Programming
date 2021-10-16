#file: Makefile
#author: 2018117610_ moon jun yong
#datetime: 2021-10-15 15:30

# build all
all : ticker_demo myhello

# build ticker_demo
ticker_demo: ticker_demo.o
		gcc ticker_demo.c set_ticker.c -o ticker_demo

# build myhello	
myhello: myhello.o
		gcc myhello.c -lcurses -o myhello

# clean
clean:
	rm -rf *.o
