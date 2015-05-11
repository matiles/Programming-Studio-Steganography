all: RSA_Encryption.o attacks.o
	g++-4.7 -std=c++11 RSA_Encryption.o -o munchkincrypt 
	g++-4.7 -std=c++11 attacks.o -o dorothy
munchkincrypt: RSA_Encryption.cpp
	g++-4.7 -std=c++11 -c RSA_Encryption.cpp
dorothy: attacks.cpp
	g++-4.7 -std=c++11 -c attacks.cpp
clean:
	rm *.o 

