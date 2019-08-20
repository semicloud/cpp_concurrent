#include <boost/log/trivial.hpp>

int main(int argc, char **argv)
{
    BOOST_LOG_TRIVIAL(debug) << "Hello, Boost!";
    return 0;
}