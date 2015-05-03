/**************************************************************
*                                                             *
*  EasyBMP Cross-Platform Windows Bitmap Library Code Sample  * 
*                                                             *
*  Author: Paul Macklin                                       *
*   email: macklin01@users.sourceforge.net                    *
*     WWW: http://easybmp.sourceforge.net                     *
*                                                             *
*    file: ColorToGrey.cpp                                    *
*    date: 5-26-2006                                          *
* version: 1.02                                               *
*                                                             *
*   License: GPL v 2                                          *
* Copyright: 2005-6 by the EasyBMP Project                    *
*                                                             *
* description: Code sample for EasyBMP library that converts  *
*              any 1, 4, 8, 16, 24, or 32-bit BMP to greyscale*
*                                                             *
**************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>

#include <string>
#include <bitset>  

#include "EasyBMP.h"

typedef unsigned char BYTE;

using namespace std;

int main( int argc, char* argv[] ){

	//ask user for for image file name
	string image_name;
	cout << "please provide the name of the cover image you would like to use: ";
	//cin >> image_name;
	getline(cin, image_name);
	
	//check if we read from file properly
	BMP image;
	if( !image.ReadFromFile(image_name.c_str()) ){
		cerr << "Could not read from file" << endl;
	}

	//check if this is not an 8-bit image
	if(image.TellBitDepth() != 8){
		cerr << "This is not an 8-bit BMP image" << endl;
	}

	//get number of bytes we can use for hiding the message
	BMIH image_info_header = GetBMIH(image_name.c_str());
	unsigned int bytes_in_image = image_info_header.biSizeImage;

	//tell user how many characters can be embedded in the image
	string ans1;
	cout << "You can embed " << bytes_in_image << " characters in this image." << endl;
	cout << "Would you still like to use this image? (Y or N) : "; 
	//cin >> ans1;
	getline(cin, ans1);
	if(ans1 != "N" || ans1 != "Y"){
		cerr << "Bad imput" << endl;
	}
	if(ans1 == "N"){
		//let user choose different image
	}

	//ask user what message they would like to hide
	string secret_message;
	cout << "Input secret message: ";
	//cin >> secret_message;
	getline(cin, secret_message);

	//check if secret message would fit
	if( 8 * secret_message.length() > bytes_in_image ){
		cerr << "sorry your message is to long. Please try agiain with a different message.";
	}

	/*
	//encode
	BMFH image_header = GetBMFH(image_name);
	unsigned int off_set_data = image_header.bfoffBits;
	for(int i=0; i<secret_message.length(); ++i){
		embed(secret_message.at(i), image, off_set_data);
		++off_set_data;
	}
	*/

	//get offset
	BMFH image_header = GetBMFH(image_name.c_str());
	unsigned int off_set_data = image_header.bfOffBits;

	//to read and minipulate file
	FILE *bmp_file;
	FILE *outfile;

	string out_file_name = "s_" + image_name;
	const char *input_file_name = image_name.c_str();
	const char *output_file_name = (out_file_name).c_str();
	
	//open files
	bmp_file = fopen(input_file_name,"rb");
	outfile = fopen(output_file_name,"w+b");

	//header and metadata
	unsigned char header[54];
	unsigned char metadata[off_set_data-54];
	
	//fread(header, 54, 1, bmp_file);	//read BMP header
	fread(header, 1, 54, bmp_file);	//read BMP header
	
	//fwrite(header, 54, 1, outfile);	//write BMP header
	fwrite(header, 1, 54, outfile);	//write BMP header
	
	//fread(metadata, off_set_data - 54, 1, bmp_file);	//read meta
	fread(metadata, 1, off_set_data - 54, bmp_file);	//read meta
	
	//fwrite(metadata, off_set_data - 54, 1, outfile);	//write meta
	fwrite(metadata, 1, off_set_data - 54, outfile);	//write meta
	
	//fseek(bmp_file, off_set_data-54, SEEK_CUR);		//go to BMP image data

	//keep track of the current size of our file
	unsigned int size = bytes_in_image;

	char bmp_buffer;
	char message_buffer;
	char temp_buffer;
	char terminator = '|';
	
	//embed secret message
	for(int i = 0; i<secret_message.length(); ++i){
		message_buffer = secret_message.at(i);
		cout << "\nmessage_buffer: " << message_buffer << endl;
		for(int j = 0; j < 8; j++){
			//temp_buffer = message_buffer;
			bmp_buffer = fgetc(bmp_file);
			bmp_buffer &= 0xFE;
			bmp_buffer |= (char)((message_buffer >> j) & 1);
			
			//get bit
			//temp_buffer <<=  j;
			//temp_buffer >>=  (7 - j);
			//bmp_buffer |= (char) temp_buffer;
			fputc(bmp_buffer,outfile);

			size--;
		}
	}

	//embed terminator
	for(int k = 0; k < 8; k++){
		bmp_buffer = fgetc(bmp_file);
		bmp_buffer &= 0xFE;
		bmp_buffer |= (char)((terminator >> k) & 1);
		fputc(bmp_buffer,outfile);
		size--;
	}

	// write remaing bmp bytes into the new bmp file.
	if(size != 0){
		while( ! feof(bmp_file) ){
			fputc(fgetc(bmp_file), outfile);
		}
	}

	//close files
	fclose(bmp_file);
	fclose(outfile);

	cout << "reached the end of embedding" << endl;
	cout << "Now time for extracting" << endl;

	//extracting
	const char *bmpfile = out_file_name.c_str();
	char *txtfile = "road_secret_message.txt";

	FILE *bfile, *tfile;
	char ch, bmpBuffer[8];
	int i;
	bfile = fopen(bmpfile,"rb");
	tfile = fopen(txtfile,"w+b");

	fseek(bfile, off_set_data, SEEK_SET);	//skip the BMP header part
	int count = 0;
	char temp;

	while(!feof(bfile))
	{
		++count;
		//read the last bit from BMP file
		ch = 0;
		for(i=0; i<=7; i++)
		{
			bmpBuffer[i] = fgetc(bfile);
		}

		for(i=7; i>=0; i--)
		{
			ch += (bmpBuffer[i] & 1);
			if(i != 0)
				ch <<= 1;
		}

/*
		for(i=0; i<8; i++){
			temp = bmpBuffer[i];
			cout << "(int) temp BEFORE: " << (int) temp << endl;

			temp << 7;
			temp >> 7;

			cout << "(int) temp: " << (int) temp << endl;
			//temp >> 7- i;
			//ch |= (char)temp;
			
			ch ^= (-((int) temp) ^ ch) & (1 << 7-i);
			//ch = ch & ~(1 << 7) | (bmpBuffer[i] << 7);
		}
*/

		if(ch == '|')
		{
			cout << "Reached terminating character done." << endl;
			cout << "COUNT: " << count << endl;
			break;
		}
		if(ch == EOF)
		{
			cout << "Reached EOF done." << endl;
			cout << "COUNT: " << count << endl;
			break;
		}
		cout << "extracted character: " << ch << endl;
		fputc(ch,tfile);
	}

	fclose(bfile);
	fclose(tfile);
	
	return 0;
}
