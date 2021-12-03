#file: Makefile
#author: 2018117610_moonjunyong
#datetime: 2021-11-20 1:00(AM)


#build smsh4
smsh4: smsh4.o
	cc -o smsh4 smsh4.c splitline.c execute2.c process2.c controlflow.c \
		builtin.c varlib.c

#build clean
clean:
	rm -rf ./*.o
