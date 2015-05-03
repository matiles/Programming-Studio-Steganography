#include <fstream>
#include <cstdlib>
#include <string.h>
#include <iostream>

#include "bmp_lsb.h"
#include "EasyBMP.h"

int bmp_lsb::isValid(string original_file){
  //check if we read from file properly
  BMP image;
  if( !image.ReadFromFile(original_file.c_str()) ){
    return 0;
  }

  //check if this is not an 8-bit image
  if(image.TellBitDepth() != 8){
    return 0;
  }
  return 1;
}

// Defualt constructor
bmp_lsb::bmp_lsb(){
  bytes_in_image = 0;
}

// Constructor
bmp_lsb::bmp_lsb(string original_file){
  //check if the file is valid
  if(!isValid(original_file)){
    cerr << "This is either not an 8-bit BMP image, or we could not read from the file." << endl;
  }

  //get number of bytes we can use for hiding the message
  BMIH image_info_header = GetBMIH(original_file.c_str());

  bytes_in_image = image_info_header.biSizeImage;
  image_name = original_file;
}

bmp_lsb::~bmp_lsb(){
  //none needed
}

string bmp_lsb::reveal(){

  const char *bmpfile = image_name.c_str();
  
  string secret_message;
  //char *txtfile = "road_secret_message.txt";

  FILE *bfile;
  //FILE *tfile;
  
  char ch;
  char bmpBuffer[8];
  int i;
  
  bfile = fopen(bmpfile,"rb");
  //tfile = fopen(txtfile,"w+b");

  //get offset
  BMFH image_header = GetBMFH(image_name.c_str());
  unsigned int off_set_data = image_header.bfOffBits;

  //seek to image data
  fseek(bfile, off_set_data, SEEK_SET); //skip the BMP header and metadata
  int count = 0;
  char temp;

  while(!feof(bfile)){
    ++count;
    ch = 0;
    for(i=0; i<=7; i++){
      bmpBuffer[i] = fgetc(bfile);
    }

    for(i=7; i>=0; i--){
      ch += (bmpBuffer[i] & 1);
      if(i != 0)
        ch <<= 1;
    }

    if(ch == '|'){
      break;
    }
    if(ch == EOF){
      break;
    }
    secret_message += ch;
  }

  fclose(bfile);

  return secret_message;  
}

int bmp_lsb::hide(string secret_message, string out_file){

  //check if secret message would fit
  if( 8 * secret_message.length() > bytes_in_image ){
    cerr << "Sorry your message is to long. Please try agiain with a different message." << endl;
    cerr << "To check how many characters you can use call how_many_chars()" << endl;
    return 0;
  }

  //get offset
  BMFH image_header = GetBMFH(image_name.c_str());
  unsigned int off_set_data = image_header.bfOffBits;

  //to read and minipulate file
  FILE *bmp_file;
  FILE *outfile;

  string out_file_name = out_file;
  const char *input_file_name = image_name.c_str();
  const char *output_file_name = (out_file_name).c_str();
  
  //open files
  bmp_file = fopen(input_file_name,"rb");
  outfile = fopen(output_file_name,"w+b");

  //header and metadata
  unsigned char header[54];
  unsigned char metadata[off_set_data-54];
  
  fread(header, 1, 54, bmp_file); //read BMP header 
  fwrite(header, 1, 54, outfile); //write BMP header
  
  fread(metadata, 1, off_set_data - 54, bmp_file);  //read meta
  fwrite(metadata, 1, off_set_data - 54, outfile);  //write meta
  
  //keep track of the current size of our file
  unsigned int size = bytes_in_image;

  char bmp_buffer;
  char message_buffer;
  char terminator = '|';
  
  //embed secret message
  for(int i = 0; i<secret_message.length(); ++i){
    message_buffer = secret_message.at(i);
    for(int j = 0; j < 8; j++){
      bmp_buffer = fgetc(bmp_file);
      bmp_buffer &= 0xFE;
      bmp_buffer |= (char)((message_buffer >> j) & 1);
      
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

  return 1;
}
  
int bmp_lsb::how_many_chars(){
  return bytes_in_image;
}

string bmp_lsb::get_name(){
  return image_name;
}

void bmp_lsb::is_hiding_something(){
  //check if image is hiding a secrete message

  //if so reveal what the image is hiding

  //if tell the user that the image is not hiding anything
}
