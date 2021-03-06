#ifndef MIDI_TRK_
#define MIDI_TRK_

#include <iostream>
#include <string>
#include "MidiFile.h"

using namespace std;

// track on midi.
class midi_trk {
  private:
    string file_name;
    MidiFile midi_file;
    unsigned int bytes_in_image;

  public:

  // Constructor
  midi_trk(string file);
  midi_trk();

  ~midi_trk();

  string reveal();
  int hide(string message, string output_file);
  
  //attacks
  int might_hide_something();
  vector<string> is_hiding_messages();
  
  int isValid(string file);
  string get_name();
};

#endif