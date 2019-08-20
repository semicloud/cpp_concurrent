/**
 * 该程序展示了在thread对象之间传递线程所有权的过程
 * */

#include <boost/thread/thread.hpp>
#include <iostream>
#include <string>
#include <utility>

void some_function();

void some_other_function();

void some_function()
{
    while (true)
    {
        std::cout << "some_function under thread " << boost::this_thread::get_id() << std::endl;
        boost::this_thread::sleep_for(boost::chrono::seconds(2));
    }
}

void some_other_function()
{
    while (true)
    {
        std::cout << "some_other_function under thread " << boost::this_thread::get_id() << std::endl;
        boost::this_thread::sleep_for(boost::chrono::seconds(3));
    }
}

// g++.exe -std=c++0x -Wall -c -IC:\SDK\boost_1_69_0 change_ownership.cc
// g++.exe change_ownership.o -LC:\SDK\boost_1_69_0\bin\gcc_all_static\lib -lboost_thread-mgw82-mt-s-x32-1_69 -o change_ownership.exe
int main(int argc, char **argv)
{
    std::cout << boost::thread::hardware_concurrency() << std::endl;
    boost::thread t1(some_function);
    boost::thread t2(some_other_function);
    std::cout << "t2 id:" << t2.get_id() << std::endl;
    boost::this_thread::sleep_for(boost::chrono::seconds(3));
    boost::thread t3 = std::move(t2);
    std::cout << "t3 id:" << t3.get_id() << std::endl; // t2 移动到 t3, ID肯定不变
    // boost::thread t2 = std::move(t1);

    // t2.join();

    // t3.join();
    // t1 = boost::thread(some_other_function);
    // t1.join();
    boost::this_thread::sleep_for(boost::chrono::seconds(20));
    // 睡20s后，把t3移动到t1，由于t1已经有线程，因此该赋值将结束程序
    std::cout << "Terminated..?" << std::endl;
    t1 = std::move(t3);
    return 0;
}