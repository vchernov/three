#pragma once

#include "Uniform.h"

#include <memory>

namespace three {

class SmartShaderProgram;

class IDeferredUniform {
public:
    virtual ~IDeferredUniform() = default;

    virtual void apply() = 0;
};

template<typename T>
class SmartUniform : public Uniform<T>, public IDeferredUniform {
public:
    SmartUniform(int location, std::weak_ptr<SmartShaderProgram> owner)
        :
        Uniform(location),
        owner(std::move(owner)) {
    }

    void set(T value) override {
        this->value = value;

        auto program = owner.lock();
        if (!program) {
            throw std::runtime_error("Program destroyed");
        }

        if (program->isActive()) {
            Uniform<T>::set(value);
        }
    }

    void apply() override {
        auto program = owner.lock();
        if (!program) {
            throw std::runtime_error("Program destroyed");
        }

        if (!program->isActive()) {
            throw std::runtime_error("Owner program is not current");
        }

        Uniform<T>::set(value);
    }

private:
    T value;
    std::weak_ptr<SmartShaderProgram> owner;
};

}
