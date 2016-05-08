#ifndef STEM_3D_H
#define STEM_3D_H

class Stem3D {
public:
  void display();
};

void Stem3D::display() {

  int i;
  int max_x, max_y, min_x, min_y, max_z, min_z;
  float width;

  Dataset X;
  DataSetReader reader;
  X = reader.read();

  Vertex v1 = {-0.8, -0.8, 0.8, 0, 0, 0, 0.5};
  Vertex v2 = {0.8, -0.8, 0.8, 0, 0, 0, 0.5};
  Vertex v3 = {0.8, 0.8, 0.8, 0, 0, 0, 0.5};
  Vertex v4 = {-0.8, 0.8, 0.8, 0, 0, 0, 0.5};
  Vertex v5 = {-0.8, -0.8, -0.8, 0, 0, 0, 0.5};
  Vertex v6 = {0.8, -0.8, -0.8, 0, 0, 0, 0.5};
  Vertex v7 = {0.8, 0.8, -0.8, 0, 0, 0, 0.5};
  Vertex v8 = {-0.8, 0.8, -0.8, 0, 0, 0, 0.5};

  max_x = 0;
  max_y = 0;
  max_z = 0;
  min_x = 0;
  min_y = 0;
  min_z = 0;

  for (i = 0; i < X.size(); i++) {
    if (max_x < X[i].x) {
      max_x = X[i].x;
    }

    if (max_y < X[i].y) {
      max_y = X[i].y;
    }

    if (max_z < X[i].z) {
      max_z = X[i].z;
    }

    if (min_x > X[i].x) {
      min_x = X[i].x;
    }

    if (min_y > X[i].y) {
      min_y = X[i].y;
    }

    if (min_z > X[i].z) {
      min_z = X[i].z;
    }
  }

  width = 1.6 / X.size();
  Color graph_color = { 23 / 255.0, 55 / 255.0, 83 / 255.0, 1 };

  float current = -0.8;
  float y;
  float z;

  // drawing the 3d axes
  glPushMatrix();
  glScalef(0.5, 0.5, 0.5);
  glRotatef(45, 1.f, 0.f, 0.f);
  glRotatef(45, 0.f, 1.f, 0.f);
  Primitive::unfilled_cube(v1, v2, v3, v4, v5, v6, v7, v8, 1);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.5, 0.5, 0.5);
  glRotatef(45, 1.f, 0.f, 0.f);
  glRotatef(45, 0.f, 1.f, 0.f);
  for (i = 0; i < X.size(); i++) {
    y = -0.8 + 1.6 * X[i].y / (max_y - min_y);
    z = -0.8 + 1.6 * X[i].z / (max_z - min_z);
    Vertex v1 = {current + width / 2.f, -0.8, z, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Vertex v2 = {current + width / 2.f, y, z, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Primitive::line(v1, v2, 1);
    Primitive::point(v2, 10);
    Primitive::write(X[i].label, current + width / 2.f, y, z);
    current += width;
  }
  glPopMatrix();
}

#endif
