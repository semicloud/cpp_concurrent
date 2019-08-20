#include "thread_guard.h"

thread_guard::~thread_guard()
{
    // if (m_thread.joinable())
    // {
        m_thread.join();
    // }
}