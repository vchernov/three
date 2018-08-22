#pragma once

namespace three
{

class IDeferredUniform
{
public:
    virtual ~IDeferredUniform() = default;

    virtual void apply() = 0;
};

}
