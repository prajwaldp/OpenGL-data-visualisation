#ifndef SCATTER_PLOT_3D_H
#define SCATTER_PLOT_3D_H

class ScatterPlot3D {
public:
  void display();
};

void ScatterPlot3D::display() {

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

  max_x += 1;
  max_y += 1;
  max_z += 1;

  Color graph_color = { 23 / 255.0, 55 / 255.0, 83 / 255.0, 1 };
  Color graph_lines_color = { 210 / 255.0, 210 / 255.0, 210 / 255.0, 1.0 };

  float x;
  float y;
  float z;
  float height, width, depth;

  // drawing the 3d axes
  glPushMatrix();
  glScalef(0.5, 0.5, 0.5);
  Primitive::unfilled_cube(v1, v2, v3, v4, v5, v6, v7, v8, 1);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.5, 0.5, 0.5);
  for (i = 0; i <= 10; i++) {
    height = -0.8 + i * 1.6 / 10;
    ostringstream ss;
    ss << i * (float) max_x / 10;
    std::string s(ss.str());
    Primitive::write(s, -0.9, height, 0.8);

    width = -0.8 + i * 1.6 / 10;
    Vertex v1 = {-0.8, height, 0.8, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a};
    Vertex v2 = {0.8, height, 0.8, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a};
    Vertex v3 = {-0.8, height, -0.8, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a};
    Primitive::line(v1, v2, 1);
    Primitive::line(v1, v3, 1);
    ostringstream ss1;
    ss1 << i * (float) max_y / 10;
    std::string s1(ss1.str());
    Primitive::write(s1, width, -0.9, 0.8);

    depth = -0.8 + i * 1.6 / 10;
    ostringstream ss2;
    ss2 << i * (float) max_z / 10;
    std::string s2(ss2.str());
    Primitive::write(s2, -0.8, -0.9, depth);
  }
  glPopMatrix();

  glPushMatrix();
  glScalef(0.5, 0.5, 0.5);
  for (i = 0; i < X.size(); i++) {
    x = -0.8 + 1.6 * X[i].x / (max_x - min_x);
    y = -0.8 + 1.6 * X[i].y / (max_y - min_y);
    z = -0.8 + 1.6 * X[i].z / (max_z - min_z);
    Vertex v = {x, y, z, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Primitive::point(v, 10);
    Primitive::write(X[i].label, x, y, z);
  }
  glPopMatrix();
}

#endif
