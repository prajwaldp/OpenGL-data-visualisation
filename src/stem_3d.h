#ifndef STEM_3D_H
#define STEM_3D_H

class Stem3D {
public:
  void display();
};

void Stem3D::display() {

  int i;
  int max_x, max_y, min_x, min_y, max_z, min_z;

  Dataset X;
  DataSetReader reader(3);
  X = reader.read();

  Vertex v1 = {-0.8, -0.8, 0.8, 0, 0, 0, 0.5};
  Vertex v2 = {0.8, -0.8, 0.8, 0, 0, 0, 0.5};
  Vertex v3 = {0.8, 0.8, 0.8, 0, 0, 0, 0.5};
  Vertex v4 = {-0.8, 0.8, 0.8, 0, 0, 0, 0.5};
  Vertex v5 = {-0.8, -0.8, -0.8, 0, 0, 0, 0.5};
  Vertex v6 = {0.8, -0.8, -0.8, 0, 0, 0, 0.5};
  Vertex v7 = {0.8, 0.8, -0.8, 0, 0, 0, 0.5};
  Vertex v8 = {-0.8, 0.8, -0.8, 0, 0, 0, 0.5};

  max_x = min_x = X[0].x;
  max_y = min_y = X[0].y;
  max_z = min_z = X[0].z;

  for (i = 0; i < X.size(); i++) {
    if (max_x < X[i].x) {
      max_x = ceil(X[i].x);
    }

    if (max_y < X[i].y) {
      max_y = ceil(X[i].y);
    }

    if (max_z < X[i].z) {
      max_z = ceil(X[i].z);
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

  Color graph_color = { 23 / 255.0, 55 / 255.0, 83 / 255.0, 1 };
  Color graph_lines_color = { 210 / 255.0, 210 / 255.0, 210 / 255.0, 1.0 };

  GLfloat x, y, z;
  GLfloat horizontal, vertical, depth;
  Vertex a, b, c; // graph lines

  // drawing the 3d axes
  glPushMatrix();
  glScalef(0.5, 0.5, 0.5);
  glRotatef(45, 1, 0, 0);
  glRotatef(45, 0, 1, 0);
  Primitive::unfilled_cube(v1, v2, v3, v4, v5, v6, v7, v8, 1);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.5, 0.5, 0.5);
  glRotatef(45, 1, 0, 0);
  glRotatef(45, 0, 1, 0);
  for (i = 0; i <= 10; i++) {
    horizontal = -0.8 + i * 1.6 / 10;
    a = { -0.8, horizontal, 0.8, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a };
    b = { 0.8, horizontal, 0.8, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a };
    c = { -0.8, horizontal, -0.8, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a };
    Primitive::line(a, b, 1);
    Primitive::line(a, c, 1);
    ostringstream ss;
    ss << min_x + i * (float) (max_x - min_x) / 10;
    string s(ss.str());
    Primitive::write(s, -0.9, horizontal, -0.8);

    vertical = -0.8 + i * 1.6 / 10;
    a = { vertical, -0.8, 0.8, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a };
    b = { vertical, 0.8, 0.8, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a };
    Primitive::line(a, b, 1);
    ostringstream ss1;
    ss1 << min_y + i * (float) (max_y - min_y) / 10;
    string s1(ss1.str());
    Primitive::write(s1, vertical, -0.9, 0.8);

    depth = -0.8 + i * 1.6 / 10;
    a = { -0.8, -0.8, depth, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a };
    b = { -0.8, 0.8, depth, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a };
    Primitive::line(a, b, 1);
    ostringstream ss2;
    ss2 << min_z + i * (float) (max_z - min_z) / 10;
    string s2(ss2.str());
    Primitive::write(s2, -0.8, -0.9, depth);
  }
  glPopMatrix();

  glPushMatrix();
  glScalef(0.5, 0.5, 0.5);
  glRotatef(45, 1, 0, 0);
  glRotatef(45, 0, 1, 0);
  for (i = 0; i < X.size(); i++) {
    x = -0.8 + 1.6 * (X[i].x - min_x) / (max_x - min_x);
    y = -0.8 + 1.6 * (X[i].y - min_y) / (max_y - min_y);
    z = -0.8 + 1.6 * (X[i].z - min_z) / (max_z - min_z);
    Vertex v1 = {x, y, z, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Vertex v2 = {x, -0.8, z, graph_color.r, graph_color.b, graph_color.g, graph_color.a};
    Primitive::point(v1, 10);
    Primitive::line(v1, v2, 1);
    Primitive::write(X[i].label, x, y, z);
  }
  glPopMatrix();
}

#endif
