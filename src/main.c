#include "array.h"
#include "display.h"
#include "mesh.h"
#include "triangle.h"
#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <stdint.h>

int fov_factor = 640;
bool is_running = false;
vec3_t camera_position = {0, 0, -5};
int previous_tick = 0;
char *filename = "./assets/f22.obj";

triangle_t *triangles_to_render = NULL;

void setup(void) {
  color_buffer =
      (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);

  if (!color_buffer) {
    fprintf(stderr, "Error initializing color buffer.\n");
    is_running = false;

    return;
  }

  color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           window_width, window_height);
  if (!color_buffer_texture) {
    fprintf(stderr, "Error initializing SDL color buffer texture.\n");
    is_running = false;
  }

  bool loaded = load_obj_file_data(filename);
  if (!loaded) {
    fprintf(stderr, "Error loading mesh data from: '%s'", filename);
    is_running = false;
  }
}

void process_input(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE) {
      is_running = false;
    }
    break;
  }
}

vec2_t project(vec3_t point) {
  vec2_t projected_point = {fov_factor * (point.x / point.z),
                            fov_factor * (point.y / point.z)};

  return projected_point;
}

void update(void) {
  int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_tick);
  if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
    SDL_Delay(time_to_wait);
  }

  previous_tick = SDL_GetTicks();

  mesh.rotation.x += 0.01;
  mesh.rotation.y += 0.01;
  mesh.rotation.z += 0.01;

  triangles_to_render = NULL;

  int num_faces = array_length(mesh.faces);
  for (int i = 0; i < num_faces; i++) {
    face_t mesh_face = mesh.faces[i];

    vec3_t face_vertices[3];
    face_vertices[0] = mesh.vertices[mesh_face.a - 1];
    face_vertices[1] = mesh.vertices[mesh_face.b - 1];
    face_vertices[2] = mesh.vertices[mesh_face.c - 1];

    triangle_t transformed_triangle;
    for (int j = 0; j < 3; j++) {
      vec3_t transformed_vertex = face_vertices[j];

      transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
      transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
      transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);

      transformed_vertex.z -= camera_position.z;

      vec2_t projected_point = project(transformed_vertex);

      projected_point.x += (window_width / 2.0);
      projected_point.y += (window_height / 2.0);

      transformed_triangle.points[j] = projected_point;
    }

    array_push(triangles_to_render, transformed_triangle);
  }
}

void render(void) {
  clear_color_buffer(0xFF000000);
  draw_grid();

  int num_triangle_faces = array_length(triangles_to_render);
  for (int i = 0; i < num_triangle_faces; i++) {
    triangle_t triangle = triangles_to_render[i];
    draw_rectangle(triangle.points[0].x, triangle.points[0].y, 3, 3,
                   0xFFFFA500);
    draw_rectangle(triangle.points[1].x, triangle.points[1].y, 3, 3,
                   0xFFFFA500);
    draw_rectangle(triangle.points[2].x, triangle.points[2].y, 3, 3,
                   0xFFFFA500);

    draw_triangle(triangle.points[0].x, triangle.points[0].y,
                  triangle.points[1].x, triangle.points[1].y,
                  triangle.points[2].x, triangle.points[2].y, 0xFFFFA500);
  }

  render_color_buffer();

  SDL_RenderPresent(renderer);

  array_free(triangles_to_render);
}

void free_resources(void) {
  array_free(mesh.vertices);
  array_free(mesh.faces);
  free(color_buffer);
}

int main(void) {
  is_running = initialize_window();

  setup();

  while (is_running) {
    process_input();
    update();
    render();
  }

  destroy_window();
  free_resources();

  return 0;
}
