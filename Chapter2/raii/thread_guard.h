/**
 * 本程序展示了资源获取即初始化（Resource Acquisition Is Initialization）
 * 的惯用方法，该方法用于C++并行程序中主线程必须等待子线程完成的情况，无论主
 * 线程是否抛出异常或异常终止，主线程必须等待子线程运行完成。实现方法就是用一
 * 个类包住子线程，并在这个类的析构函数中join
 */

#ifndef THREAD_GUARD_H
#define THREAD_GUARD_H

#include <boost/thread/thread.hpp>

class thread_guard
{
public:
    explicit thread_guard(boost::thread &t) : m_thread(t)
    {
        if (!m_thread.joinable())
            throw std::logic_error("No thread");
    }
    ~thread_guard();
    // 不允许拷贝
    thread_guard(const thread_guard &) = delete;
    // 不允许赋值
    thread_guard &operator=(const thread_guard &) = delete;

private:
    boost::thread &m_thread;
};

#endif