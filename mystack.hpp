#pragma once

#include <stdexcept>
#include <vector>

template<typename T>
class Stack
{
private:
    int top_;

    size_t capacity;

    std::vector<T> data;
public:
    explicit Stack(const size_t &capacity) : top_(bottom), capacity(capacity), data(std::vector<T> (capacity))
    {}
    void push(const T& value)
    {
        overflow_check();
        top_++;
        data[top_] = value;
    }
    void pop()
    {
        underflow_check();
        top_--;
    }
    T top()
    {
        empty_check();
        return data[top_];
    }
    constexpr size_t size() const
    {
        return static_cast<size_t> (top_ + 1);
    }
    constexpr bool empty() const
    {
        return (top_ == bottom) ? true : false;
    }
private:
    static constexpr int bottom = -1;

    void overflow_check() const
    {
        if ( size() == capacity ) throw std::overflow_error("Stack overflow");
    }
    void underflow_check() const
    {
        if ( empty() ) throw std::underflow_error("Stack is empty");
    }
    void empty_check() const
    {
        if ( empty() ) throw std::logic_error("Stack is empty");
    }
};
