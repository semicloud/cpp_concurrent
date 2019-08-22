#include "hierarchical_mutex.h"

int main(int argc, char **argv)
{
    hierarchical_mutex m(5000);
    std::cout << m << std::endl;
    return 0;
}