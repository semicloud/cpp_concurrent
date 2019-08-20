#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

/**
 * this program verify mutex in c++ programming language
 * compile command (on Ubuntu): 
 * g++ -pthread -std=c++0x compare.cc -o compare.out
 * */

class foo
{
public:
    void fill_vec(int first, int last)
    {
        for (int i = first; i <= last; ++i)
            m_vec.push_back(i);
    }

    int vec_size()
    {
        return m_vec.size();
    }

private:
    std::vector<int> m_vec;
};

class foo_thread_safe
{
public:
    void fill_vec(int first, int last)
    {
        std::lock_guard<std::mutex> guard(m_fill_mutex);
        for (int i = first; i <= last; ++i)
            m_vec.push_back(i);
    }

    int vec_size()
    {
        return m_vec.size();
    }

private:
    std::vector<int> m_vec;
    std::mutex m_fill_mutex;
};

int main(int argc, char **argv)
{
    // run 30 times, to verify that if every time output is 2000
    // a race condition is occur if not
    const unsigned run_time = 30;

    // thread not safe
    // for (int i = 0; i <= run_time; ++i)
    // {
    //     foo f;
    //     std::thread t1(&foo::fill_vec, &f, 1, 1000);
    //     std::thread t2(&foo::fill_vec, &f, 1001, 2000);
    //     t1.join();
    //     t2.join();
    //     std::cout << f.vec_size() << std::endl;
    // }

    // may be thread safe
    for (int i = 0; i <= run_time; ++i)
    {
        foo_thread_safe f;
        std::thread t1(&foo_thread_safe::fill_vec, &f, 1, 1000);
        std::thread t2(&foo_thread_safe::fill_vec, &f, 1001, 2000);
        t1.join();
        t2.join();
        std::cout << f.vec_size() << std::endl;
    }
    return 0;
}