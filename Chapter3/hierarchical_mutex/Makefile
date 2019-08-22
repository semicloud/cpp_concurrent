use_hierarchical_mutex.out: use_hierarchical_mutex.o hierarchical_mutex.o
	g++ use_hierarchical_mutex.o hierarchical_mutex.o -o use_hierarchical_mutex.out

use_hierarchical_mutex.o: use_hierarchical_mutex.cc
	g++ -c -std=c++0x -pthread use_hierarchical_mutex.cc

hierarchical_mutex.o: hierarchical_mutex.cc hierarchical_mutex.h
	g++ -c -std=c++0x -pthread hierarchical_mutex.cc;

Clean:
	rm -f *.o
	rm -f *.out