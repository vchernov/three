#include "Scene.h"

void Scene::draw() const
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    root.draw(modelMatrix);
}
