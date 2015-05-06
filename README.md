315-Project-4
=============

Overview
--------

  This repository contains 4 tools.
  
  1. RSA Encryption
  2. Cryptanalysis of RSA
  3. Steganography (1-LSB BMP and tracks on midi)
  4. Steganalysis and countermeasure

  * munchkin_steg is a command line tool for embeding messages in the least significant bit of a bmp file.
  * scarecrow_steg is a command line tool for embeding messages in tracks of a midi file.
  * Both directories contain their respective attacks and countermeasures.

Development
-----------

  In this project we used the scrum methodology for managing product development. Specifically we used taiga.io as our
  project management platform. 
  
  taiga is here: https://taiga.io/

Downloading and running the tools
---------------------------------

  Download source code from this repository.

  The below make files do not run the actual tools. They are make files for running unit tests using googles gtest version   1.7.
  
  [http://code.google.com/p/googletest/](http://code.google.com/p/googletest/)

  * Makefile.munchkin_steg is for running tests for munchkin_steg
  * Makefile.scarecrow_steg is for running tests for scarecrow_steg
  

To run munchkin_steg go to the munchkin_steg directory and run 'make all'.
  * To embed execute     ./bmp_lsb_embed
  * To extract execute   ./bmp_lsb_extract
  * To attack execute    ./bmp_attack

To run scarecrow_steg go to the scarecrow_steg directory and run 'make all'.
  * To embed execute     ./midi_embed
  * To extract execute   ./midi_extract
  * To attack execute    ./midi_attack


Acknowledgments
---------------

This project uses Craig Stuart's C++ library for parsing Standard MIDI Files.

[http://midifile.sapp.org/](http://midifile.sapp.org/)

This project uses Paul Macklin's C++ Bitmap Library.

[http://easybmp.sourceforge.net/](http://easybmp.sourceforge.net/)
