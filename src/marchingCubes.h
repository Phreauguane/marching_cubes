#pragma once

/* We use the following layout for vertex data */
typedef struct {
public:
	GLfloat pos[3]; /* 3D cartesian coordinates */
	GLubyte clr[4]; /* RGBA (8bit per channel is typically enough) */
} Vertex;

typedef struct {
   glm::vec3 p[3];
} Tri;

typedef struct {
   glm::vec3 p[8];
   double val[8];
} Cell;

int Polygonise(Cell grid, float iso, std::vector<Tri> &Triangles);
void genMarchingCubes(float iso, std::vector<Vertex> &vertices, std::vector<GLushort> &indices, glm::vec3 start, glm::vec3 end, float(*f)(glm::vec3, glm::vec3));

float dist(glm::vec3 p1, glm::vec3 p2);
// Iso surface generators
float sphereIsoSurf(glm::vec3 p1, glm::vec3 p2);
float noiseIsoSurf(glm::vec3 p1, glm::vec3 p2);
float fullIsoSurf(glm::vec3 p1, glm::vec3 p2);
float defIsoSurf(glm::vec3 p1, glm::vec3 p2);