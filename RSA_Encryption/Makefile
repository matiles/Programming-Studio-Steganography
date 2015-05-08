all: Circuit.o TruthTable.o Gate.o hill_climber.o
	g++-4.7 -std=c++11 Circuit.o TruthTable.o Gate.o hill_climber.o -o proj3 -lfltk -lfltk_images -w
Circuit.o: Circuit.cpp Circuit.h
	g++-4.7 -std=c++11 -c Circuit.cpp
TruthTable.o: TruthTable.cpp 
	g++-4.7 -std=c++11 -c TruthTable.cpp
Gate.o: Gate.cpp 
	g++-4.7 -std=c++11 -c Gate.cpp
hill_climber.o: hill_climber.cpp 
	g++-4.7 -std=c++11 -c hill_climber.cpp -w
clean:
	rm *.o 

