#ifndef STEM_H
#define STEM_H

class Stem
{
public:
  void display();
};

void Stem::display()
{
  int i;
  int max_x, max_y, min_x, min_y;
  float width;

  Dataset X;

  DataSetReader reader;
  X = reader.read();

  max_x = 0;
  max_y = 0;
  min_x = 0;
  min_y = 0;

  for (i = 0; i < X.size(); i++) {
    if (max_x < X[i].x) {
      max_x = X[i].x;
    }

    if (max_y < X[i].y) {
      max_y = X[i].y;
    }

    if (min_x > X[i].x) {
      min_x = X[i].x;
    }

    if (min_y > X[i].y) {
      min_y = X[i].y;
    }
  }

  Color border_color = { 77 / 255.0, 83 / 255.0, 89 / 255.0, 1 };

  Vertex v1 = { -0.8f, -0.8f, 0.f, border_color.r, border_color.g, border_color.b, border_color.a};
  Vertex v2 = { -0.8f, 0.8f, 0.f, border_color.r, border_color.g, border_color.b, border_color.a};
  Vertex v3 = { 0.8f, 0.8f, 0.f, border_color.r, border_color.g, border_color.b, border_color.a};
  Vertex v4 = { 0.8f, -0.8f, 0.f, border_color.r, border_color.g, border_color.b, border_color.a};
  Primitive::unfilled_quad(v1, v2, v3, v4, 1);

  width = 1.6 / X.size();
  Color graph_color = { 23 / 255.0, 55 / 255.0, 83 / 255.0, 1 };

  float current = -0.8;
  float height;
  for (i = 0; i < X.size(); i++) {
    height = -0.8 + 1.6 * X[i].y / (max_y - min_y);
    Vertex v1 = {current + width / 2.f, -0.8, 0, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Vertex v2 = {current + width / 2.f, height, 0, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Primitive::line(v1, v2, 1);
    Primitive::point(v2, 10);
    current += width;
  }
}

#endif
