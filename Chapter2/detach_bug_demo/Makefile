CC=g++.exe
BOOST_LIB=C:\SDK\boost_1_69_0\bin\gcc_all_static\lib
BOOST_INCLUDE=C:\SDK\boost_1_69_0
BOOST_THREAD=boost_thread-mgw82-mt-s-x32-1_69

detach_bug_demo.exe: detach_bug_demo.o
	$(CC) detach_bug_demo.o -Wall -L$(BOOST_LIB) -l$(BOOST_THREAD) -o detach_bug_demo.exe

detach_bug_demo.o: detach_bug_demo.cc
	$(CC) -std=c++0x -I$(BOOST_INCLUDE) -c detach_bug_demo.cc 