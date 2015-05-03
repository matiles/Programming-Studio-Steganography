/**************************************************************
*                                                             *
*    Author: Mateo Aviles                                     *
*    file: lsb_embed.cpp                                      *
*    date: 5-2-2015                                           *
*                                                             *
* description: embeds secret message 8 bit greyscale bmp files*
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
	cout << "This program only excepts 8 bit bmp files" << endl;
	cout << "Provide a cover image for your secret message (eg. a_regular_file.bmp): ";
	string file;
	getline(cin, file);
	
	string outfile;
	cout << "Provide the output file to hide your secret message (eg. message_file.bmp): ";
	getline(cin, outfile);

	bmp_lsb duck_file(file);
	
	//ask user what message they would like to hide
	string secret_message;
	cout << "Input secret message: ";
	getline(cin, secret_message);
	
	if(duck_file.hide(secret_message, outfile)){
		cout << "\nSuccessfully wrote message in... " << outfile << endl;
	}
	else{
		cout << "Something went wrong." << endl;
	}

	return 0;
}
