
#include <thread>
#include <mutex>
#include <iostream>
#include <cstdio>

std::mutex m;

void cout_thread_safe(const std::string &str)
{
    std::lock_guard<std::mutex> guard(m);
    std::cout << str << std::endl;
}

int main(int argc, char **argv)
{
    std::mutex m1, m2;
    std::thread t1([&m1, &m2]() {
        cout_thread_safe("1. Acquiring m1.");
        m1.lock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        cout_thread_safe("1. Acquiring m2.");
        m2.lock();
    });

    std::thread t2([&m1, &m2]() {
        cout_thread_safe("2. Acquiring m1.");
        m1.lock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        cout_thread_safe("2. Acquiring m2.");
        m2.lock();
    });

    t1.join();
    t2.join();

    return 0;
}
