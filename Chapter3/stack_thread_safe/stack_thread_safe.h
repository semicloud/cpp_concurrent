#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack : std::exception
{
    const char *what() const throw();
};

template <typename T>
class thread_safe_stack
{
private:
    std::stack<T> m_data;
    mutable std::mutex m_mutex;

public:
    thread_safe_stack() {}
    thread_safe_stack(const thread_safe_stack &other)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_data = other.m_data;
    }
    thread_safe_stack &operator=(const thread_safe_stack &) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_data.push(new_value);
    }

    // this function may throw exception
    void pop(T &value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_data.empty())
            throw empty_stack();
        value = m_data.top();
        m_data.pop();
    }

    // this function may throw exception
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_data.empty())
            throw empty_stack();
        const std::shared_ptr<T> p(std::make_shared<T>(m_data.top()));
        m_data.pop();
        return p;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_data.empty();
    }
};