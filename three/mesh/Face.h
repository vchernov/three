#pragma once

namespace three
{

template<typename T, int indexCount>
struct Face
{
    using ValueType = T;

    T indices[indexCount];

    static int getIndexCount()
    {
        return indexCount;
    }
};

}
