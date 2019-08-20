#include "stack_thread_safe.h"

// g++ -std=c++0x -Wall -pthread stack_thread_safe.cc -o stack_thread_safe.out
int main(int argc, char **argv)
{
    thread_safe_stack<int> tss;
    return 0;
}