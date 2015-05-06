// Creation Date: Tue May 5, 2015
// Filename:      midi_trk.cpp
// Syntax:        C++
// Description:   Embeding messages in MIDI file.

#include "midi_trk.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

   cout << "This program only excepts midi files (ie .mid)" << endl;
   cout << "Please provide midi you suspect contains a secret message (eg. file.mid): ";
   string file;
   getline(cin, file);
   
   midi_trk midi_file(file);
   
   if(midi_file.might_hide_something()){
      cout << "\nThis midi file is suspected of hiding something... " << endl;
      cout << "\nHere is what we found..." << endl;
      for(int i=0; i < midi_file.is_hiding_messages().size(); ++i){
         cout << i+1 << ". " << midi_file.is_hiding_messages()[i] << endl;
      }
   }
   else{
      cout << "This file is likely not hiding anything." << endl;
   }
   
   return 0;
}
