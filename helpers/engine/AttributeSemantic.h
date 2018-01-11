#pragma once

enum class AttributeSemantic : int {
    none = 0,

    position = (1 << 0),
    color = (1 << 1),
    texCoord = (1 << 2),
    normal = (1 << 3),

    all = position | color | texCoord | normal
};
