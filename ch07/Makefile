#file: Makefile
#author: 2018117610_ moon jun yong
#datetime: 2021-10-15 15:30 => 2021-10-28(updated)

# build all
all : ticker_demo myhello

# build ticker_demo
ticker_demo: ticker_demo.o
		cc ticker_demo.c set_ticker.c -o ticker_demo

# build myhello	
myhello: myhello.o
		cc myhello.c -lcurses -o myhello

# build clean
clean:
	rm -rf ./*.o
