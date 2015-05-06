// Creation Date: Tue May 5, 2015
// Filename:      midi_trk.cpp
// Syntax:        C++
// Description:   Embeding messages in MIDI file.

#include "midi_trk.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
   cout << "\nHello from midi_embed" << endl;

   cout << "This program only excepts midi files (ie .mid)" << endl;
   cout << "Please provide a cover midi for your secret message (eg. a_regular_file.mid): ";
   string file;
   getline(cin, file);
   
   string outfile;
   cout << "Provide the output file to hide your secret message (eg. message_file.mid): ";
   getline(cin, outfile);

   midi_trk midi_file(file);
   
   //ask user what message they would like to hide
   string secret_message;
   cout << "Input secret message: ";
   getline(cin, secret_message);
   
   if(midi_file.hide(secret_message, outfile)){
      cout << "\nSuccessfully wrote message in... " << outfile << endl;
   }
   else{
      cout << "Something went wrong." << endl;
   }
   
   return 0;
}
