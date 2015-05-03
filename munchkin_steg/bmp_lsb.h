#ifndef BMP_LSB_
#define BMP_LSB_

#include <iostream>
#include <string>

using namespace std;

// lsb on bmp.
class bmp_lsb {
  private:
    string image_name;
    unsigned int bytes_in_image;

  public:

  // Constructor
  bmp_lsb(string file);
  bmp_lsb();

  ~bmp_lsb();

  string reveal();
  int hide(string message, string output_file);
  void is_hiding_something();  //attack
  
  int isValid(string file);
  int how_many_chars();
  string get_name();
};

#endif