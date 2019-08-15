demo_mt.exe: demo_mt.o
	g++ demo_mt.o -Wall -LC:\SDK\boost_1_69_0\bin\gcc_all_static\lib -lboost_thread-mgw82-mt-s-x32-1_69 -o demo_mt.exe

demo_mt.o: demo_mt.cc
	g++ -std=c++0x -IC:\SDK\boost_1_69_0 -c demo_mt.cc