#include "vector.h"
#include <math.h>

vec2_t vec2_add(vec2_t a, vec2_t b) {
  vec2_t vector = {a.x + b.x, a.y + b.y};
  return vector;
}

vec2_t vec2_sub(vec2_t a, vec2_t b) {
  vec2_t vector = {a.x - b.x, a.y - b.y};
  return vector;
}

vec2_t vec2_mul(vec2_t v, float factor) {
  vec2_t vector = {v.x * factor, v.y * factor};
  return vector;
}

vec2_t vec2_div(vec2_t v, float factor) {
  vec2_t vector = {v.x / factor, v.y / factor};
  return vector;
}

float vec2_length(vec2_t v) { return sqrt(v.x * v.x + v.y * v.y); }

void vec2_normalize(vec2_t *v) {
  float length = sqrt(v->x * v->x + v->y * v->y);
  v->x /= length;
  v->y /= length;
}

vec3_t vec3_add(vec3_t a, vec3_t b) {
  vec3_t vector = {a.x + b.x, a.y + b.y, a.z + b.z};
  return vector;
}

vec3_t vec3_sub(vec3_t a, vec3_t b) {
  vec3_t vector = {a.x - b.x, a.y - b.y, a.z - b.z};
  return vector;
}

vec3_t vec3_mul(vec3_t v, float factor) {
  vec3_t vector = {v.x * factor, v.y * factor, v.z * factor};
  return vector;
}

vec3_t vec3_div(vec3_t v, float factor) {
  vec3_t vector = {v.x / factor, v.y / factor, v.z / factor};
  return vector;
}

float vec3_length(vec3_t v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

vec3_t vec3_rotate_x(vec3_t v, float angle) {
  vec3_t rotated_point = {.x = v.x,
                          .y = cos(angle) * v.y - sin(angle) * v.z,
                          .z = sin(angle) * v.y + cos(angle) * v.z};

  return rotated_point;
}

vec3_t vec3_rotate_y(vec3_t v, float angle) {
  vec3_t rotated_point = {.x = cos(angle) * v.x - sin(angle) * v.z,
                          .y = v.y,
                          .z = sin(angle) * v.x + cos(angle) * v.z};

  return rotated_point;
}

vec3_t vec3_rotate_z(vec3_t v, float angle) {
  vec3_t rotated_point = {.x = cos(angle) * v.x - sin(angle) * v.y,
                          .y = sin(angle) * v.x + cos(angle) * v.y,
                          .z = v.z};

  return rotated_point;
}

vec3_t vec3_cross(vec3_t a, vec3_t b) {
  vec3_t vector = {(a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z),
                   (a.x * b.y) - (a.y * b.x)};
  return vector;
}

float vec3_dot(vec3_t a, vec3_t b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

void vec3_normalize(vec3_t *v) {
  float length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
  v->x /= length;
  v->y /= length;
  v->z /= length;
}
