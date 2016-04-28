#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

typedef struct {
  GLfloat x, y, z;
  GLfloat r, g, b, a;
} Vertex;

typedef struct {
  GLfloat x, y, z;
  string label;
} Data;

typedef struct {
  GLfloat r, g, b, a;
} Color;

typedef vector<Data> Dataset;

#endif
