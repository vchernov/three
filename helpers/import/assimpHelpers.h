#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../three/mesh/VertexBuffer.h"
#include "../../three/mesh/IndexBuffer.h"
#include "../../three/mesh/AttributeBindings.h"
#include "../../three/TypeInfo.h"

unsigned int* importTriangleIndices(const aiMesh* mesh);

void uploadIndices(const aiMesh* mesh, unsigned int* triangleIndices, three::IndexBuffer& indexBuffer);

three::AttributeBindings uploadVertices(const aiMesh* mesh, three::VertexBuffer& vertexBuffer);
