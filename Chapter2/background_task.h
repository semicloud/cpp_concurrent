#include <boost/thread/thread.hpp>
#include <iostream>
#include <cstdlib>

class background_task
{
public:
    background_task() = default;

    ~background_task() = default;

    void operator()()
    {
        boost::mutex mtx;
        boost::lock_guard<boost::mutex> lock(mtx);
        const int max_sleep = 6;
        srand(time(0));
        const int sleep_time = (rand() % max_sleep) + 1;
        std::cout << "child thread " << boost::this_thread::get_id()
                  << " will running " << sleep_time << " seconds.." << std::endl;
        boost::this_thread::sleep(boost::posix_time::seconds(sleep_time));
        std::cout << "child thread terminated.." << std::endl;
    }
};
