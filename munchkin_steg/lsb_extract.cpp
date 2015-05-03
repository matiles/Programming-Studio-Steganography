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
	string file_name;
	cout << "Input image file name (eg. secret.bmp): ";
	getline(cin,file_name);
	bmp_lsb duck_file(file_name);
	cout << "secret message is: " << duck_file.reveal() << endl;
	
	return 0;
}
