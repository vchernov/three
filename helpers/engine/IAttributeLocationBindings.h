#pragma once

#include "../../three/shader/AttributeInfo.h"

#include "AttributeSemantic.h"

class IAttributeLocationBindings {
public:
    virtual ~IAttributeLocationBindings() = default;

    virtual bool hasAttribute(AttributeSemantic semantic) const = 0;
    virtual const three::AttributeInfo& getAttributeInfo(AttributeSemantic semantic) const = 0;
};
