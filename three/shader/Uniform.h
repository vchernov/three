#pragma once

#include <stdexcept>

namespace three
{

template<typename T>
class Uniform
{
public:
    explicit Uniform(int location)
        :
        location(location)
    {
        if (location < 0)
        {
            throw std::runtime_error("Invalid uniform location");
        }
    }

    virtual ~Uniform() = default;

    virtual void set(T value)
    {
        update(location, value);
    }

    static void update(int location, T value);

private:
    int location;
};

}
