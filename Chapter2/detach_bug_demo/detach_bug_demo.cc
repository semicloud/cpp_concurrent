#include <boost/thread/thread.hpp>
#include <iostream>
#include <Windows.h>

struct func
{
    int &i;
    func(int &i_) : i(i_) {}
    void operator()()
    {
        for (unsigned j = 0; j < 1000000; ++j)
        {
            i++;
            std::cout << i << std::endl;
        }
    }
};

void oops()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    // boost::this_thread::sleep(boost::posix_time::seconds(2));
    boost::thread my_thread(my_func);
    my_thread.detach(); // detach的话主线程结束了，子线程也就结束了
    while(true);
    // Sleep(5000);
    // std::cout << "oops is over.." << std::endl;
}

int main(int argc, char **argv)
{
    oops();
}