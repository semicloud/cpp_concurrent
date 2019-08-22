#ifndef HIERARCHICAL_MUTEX_H_
#define HIERARCHICAL_MUTEX_H_

#include <iostream>
#include <mutex>

class hierarchical_mutex
{
    friend std::ostream& operator<<(std::ostream& ,const hierarchical_mutex&);
private:
    std::mutex internal_mutex;
    const unsigned long hierarchy_value;
    const unsigned long preivous_hierarchy_value;
    static thread_local unsigned long this_thread_hierarchy_value;

    void check_for_hierarchy_violation();
    void update_hierarchy_value();

public:
    explicit hierarchical_mutex(unsigned long value) : hierarchy_value(value), preivous_hierarchy_value(0) {}
    void lock();
    void unlock();
    bool try_lock();
};

#endif
