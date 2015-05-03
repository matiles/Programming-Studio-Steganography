// This sample shows how to write a more complex unit test for a class
// that has multiple member functions.
//
// Usually, it's a good idea to have one test for each method in your
// class.  You don't have to do that exactly, but it helps to keep
// your tests organized.  You may also throw in additional tests as
// needed.

#include "bmp_lsb.h"
#include "gtest/gtest.h"

// Testing bmp_lsb class.

// Tests isValid.
TEST(bmp_lsb, isValid) {
  string invalid_file = "image.bmp";
  string valid_file = "roadGrey.bmp";

  bmp_lsb inval_file;
  bmp_lsb val_file;

  int inval = inval_file.isValid(invalid_file);
  int val = val_file.isValid(valid_file);

  EXPECT_EQ(0, inval);
  EXPECT_EQ(1, val);
}

// Tests the hide method.
TEST(bmp_lsb, hide) {
  
  string cover_file = "roadGrey.bmp";
  string outfile = "roadGrey_secret.bmp";
  string secret_message = "Top secret message";
  
  bmp_lsb duck_file(cover_file);  

  EXPECT_EQ(1, duck_file.hide(secret_message, outfile));
}

// Tests the reveal method.
TEST(bmp_lsb, reveal) {

  string outfile = "roadGrey_secret.bmp";
  string secret_message = "Top secret message";
  
  bmp_lsb duck_file(outfile);
  string secret = duck_file.reveal();

  EXPECT_EQ( 0, strcmp(secret.c_str(), secret_message.c_str()) );
}

