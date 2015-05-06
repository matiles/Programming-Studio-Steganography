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
  string is_hiding_str();  //attack
  int mess_up_message();
  
  int isValid(string file);
  int how_many_chars();
  string get_name();
};

#endif