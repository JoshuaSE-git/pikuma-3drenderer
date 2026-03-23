#include "mesh.h"
#include "array.h"
#include "vector.h"
#include <stdio.h>

mesh_t mesh = {.vertices = NULL, .faces = NULL, .rotation = {0, 0, 0}};

vec3_t cube_vertices[N_CUBE_VERTICES] = {
    {-1, -1, -1}, {-1, 1, -1}, {1, 1, -1}, {1, -1, -1},
    {1, 1, 1},    {1, -1, 1},  {-1, 1, 1}, {-1, -1, 1},
};

face_t cube_faces[N_CUBE_FACES] = {
    // front
    {1, 2, 3, 0xFFFF0000},
    {1, 3, 4, 0xFFFF0000},
    // right
    {4, 3, 5, 0xFF00FF00},
    {4, 5, 6, 0xFF00FF00},
    // back
    {6, 5, 7, 0xFF0000FF},
    {6, 7, 8, 0xFF0000FF},
    // left
    {8, 7, 2, 0xFFFFFF00},
    {8, 2, 1, 0xFFFFFF00},
    // top
    {2, 7, 5, 0xFFFF00FF},
    {2, 5, 3, 0xFFFF00FF},
    // bottom
    {6, 8, 1, 0xFF00FFFF},
    {6, 1, 4, 0xFF00FFFF}};

void load_cube_mesh_data(void) {
  for (int i = 0; i < N_CUBE_VERTICES; i++) {
    vec3_t vertex = cube_vertices[i];
    array_push(mesh.vertices, vertex);
  }

  for (int i = 0; i < N_CUBE_FACES; i++) {
    face_t face = cube_faces[i];
    array_push(mesh.faces, face)
  }
}

bool load_obj_file_data(char *filename) {
  FILE *fptr;
  fptr = fopen(filename, "r");
  if (!fptr) {
    return false;
  }

  char buf[1024];
  while (fgets(buf, sizeof(buf), fptr) != NULL) {
    if (buf[0] == 'v' && buf[1] == ' ') {
      vec3_t vertex;
      sscanf(buf, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
      array_push(mesh.vertices, vertex);
    } else if (buf[0] == 'f') {
      face_t face;
      sscanf(buf, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &face.a, &face.b,
             &face.c);
      array_push(mesh.faces, face);
    }
  }

  fclose(fptr);
  return true;
}
