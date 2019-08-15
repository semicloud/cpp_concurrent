
CC=g++.exe
BOOST_LIB=C:\SDK\boost_1_69_0\bin\gcc_all_static\lib
BOOST_INCLUDE=C:\SDK\boost_1_69_0
BOOST_THREAD=boost_thread-mgw82-mt-s-x32-1_69

run_background_task.exe: run_background_task.o
	$(CC) run_background_task.o -Wall -L$(BOOST_LIB) -l$(BOOST_THREAD) -o run_background_task.exe

run_background_task.o: run_background_task.cc background_task.h
	$(CC) -std=c++0x -I$(BOOST_INCLUDE) -c run_background_task.cc 