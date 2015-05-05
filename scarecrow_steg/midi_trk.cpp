#include <fstream>
#include <cstdlib>
#include <string.h>
#include <iostream>

#include "midi_trk.h"
#include "MidiFile.h"
#include "MidiEvent.h"

int midi_trk::isValid(string original_file){
  std::size_t pos = original_file.find(".");// position of "." in original file
  string ext = original_file.substr(pos);
  if(ext != ".mid"){
    return 0;
  }
  return 1;
}

// Defualt constructor
midi_trk::midi_trk(){

}

// Constructor
midi_trk::midi_trk(string original_file){
  if(!isValid(original_file)){
    cerr << "This is either not an midi file, or we could not read from the file." << endl;
  }

  file_name = original_file;
  midi_file.read(file_name);
  if(!midi_file.status()){
    cerr << "could not read from file" << endl;
    exit(1);
  }
}

midi_trk::~midi_trk(){
  //none needed
}

string midi_trk::reveal(){

 int trk_count = midi_file.getTrackCount();

 //go to last track
 int event_count = midi_file.getEventCount(trk_count-1);

 vector<unsigned char> message;
 // vector<unsigned char> message = midi_file[trk_count-1][0].getMessage();
 
// cout << "message.size() is: " << message.size() << endl;
// cout << "message[0]: " << (int)message[0] << endl;
// cout << "message[1]: " << (int)message[1] << endl;
// cout << "message[2]: " << (int)message[2] << endl;
// cout << "message[3]: " << (char)message[3] << endl;
// cout << "message[4]: " << (char)message[4] << endl;
// cout << "message[5]: " << (char)message[5] << endl;
// cout << "message[6]: " << (char)message[6] << endl;

//iterate through events
for (int j = 0; j < event_count; ++j){
  message = midi_file[trk_count-1][j].getMessage();
  //if its a text event and if it has the secret identifier
  if( (int)message[0] == 255 && (int)message[1] == 1 && (char)message[3] == '|'){
    break;
  }
}

string message_str;
//start of message always starts at index 4. Read until the end.
for (int i = 4; i < message.size(); ++i){
   message_str += message[i];
 }
 return message_str;
}

int midi_trk::hide(string secret_message, string out_file){
  //calculate the space required to fit message
  int required_bytes = secret_message.length();
  string identifier = "|";
  secret_message = identifier + secret_message;

  //each track is 10 bytes long
  //create track
  midi_file.absoluteTicks();
  int track = midi_file.addTrack(1);
  //int type = 256;
  int type = 65281;

  //add event
  midi_file.addMetaEvent(track,0,type,secret_message.c_str());

  //write/create the stego object
  midi_file.sortTracks();
  //midi_file.write(out_file);
  midi_file.write(out_file);

  return 1;
}
  
int midi_trk::how_many_chars(){
  return 0;
}

string midi_trk::get_name(){
  return file_name;
}

void midi_trk::is_hiding_something(){
  //check if image is hiding a secrete message

  //if so reveal what the image is hiding

  //if tell the user that the image is not hiding anything
}
