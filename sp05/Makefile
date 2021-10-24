#        file: Makefile
#      author: 2018117610 moon jun yong
#    datetime: 2021-10-23(updated)
# description: compile write0 mywrite

# build all
all: write0 mywrite


# build write0
write0: write0.o
	gcc write0.c -o write0

# build mywrite
mywrite: mywrite.o
	gcc mywrite.c -o mywrite

# build clean
clean:
	rm -rf ./*.o
