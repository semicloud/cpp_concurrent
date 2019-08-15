#include "background_task.h"

int main(int argc, char** argv){
    background_task task;
    boost::thread my_thread(task);
    boost::thread your_thread([&task](){
        background_task t;
        t();
    });
    my_thread.join();
    your_thread.join();
    return 0;
}