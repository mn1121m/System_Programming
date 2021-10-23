# file:	Makefile
# author: 2018117610_moon jun yong
# datetime: 2021-10-23(Sat)(updated)
# description: compile spwd.c myspwd.c

# build all
all: spwd myspwd


# build spwd
spwd: spwd.o
	gcc spwd.c -o spwd

# build myspwd
myspwd: myspwd.o
	gcc myspwd.c -o myspwd

# build clean
clean:
	rm -rf ./*.o
