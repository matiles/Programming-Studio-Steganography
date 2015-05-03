# makefile

all: midi_embed midi_extract

Binasc.o: Binasc.h Binasc.cpp
	g++-4.7 -std=c++11 -c Binasc.cpp

MidiMessage.o: MidiMessage.h MidiMessage.cpp Binasc.h 
	g++-4.7 -std=c++11 -c MidiMessage.cpp

MidiEvent.o: MidiEvent.h MidiEvent.cpp MidiMessage.h
	g++-4.7 -std=c++11 -c MidiEvent.cpp

MidiEventList.o: MidiEventList.h MidiEventList.cpp MidiEvent.h
	g++-4.7 -std=c++11 -c MidiEventList.cpp

MidiFile.o: MidiFile.h MidiFile.cpp MidiEventList.h
	g++-4.7 -std=c++11 -c MidiFile.cpp

midi_trk.o: midi_trk.cpp midi_trk.h MidiFile.h
	g++-4.7 -std=c++11 -c midi_trk.cpp

#  MidiFile.o MidiFile.o MidiEvent.o MidiEventList.o MidiMessage.o Binasc.o

midi_embed.o: midi_embed.cpp midi_trk.h
	g++-4.7 -std=c++11 -c midi_embed.cpp

midi_extract.o: midi_extract.cpp midi_trk.h
	g++-4.7 -std=c++11 -c midi_extract.cpp

midi_embed: midi_embed.o midi_trk.o MidiFile.o MidiEventList.o MidiEvent.o MidiMessage.o Binasc.o
	g++-4.7 -std=c++11 -o midi_embed midi_embed.o midi_trk.o MidiFile.o MidiEventList.o MidiEvent.o MidiMessage.o Binasc.o

midi_extract: midi_extract.o midi_trk.o MidiFile.o MidiEventList.o MidiEvent.o MidiMessage.o Binasc.o
	g++-4.7 -std=c++11 -o midi_extract midi_extract.o midi_trk.o MidiFile.o MidiEventList.o MidiEvent.o MidiMessage.o Binasc.o

#midi_embed: midi_embed.cpp midi_trk.o
#	g++-4.7 -std=c++11 -o midi_embed midi_embed.cpp midi_trk.o

#midi_extract: midi_extract.cpp midi_trk.o
#	g++-4.7 -std=c++11 -o midi_extract midi_extract.cpp midi_trk.o

clean:
	rm -f *.o
