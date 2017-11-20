#include "Shape.h"

#include "AttributeName.h"
#include "Face3.h"
#include "../../three/TypeInfo.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/normal.hpp>

#pragma warning(push)
#pragma warning(disable: 4244)
#pragma warning(disable: 4305)
#pragma warning(disable: 4838)
#define PAR_SHAPES_IMPLEMENTATION
#include "par_shapes.h"
#pragma warning(pop)

using namespace three;

GeometryBuffer Shape::createTriangle() {
    GeometryBuffer geometry;
    geometry.primitiveType = GL_TRIANGLES;

    std::vector<glm::vec3> vertices;
    const float offset = 0.5f;
    vertices.push_back({-offset, -offset, 0.0f});
    vertices.push_back({offset, -offset, 0.0f});
    vertices.push_back({offset, offset, 0.0f});

    std::vector<Face3> faces;
    faces.push_back({0, 1, 2});

    VertexBuffer pointsBuffer;
    pointsBuffer.bind();
    pointsBuffer.upload(vertices);
    pointsBuffer.addAttribute({AttributeName::position, TypeInfo<float>::dataType, 3, 0});
    geometry.vertexBuffers.emplace_back(std::move(pointsBuffer));

    geometry.indexBuffer.bind();
    geometry.indexBuffer.upload(faces.data(), TypeInfo<Face3::ValueType>::dataType, sizeof(Face3::ValueType), Face3::getIndexCount() * faces.size());

    return geometry;
}

GeometryBuffer Shape::createGrid(glm::vec3 point0, glm::vec3 point1, glm::vec3 point2, int rows, int columns) {
    GeometryBuffer geometry;
    geometry.primitiveType = GL_LINES;

    glm::vec3 end1 = point1 - point0;
    glm::vec3 end2 = point2 - point0;

    glm::vec3 offset1 = end1 / (float)columns;
    glm::vec3 offset2 = end2 / (float)rows;

    std::vector<glm::vec3> vertices;
    std::vector<unsigned short> indices;

    vertices.push_back(point0);
    vertices.push_back(point1);
    vertices.push_back(point2);
    vertices.push_back(point0 + end1 + end2);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(1);
    indices.push_back(3);

    for (int i = 1; i < rows; i++) {
        glm::vec3 vertex1 = point0 + offset2 * (float)i;
        glm::vec3 vertex2 = vertex1 + end1;

        vertices.push_back(vertex1);
        vertices.push_back(vertex2);

        indices.push_back(2 + i * 2);
        indices.push_back(2 + i * 2 + 1);
    }

    for (int j = 1; j < columns; j++) {
        glm::vec3 vertex1 = point0 + offset1 * (float)j;
        glm::vec3 vertex2 = vertex1 + end2;

        vertices.push_back(vertex1);
        vertices.push_back(vertex2);

        indices.push_back(rows * 2 + j * 2);
        indices.push_back(rows * 2 + j * 2 + 1);
    }

    VertexBuffer pointBuffer;
    pointBuffer.bind();
    pointBuffer.upload(vertices);
    pointBuffer.addAttribute({AttributeName::position, TypeInfo<float>::dataType, 3, 0});
    geometry.vertexBuffers.emplace_back(std::move(pointBuffer));

    geometry.indexBuffer.bind();
    geometry.indexBuffer.upload(indices.data(), TypeInfo<unsigned short>::dataType, sizeof(unsigned short), indices.size());

    return geometry;
}

GeometryBuffer Shape::createCube() {
    GeometryBuffer geometry;
    geometry.primitiveType = GL_TRIANGLES;

    par_shapes_mesh* mesh = par_shapes_create_cube();

    VertexBuffer pointBuffer;
    pointBuffer.bind();
    pointBuffer.upload(mesh->points, mesh->npoints, sizeof(float) * 3);
    pointBuffer.addAttribute({AttributeName::position, TypeInfo<float>::dataType, 3, 0});
    geometry.vertexBuffers.emplace_back(std::move(pointBuffer));

    par_shapes_compute_normals(mesh);

    VertexBuffer normalBuffer;
    normalBuffer.bind();
    normalBuffer.upload(mesh->normals, mesh->npoints, sizeof(float) * 3);
    normalBuffer.addAttribute({AttributeName::normal, TypeInfo<float>::dataType, 3, 0});
    geometry.vertexBuffers.emplace_back(std::move(normalBuffer));

    geometry.indexBuffer.bind();
    geometry.indexBuffer.upload(mesh->triangles, TypeInfo<PAR_SHAPES_T>::dataType, sizeof(PAR_SHAPES_T), mesh->ntriangles * 3);

    par_shapes_free_mesh(mesh);
    return geometry;
}

GeometryBuffer Shape::createSphere(int slices, int stacks) {
    GeometryBuffer geometry;
    geometry.primitiveType = GL_TRIANGLES;

    par_shapes_mesh* mesh = par_shapes_create_parametric_sphere(slices, stacks);

    VertexBuffer pointBuffer;
    pointBuffer.bind();
    pointBuffer.upload(mesh->points, mesh->npoints, sizeof(float) * 3);
    pointBuffer.addAttribute({AttributeName::position, TypeInfo<float>::dataType, 3, 0});
    geometry.vertexBuffers.emplace_back(std::move(pointBuffer));

    VertexBuffer normalBuffer;
    normalBuffer.bind();
    normalBuffer.upload(mesh->normals, mesh->npoints, sizeof(float) * 3);
    normalBuffer.addAttribute({AttributeName::normal, TypeInfo<float>::dataType, 3, 0});
    geometry.vertexBuffers.emplace_back(std::move(normalBuffer));

    VertexBuffer texCoordBuffer;
    texCoordBuffer.bind();
    texCoordBuffer.upload(mesh->tcoords, mesh->npoints, sizeof(float) * 2);
    texCoordBuffer.addAttribute({AttributeName::texCoord, TypeInfo<float>::dataType, 2, 0});
    geometry.vertexBuffers.emplace_back(std::move(texCoordBuffer));

    geometry.indexBuffer.bind();
    geometry.indexBuffer.upload(mesh->triangles, TypeInfo<PAR_SHAPES_T>::dataType, sizeof(PAR_SHAPES_T), mesh->ntriangles * 3);

    par_shapes_free_mesh(mesh);
    return geometry;
}
