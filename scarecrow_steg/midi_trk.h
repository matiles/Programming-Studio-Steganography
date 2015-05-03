#ifndef MIDI_TRK_
#define MIDI_TRK_

#include <iostream>
#include <string>

using namespace std;

// track on midi.
class midi_trk {
  private:
    string file_name;
    unsigned int bytes_in_image;

  public:

  // Constructor
  midi_trk(string file);
  midi_trk();

  ~midi_trk();

  string reveal();
  int hide(string message, string output_file);
  void is_hiding_something();  //attack
  
  int isValid(string file);
  int how_many_chars();
  string get_name();
};

#endif