#include <boost/thread/thread.hpp>
#include <iostream>

void hello();

int main(int argc, char **argv)
{
    boost::thread t(hello);
    t.join();
    return 0;
}

void hello()
{
    std::cout << "Hello Concurrent World!\n";
}
