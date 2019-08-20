/**
 * 在C++中，向线程对象传递参数可以通过三种方式进行：
 * 1. 在构造thread对象时，第一个参数为函数指针，第二个参数开始就是参数了
 *  注意在这种传递方式中，参数是按值传递的，就算函数的参数要求参数为引用
 *  也是按值传递的，如果需要按引用传递，需要std::ref处理一下
 * 2. 在构造thread对象时，可以通过对象的成员函数来构造thread，第一个参数
 *  是成员函数的指针，第二个参数是成员函数的对象的指针（地址），从第三个参
 *  数开始就可以是真正的参数了，注意，这里的参数如果不加处理，也是按值传递的
 * 3. 某些不能复制但能传递的对象，如std::unique_ptr，可以使用移动构造函数来
 *  构造thread对象，在源对象是临时对象的场合，移动操作是自动的，在源对象是
 *  命名对象的场合，必须使用std::move函数处理
 * */

#include <boost/thread/thread.hpp>
#include <iostream>
#include <utility>

class X
{
public:
    void f(const std::string &str)
    {
        std::cout << "f(const std::string&) is called.." << std::endl;
        std::cout << str << std::endl;
    }

    void f(std::string &&str)
    {
        std::cout << "f(std::string&&) is called.." << std::endl;
        std::cout << str << std::endl;
    }
};

int main(int argc, char **argv)
{
    X x;
    std::string str("123");
    // 拿lambda包一下，否则就要写函数指针指定调用哪个f
    auto f1 = [&x, &str]() -> void { x.f(str); };
    auto f2 = [&x, &str]() -> void { x.f(std::move(str)); };
    auto f3 = [&x]() -> void { x.f("123"); };
    boost::thread t1(f1);
    boost::thread t2(f2);
    boost::thread t3(f3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}