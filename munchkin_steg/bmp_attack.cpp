/**************************************************************
*                                                             *
*    Author: Mateo Aviles                                     *
*    file: lsb_extract.cpp                                    *
*    date: 5-2-2015                                           *
*                                                             *
* description: extracts secret message embedded in bmp files  *
*                                                             *
**************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include "EasyBMP.h"
#include "bmp_lsb.h"

using namespace std;

int main( int argc, char* argv[] ){
	/*
	string file_name;
	cout << "Input image file name you suspect contains message (eg. secret.bmp): ";
	getline(cin,file_name);
	bmp_lsb file(file_name);
	cout << "secret message is: " << file.is_hiding_str() << endl;
	*/
	
	string file_name;
	cout << "Input image file name you suspect contains message (eg. secret.bmp): ";
	getline(cin,file_name);
	bmp_lsb file(file_name);

	if(file.mess_up_message())
		cout << "messed up file successfully." << endl;
	
	return 0;
}
