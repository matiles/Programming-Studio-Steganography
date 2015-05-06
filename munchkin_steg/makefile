# makefile


clean:
	rm -f *.o

all: lsb_extract lsb_embed bmp_attack

EasyBMP.o: EasyBMP.h EasyBMP.cpp
	g++-4.7 -std=c++11 -c EasyBMP.cpp

bmp_lsb.o: bmp_lsb.h bmp_lsb.cpp EasyBMP.o
	g++-4.7 -std=c++11 -c bmp_lsb.cpp

lsb_extract: lsb_extract.cpp bmp_lsb.o EasyBMP.o
	g++-4.7 -std=c++11 -o lsb_extract lsb_extract.cpp bmp_lsb.o EasyBMP.o

lsb_embed: lsb_embed.cpp bmp_lsb.o EasyBMP.o
	g++-4.7 -std=c++11 -o lsb_embed lsb_embed.cpp bmp_lsb.o EasyBMP.o

bmp_attack: bmp_attack.cpp bmp_lsb.o EasyBMP.o
	g++-4.7 -std=c++11 -o bmp_attack bmp_attack.cpp bmp_lsb.o EasyBMP.o

# lsb_extract: lsb_extract.cpp 
# 	g++-4.7 -std=c++11 -o lsb_extract lsb_extract.cpp bmp_lsb.h bmp_lsb.cpp EasyBMP.h EasyBMP.cpp 

# lsb_embed: lsb_embed.cpp bmp_lsb.o
# 	g++-4.7 -std=c++11 -o lsb_embed lsb_embed.cpp bmp_lsb.h bmp_lsb.cpp EasyBMP.h EasyBMP.cpp
