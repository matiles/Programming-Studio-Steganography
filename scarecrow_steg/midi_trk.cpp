#include <fstream>
#include <cstdlib>
#include <string.h>
#include <iostream>

#include "midi_trk.h"
#include "MidiFile.h"

int midi_trk::isValid(string original_file){
  std::size_t pos = original_file.find(".");// position of "." in original file
  string ext = original_file.substr(pos);
  if(ext != "mid"){
    return 0;
  }
  return 0;
}

// Defualt constructor
midi_trk::midi_trk(){

}

// Constructor
midi_trk::midi_trk(string original_file){
  if(!isValid(original_file)){

  }

}

midi_trk::~midi_trk(){
  //none needed
}

string midi_trk::reveal(){
 return "none";
}

int midi_trk::hide(string secret_message, string out_file){
  return 0;
}
  
int midi_trk::how_many_chars(){
  return 0;
}

string midi_trk::get_name(){
  return "none";
}

void midi_trk::is_hiding_something(){
  //check if image is hiding a secrete message

  //if so reveal what the image is hiding

  //if tell the user that the image is not hiding anything
}
