#pragma once

#include <cassert>

template<typename T>
class BufferHolder
{
public:
    explicit BufferHolder(T* buffer)
        : buffer(buffer)
    {
        assert(buffer != nullptr);
    }

    virtual ~BufferHolder()
    {
        delete[] buffer;
    }

    BufferHolder(const BufferHolder&) = delete;
    BufferHolder& operator=(const BufferHolder&) = delete;

    BufferHolder(BufferHolder&& other) noexcept
        : buffer(other.buffer)
    {
        other.buffer = nullptr;
    }

    BufferHolder& operator=(BufferHolder&& other) noexcept
    {
        buffer = other.buffer;
        other.buffer = nullptr;
        return *this;
    }

    const T* getBuffer() const
    {
        return buffer;
    }

private:
    T* buffer;
};
