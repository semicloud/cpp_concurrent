#include <boost/thread/thread.hpp>
#include <boost/program_options.hpp>
#include <algorithm>
#include <chrono>
#include <iterator>
#include <iostream>
#include <numeric>
#include <malloc.h>

template <typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T &result)
    {
        result = std::accumulate(first, last, result);
    }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    unsigned long const length = std::distance(first, last);
    if (!length)
        return init;

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread) / min_per_thread;
    // BOOST_LOG_TRIVIAL(debug) << "max_thread: " << max_threads;

    unsigned long const hardware_threads = boost::thread::hardware_concurrency();
    // BOOST_LOG_TRIVIAL(debug) << "hardware_concurrency: " << hardware_threads;
    unsigned long const num_threads =
        std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
    // BOOST_LOG_TRIVIAL(debug) << "num_threads: " << num_threads;
    unsigned long const block_size = length / num_threads;
    // BOOST_LOG_TRIVIAL(debug) << "block_size: " << block_size;

    std::vector<T> results(num_threads);
    std::vector<boost::thread> threads(num_threads - 1);

    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_threads - 1); ++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size); // 将迭代器向前移动n个位置
        threads[i] = boost::thread(
            accumulate_block<Iterator, T>(),
            block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&boost::thread::join));

    return std::accumulate(results.begin(), results.end(), init);
}

typedef unsigned long long num;

std::vector<num> get_data(num t);
void run_single_thread(num t);
void run_multiple_threads(num t);

std::vector<num> get_data(num t)
{
    std::vector<num> vec;
    for (num i = 1; i < t + 1; ++i)
        vec.push_back(i);
    return vec;
}

void run_single_thread(num t)
{
    std::vector<num> data = get_data(t);
    num sum = std::accumulate(data.begin(), data.end(), 0);
    std::cout << "sum: " << std::endl;
}

void run_multiple_threads(num t)
{
    std::vector<num> data = get_data(t);
    num sum = parallel_accumulate<std::vector<num>::iterator, num>(data.begin(), data.end(), 0);
    std::cout << "sum: " << std::endl;
}

int main(int argc, char **argv)
{
    num t = 100000;
    // boost::program_options::options_description desc("All allowed options:");
    // desc.add_options()("help", "produce help messages")("t", boost::program_options::value<num>(&t), "max_num")("s", "run in single thread mode")("m", "run in multi-thread mode");
    // boost::program_options::variables_map vm;
    // boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).run(), vm);
    // boost::program_options::notify(vm);
    const auto start = std::chrono::high_resolution_clock::now();
    // if (vm.count("s"))
    // {
        // run_single_thread(t);
    // }
    // if (vm.count("m"))
    // {
        run_multiple_threads(t);
    // }

    const auto stop = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

    std::cout << "Cost seconds: " << duration << " miliseconds.." << std::endl;
    return 0;
}