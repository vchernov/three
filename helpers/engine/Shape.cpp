#include "Shape.h"

#include <array>

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
    geometry.vertexBuffers.push_back(std::move(pointsBuffer));

    geometry.indexBuffer.bind();
    geometry.indexBuffer.upload(faces.data(), TypeInfo<Face3::ValueType>::dataType, sizeof(Face3::ValueType), Face3::getIndexCount() * faces.size());

    return geometry;
}

GeometryBuffer Shape::createCube() {
    GeometryBuffer geometry;
    geometry.primitiveType = GL_TRIANGLES;

    auto v1 = glm::vec3(-0.5f, -0.5f, 0.5f);
    auto v2 = glm::vec3(0.5f, -0.5f, 0.5f);
    auto v3 = glm::vec3(0.5f, 0.5f, 0.5f);
    auto v4 = glm::vec3(-0.5f, 0.5f, 0.5f);

    auto v5 = glm::vec3(-0.5f, -0.5f, -0.5f);
    auto v6 = glm::vec3(0.5f, -0.5f, -0.5f);
    auto v7 = glm::vec3(0.5f, 0.5f, -0.5f);
    auto v8 = glm::vec3(-0.5f, 0.5f, -0.5f);

    auto n1 = glm::vec3(0.0f, 0.0f, 1.0f);
    auto n2 = glm::vec3(1.0f, 0.0f, 0.0f);
    auto n3 = glm::vec3(0.0f, 0.0f, -1.0f);
    auto n4 = glm::vec3(-1.0f, 0.0f, 0.0f);
    auto n5 = glm::vec3(0.0f, 1.0f, 0.0f);
    auto n6 = glm::vec3(0.0f, -1.0f, 0.0f);

    const int vertexCount = 24;
    std::array<glm::vec3, vertexCount * 2> vertices = {
        v1, n1, v2, n1, v3, n1, v4, n1,
        v2, n2, v6, n2, v7, n2, v3, n2,
        v6, n3, v5, n3, v8, n3, v7, n3,
        v5, n4, v1, n4, v4, n4, v8, n4,
        v4, n5, v3, n5, v7, n5, v8, n5,
        v5, n6, v6, n6, v2, n6, v1, n6
    };

    std::array<unsigned char, 36> indices = {
        0, 1, 2, 0, 2, 3,
        4, 5, 6, 4, 6, 7,
        8, 9, 10, 8, 10, 11,
        12, 13, 14, 12, 14, 15,
        16, 17, 18, 16, 18, 19,
        20, 21, 22, 20, 22, 23
    };

    VertexBuffer buffer;
    buffer.bind();
    buffer.upload(vertices.data(), vertexCount, sizeof(glm::vec3) + sizeof(glm::vec3));
    buffer.addAttribute({AttributeName::position, TypeInfo<float>::dataType, glm::vec3::length(), 0});
    buffer.addAttribute({AttributeName::normal, TypeInfo<float>::dataType, glm::vec3::length(), sizeof(glm::vec3)});
    geometry.vertexBuffers.push_back(std::move(buffer));

    geometry.indexBuffer.bind();
    geometry.indexBuffer.upload(indices.data(), TypeInfo<unsigned char>::dataType, sizeof(unsigned char), indices.size());

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
    geometry.vertexBuffers.push_back(std::move(pointBuffer));

    geometry.indexBuffer.bind();
    geometry.indexBuffer.upload(indices.data(), TypeInfo<unsigned short>::dataType, sizeof(unsigned short), indices.size());

    return geometry;
}

GeometryBuffer Shape::generateCube() {
    GeometryBuffer geometry;
    geometry.primitiveType = GL_TRIANGLES;

    par_shapes_mesh* mesh = par_shapes_create_cube();

    VertexBuffer pointBuffer;
    pointBuffer.bind();
    pointBuffer.upload(mesh->points, mesh->npoints, sizeof(float) * 3);
    pointBuffer.addAttribute({AttributeName::position, TypeInfo<float>::dataType, 3, 0});
    geometry.vertexBuffers.push_back(std::move(pointBuffer));

    par_shapes_compute_normals(mesh);

    VertexBuffer normalBuffer;
    normalBuffer.bind();
    normalBuffer.upload(mesh->normals, mesh->npoints, sizeof(float) * 3);
    normalBuffer.addAttribute({AttributeName::normal, TypeInfo<float>::dataType, 3, 0});
    geometry.vertexBuffers.push_back(std::move(normalBuffer));

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
    geometry.vertexBuffers.push_back(std::move(pointBuffer));

    VertexBuffer normalBuffer;
    normalBuffer.bind();
    normalBuffer.upload(mesh->normals, mesh->npoints, sizeof(float) * 3);
    normalBuffer.addAttribute({AttributeName::normal, TypeInfo<float>::dataType, 3, 0});
    geometry.vertexBuffers.push_back(std::move(normalBuffer));

    VertexBuffer texCoordBuffer;
    texCoordBuffer.bind();
    texCoordBuffer.upload(mesh->tcoords, mesh->npoints, sizeof(float) * 2);
    texCoordBuffer.addAttribute({AttributeName::texCoord, TypeInfo<float>::dataType, 2, 0});
    geometry.vertexBuffers.push_back(std::move(texCoordBuffer));

    geometry.indexBuffer.bind();
    geometry.indexBuffer.upload(mesh->triangles, TypeInfo<PAR_SHAPES_T>::dataType, sizeof(PAR_SHAPES_T), mesh->ntriangles * 3);

    par_shapes_free_mesh(mesh);
    return geometry;
}
