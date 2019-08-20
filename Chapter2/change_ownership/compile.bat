g++.exe -std=c++0x -Wall -c -IC:\SDK\boost_1_69_0 change_ownership.cc
g++.exe change_ownership.o -LC:\SDK\boost_1_69_0\bin\gcc_all_static\lib -lboost_thread-mgw82-mt-s-x32-1_69 -o change_ownership.exe