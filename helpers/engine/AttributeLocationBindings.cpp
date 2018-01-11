#include "AttributeLocationBindings.h"

#include <cassert>

#include "AttributeName.h"

using namespace three;

AttributeLocationBindings::AttributeLocationBindings() {
    nameToSemantic[AttributeName::position] = AttributeSemantic::position;
    nameToSemantic[AttributeName::color] = AttributeSemantic::color;
    nameToSemantic[AttributeName::texCoord] = AttributeSemantic::texCoord;
    nameToSemantic[AttributeName::normal] = AttributeSemantic::normal;
}

void AttributeLocationBindings::addAttribute(const AttributeInfo& attributeInfo) {
    auto semantic = nameToSemantic[attributeInfo.name];
    attributes[semantic] = attributeInfo;
}

void AttributeLocationBindings::addAttributes(const three::ShaderProgram* program) {
    assert(program != nullptr);
    auto attributes = program->getActiveAttributes();
    for (const auto& attribute : attributes) {
        addAttribute(attribute);
    }
}

bool AttributeLocationBindings::hasAttribute(AttributeSemantic semantic) const {
    return attributes.find(semantic) != attributes.end();
}

const AttributeInfo& AttributeLocationBindings::getAttributeInfo(AttributeSemantic semantic) const {
    auto it = attributes.find(semantic);
    if (it == attributes.end()) {
        throw std::runtime_error("Attribute info not found");
    }
    return it->second;
}
