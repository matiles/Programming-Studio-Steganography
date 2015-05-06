// Creation Date: Tue May 5, 2015
// Filename:      midi_trk.cpp
// Syntax:        C++
// Description:   Embeding messages in MIDI file.

#include "midi_trk.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
   cout << "\nHello from midi_extract" << endl;

   cout << "This program only excepts midi files (ie .mid)" << endl;
   cout << "Please provide midi for extracing secret message (eg. a_regular_file.mid): ";
   string file;
   getline(cin, file);
   
   midi_trk midi_file(file);

   string secret = midi_file.reveal();   
   
   cout << "\nThe secret is: " << secret << endl;

   return 0;
}
