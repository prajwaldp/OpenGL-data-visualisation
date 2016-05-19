#ifndef BAR_GRAPH_H
#define BAR_GRAPH_H

#include <math.h>

class BarGraph
{
public:
  void display();
};

void BarGraph::display()
{
  int i;
  int max_x, max_y, min_x, min_y;
  float width, gap;

  Dataset X;

  DataSetReader reader(1);
  X = reader.read();

  max_x = 0;
  min_x = 0;

  for (i = 0; i < X.size(); i++) {
    if (max_x < X[i].x) {
      max_x = X[i].x;
    }

    if (min_x > X[i].x) {
      min_x = X[i].x;
    }
  }

  max_x += 1;

  Color border_color = { 77 / 255.0, 83 / 255.0, 89 / 255.0, 1 };

  Vertex v1 = { -0.8f, -0.8f, 0.f, border_color.r, border_color.g, border_color.b, border_color.a};
  Vertex v2 = { -0.8f, 0.8f, 0.f, border_color.r, border_color.g, border_color.b, border_color.a};
  Vertex v3 = { 0.8f, 0.8f, 0.f, border_color.r, border_color.g, border_color.b, border_color.a};
  Vertex v4 = { 0.8f, -0.8f, 0.f, border_color.r, border_color.g, border_color.b, border_color.a};
  Primitive::unfilled_quad(v1, v2, v3, v4, 1);

  width = 1.6 / X.size();
  gap = width / 50;
  Color graph_color = { 23 / 255.0, 55 / 255.0, 83 / 255.0, 1 };
  Color graph_lines_color = { 210 / 255.0, 210 / 255.0, 210 / 255.0, 1 };

  float current = -0.8;
  float height;

  // Graph lines
  for (i = 0; i <= 10; i++) {
    height = -0.8 + i * 1.6 / 10;
    Vertex v1 = {-0.8, height, 0, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a};
    Vertex v2 = {0.8, height, 0, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a};
    Primitive::line(v1, v2, 1);
    ostringstream ss;
    ss << i * (max_x) / 10;
    std::string s(ss.str());
    Primitive::write(s, -0.9, height);
  }

  // Plotting bar graph
  for (i = 0; i < X.size(); i++) {
    height = -0.8 + 1.6 * X[i].x / ceil(max_x - min_x);
    Vertex v1 = {current + gap, -0.8, 0, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Vertex v2 = {current + width - 2 * gap, -0.8, 0, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Vertex v3 = {current + width - 2 * gap, height, 0, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Vertex v4 = {current + gap, height, 0, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Primitive::filled_quad(v1, v2, v3, v4);
    Primitive::write(X[i].label, current + gap, -0.85);
    current += width;
  }
}

#endif
