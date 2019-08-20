CC=g++
CFLAGS=-std=c++0x -Wall

test_boost_log: test_boost_log.o
	$(CC) test_boost_log.o -lboost_log -pthread -o test_boost_log.out

test_boost_log.o: test_boost_log.cc
	$(CC) $(CFLAGS) -DBOOST_ALL_DYN_LINK -c test_boost_log.cc