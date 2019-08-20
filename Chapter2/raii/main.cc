#include "thread_guard.h"
#include "windows.h"
#include <cmath>
#include <iostream>

struct func
{
    int &m_i;
    func(int &i) : m_i(i) {}

    void operator()()
    {
        for (unsigned j = 0; j < 1000; ++j)
        {
            std::cout << std::sqrt(m_i++) << std::endl;
        }
    }
};

void throw_exception();
void f();

int main(int argc, char **argv)
{
    f();
    return 0;
}

/**
 * throw: 
 * */
void throw_exception()
{
    // Unhandled exception call std::terminate()
    // and still kill sub thread
    throw std::exception();
}

void f()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    boost::thread t(my_func);
    thread_guard tg(t);

    boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
    try
    {
        throw_exception();
    }
    catch (std::exception &e)
    {
        std::cout << "exception handled" << std::endl;
    }
    std::cout << "f threading about to terminated.." << std::endl;
}