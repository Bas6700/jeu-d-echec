echecs: echecs.cc Jeu.o piece.o Echiquier.o Square.o
	g++ -std=c++11 echecs.cc -o echecs Jeu.o Square.o piece.o Echiquier.o -Wall -Wextra

Jeu.o: Jeu.cc 
	g++ -std=c++11 -o Jeu.o -c Jeu.cc -Wall -Wextra

Echiquier.o: Echiquier.cc 
	g++ -std=c++11 -o Echiquier.o -c Echiquier.cc -Wall -Wextra

piece.o: piece.cc 
	g++ -std=c++11 -o piece.o -c piece.cc -Wall -Wextra

Square.o : Square.cc
	g++ -std=c++11 -o Square.o -c Square.cc -Wall -Wextra

clear:
	rm *.o
	rm echecs

Doxy: Doxyfile
	doxygen Doxyfile