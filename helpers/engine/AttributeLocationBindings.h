#pragma once

#include <unordered_map>

#include "../../three/shader/ShaderProgram.h"

#include "IAttributeLocationBindings.h"

class AttributeLocationBindings : public IAttributeLocationBindings {
public:
    AttributeLocationBindings();

    void addAttribute(const three::AttributeInfo& attributeInfo);
    void addAttributes(const three::ShaderProgram* program);

    bool hasAttribute(AttributeSemantic semantic) const override;
    const three::AttributeInfo& getAttributeInfo(AttributeSemantic semantic) const override;

private:
    std::unordered_map<std::string, AttributeSemantic> nameToSemantic;
    std::unordered_map<AttributeSemantic, three::AttributeInfo> attributes;
};
