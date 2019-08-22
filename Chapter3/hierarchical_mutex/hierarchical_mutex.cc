#include "hierarchical_mutex.h"
#include <climits>

thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value = ULONG_MAX;

std::ostream &operator<<(std::ostream &os, const hierarchical_mutex &m)
{
    os << "hierarchical mutex with level " << m.this_thread_hierarchy_value;
    return os;
}