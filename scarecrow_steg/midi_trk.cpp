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

  //iterate through events
  for (int j = 0; j < event_count; ++j){
    message = midi_file[trk_count-1][j].getMessage();
    //if its a text event and if it has the secret identifier
    if( (int)message[0] == 255 && (int)message[1] == 1 && (char)message[3] == '|'){
      break;
    }
  }

  string message_str;
  //start of message always starts at index 4 for our implementation. Read until the end.
  for (int i = 4; i < message.size(); ++i){
    message_str += message[i];
  }
  return message_str;
}

int midi_trk::hide(string secret_message, string out_file){

  if(!midi_file.status()){
	cerr << "\nFile could not be read." << endl;
  }

  string identifier = "|";
  secret_message = identifier + secret_message;

  //create track
  midi_file.absoluteTicks();
  int track = midi_file.addTrack(1);

  //add event
  int type = 65281;
  midi_file.addMetaEvent(track,0,type,secret_message.c_str());

  //write/create the stego object
  midi_file.sortTracks();
  midi_file.write(out_file);

  return 1;
}

string midi_trk::get_name(){
  return file_name;
}

//simply checks for meta messenges since this is where embeding will likely occur
int midi_trk::might_hide_something(){

  int trk_count = midi_file.getTrackCount();
  int event_count;

  vector<unsigned char> message;

  //iterate through tracks
  for(int i=0; i<trk_count; ++i){
    //iterate through events
    event_count = midi_file.getEventCount(i);
    for(int j=0; j < event_count; ++j){
      message = midi_file[i][j].getMessage();
      //if it is some sort of text event
      if( (int)message[0] == 255 && ( (int)message[1] == 1 ||
                                      (int)message[1] == 2 ||
                                      (int)message[1] == 3 ||
                                      (int)message[1] == 4 ||
                                      (int)message[1] == 5)
        )
      {
        return 1;
      }
    }
  }

  return 0;
}

vector<string> midi_trk::is_hiding_messages(){

  int trk_count = midi_file.getTrackCount();
  int event_count;

  vector<unsigned char> message;
  vector<vector<unsigned char>> meta_messages;

  //iterate through tracks
  for(int i=0; i<trk_count; ++i){
    event_count = midi_file.getEventCount(i);
    //iterate through events
    for (int j = 0; j < event_count; ++j){
      message = midi_file[i][j].getMessage();
      //if its some sort text event
      if( (int)message[0] == 255 && ( (int)message[1] == 1 ||
                                      (int)message[1] == 2 ||
                                      (int)message[1] == 3 ||
                                      (int)message[1] == 4 ||
                                      (int)message[1] == 5)
        )
      {
        meta_messages.push_back(message);
      }
    }
  }

  vector<string> possible_messages;
  //iterate through suspicious messages
  for(int k=0; k < meta_messages.size(); ++k){
    string message_str;
    //start of message always starts at index 3. Read until the end.
    for(int l = 3; l < meta_messages[k].size(); ++l){
      message_str += meta_messages[k][l];
    }
    possible_messages.push_back(message_str);
  }

  return possible_messages;
}