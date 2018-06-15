#include "BoundingBox.h"

BoundingBox::BoundingBox()
    :
    pointFrontBottomLeft(glm::vec3(std::numeric_limits<float>::max())),
    pointBackTopRight(glm::vec3(-std::numeric_limits<float>::max())) {
}

void BoundingBox::encapsulate(float x, float y, float z) {
    pointFrontBottomLeft.x = fmin(x, pointFrontBottomLeft.x);
    pointFrontBottomLeft.y = fmin(y, pointFrontBottomLeft.y);
    pointFrontBottomLeft.z = fmin(z, pointFrontBottomLeft.z);
    pointBackTopRight.x = fmax(x, pointBackTopRight.x);
    pointBackTopRight.y = fmax(y, pointBackTopRight.y);
    pointBackTopRight.z = fmax(z, pointBackTopRight.z);
}

void BoundingBox::encapsulate(const glm::vec3& point) {
    encapsulate(point.x, point.y, point.z);
}

void BoundingBox::encapsulate(const BoundingBox& other) {
    encapsulate(other.pointFrontBottomLeft);
    encapsulate(other.pointBackTopRight);
}

glm::vec3 BoundingBox::getSize() const {
    return pointBackTopRight - pointFrontBottomLeft;
}

glm::vec3 BoundingBox::getCenter() const {
    return pointFrontBottomLeft + getSize() * 0.5f;
}
