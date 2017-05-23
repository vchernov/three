#include "Shape.h"

#include "AttributeName.h"
#include "../../three/TypeInfo.h"

#define PAR_SHAPES_IMPLEMENTATION
#include "par_shapes.h"

using namespace three;

GeometryBuffer Shape::createCube() {
    GeometryBuffer geometry;
    geometry.primitiveType = GL_TRIANGLES;

    par_shapes_mesh* mesh = par_shapes_create_cube();

    VertexBuffer pointsBuffer;
    pointsBuffer.bind();
    pointsBuffer.upload(mesh->points, mesh->npoints, sizeof(float) * 3);
    pointsBuffer.addAttribute({AttributeName::position, TypeInfo<float>::dataType, 3, 0});
    geometry.vertexBuffers.emplace_back(std::move(pointsBuffer));

    geometry.indexBuffer.bind();
    geometry.indexBuffer.upload(mesh->triangles, TypeInfo<PAR_SHAPES_T>::dataType, sizeof(PAR_SHAPES_T), mesh->ntriangles);

    par_shapes_free_mesh(mesh);
    return geometry;
}

GeometryBuffer Shape::createSphere(int slices, int stacks) {
    GeometryBuffer geometry;
    geometry.primitiveType = GL_TRIANGLES;

    par_shapes_mesh* mesh = par_shapes_create_parametric_sphere(slices, stacks);

    VertexBuffer pointsBuffer;
    pointsBuffer.bind();
    pointsBuffer.upload(mesh->points, mesh->npoints, sizeof(float) * 3);
    pointsBuffer.addAttribute({AttributeName::position, TypeInfo<float>::dataType, 3, 0});
    geometry.vertexBuffers.emplace_back(std::move(pointsBuffer));

    VertexBuffer texCoordsBuffer;
    texCoordsBuffer.bind();
    texCoordsBuffer.upload(mesh->tcoords, mesh->npoints, sizeof(float) * 2);
    pointsBuffer.addAttribute({AttributeName::texCoord, TypeInfo<float>::dataType, 2, 0});
    geometry.vertexBuffers.emplace_back(std::move(texCoordsBuffer));

    geometry.indexBuffer.bind();
    geometry.indexBuffer.upload(mesh->triangles, TypeInfo<PAR_SHAPES_T>::dataType, sizeof(PAR_SHAPES_T), mesh->ntriangles);

    par_shapes_free_mesh(mesh);
    return geometry;
}
