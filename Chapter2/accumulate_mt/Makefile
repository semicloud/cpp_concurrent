accumulate.exe: accumulate.o
	g++.exe accumulate.o -LC:\SDK\boost_1_69_0\bin\gcc_all_static\lib -lboost_thread-mgw82-mt-s-x32-1_69 -lboost_program_options-mgw82-mt-s-x32-1_69 -o accumulate.exe

accumulate.o: accumulate.cc
	g++.exe -std=c++0x -Wall -c -IC:\SDK\boost_1_69_0 accumulate.cc