CC=g++.exe
CFLAGS= -IC:\SDK\boost_1_69_0 -std=c++0x -c
BOOST_LIB = C:\SDK\boost_1_69_0\bin\gcc_all_static\lib
BOOST_THREAD_LIB = boost_thread-mgw82-mt-s-x32-1_69

main.exe: main.o thread_guard.o
	$(CC) main.o thread_guard.o -L$(BOOST_LIB) -l$(BOOST_THREAD_LIB) -o main.exe

thread_guard.o: thread_guard.cc thread_guard.h
	$(CC) $(CFLAGS) thread_guard.cc

main.o: main.cc
	$(CC) $(CFLAGS) main.cc

Clean:
	del *.o
	del *.exe