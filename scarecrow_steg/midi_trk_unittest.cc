// This sample shows how to write a more complex unit test for a class
// that has multiple member functions.
//
// Usually, it's a good idea to have one test for each method in your
// class.  You don't have to do that exactly, but it helps to keep
// your tests organized.  You may also throw in additional tests as
// needed.

#include "midi_trk.h"
#include "gtest/gtest.h"

// Testing bmp_lsb class.

// Tests isValid.
TEST(midi_trk, isValid) {
  string invalid_file = "image.bmp";
  string valid_file = "twinkle.mid";

  midi_trk inval_file;
  midi_trk val_file;

  int inval = inval_file.isValid(invalid_file);
  int val = val_file.isValid(valid_file);

  EXPECT_EQ(0, inval);
  EXPECT_EQ(1, val);
}

// Tests the hide method.
TEST(midi_trk, hide) {
  
  string cover_file = "twinkle.mid";
  string outfile = "twinkle_out.mid";
  string secret_message = "Top secret message";
  
  midi_trk twinkle_file(cover_file);  

  EXPECT_EQ(1, twinkle_file.hide(secret_message, outfile));
}

// Tests the reveal method.
TEST(midi_trk, reveal) {

  string outfile = "twinkle_out.bmp";
  string secret_message = "Top secret message";
  
  midi_trk twinkle_out_file(outfile);
  string secret = twinkle_out_file.reveal();

  EXPECT_EQ( 0, strcmp(secret.c_str(), secret_message.c_str()) );
}

