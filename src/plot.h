#ifndef PLOT_H
#define PLOT_H

class Plot
{
public:
  void display();
};

void Plot::display()
{
  int i;
  int max_x, max_y, min_x, min_y;

  Dataset X;

  DataSetReader reader(2);
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

  max_x += 1;
  max_y += 1;

  Color border_color = { 77 / 255.0, 83 / 255.0, 89 / 255.0, 1 };

  Vertex v1 = { -0.8f, -0.8f, 0.f, border_color.r, border_color.g, border_color.b, border_color.a};
  Vertex v2 = { -0.8f, 0.8f, 0.f, border_color.r, border_color.g, border_color.b, border_color.a};
  Vertex v3 = { 0.8f, 0.8f, 0.f, border_color.r, border_color.g, border_color.b, border_color.a};
  Vertex v4 = { 0.8f, -0.8f, 0.f, border_color.r, border_color.g, border_color.b, border_color.a};
  Primitive::unfilled_quad(v1, v2, v3, v4, 1);

  Color graph_color = { 23 / 255.0, 55 / 255.0, 83 / 255.0, 1.0 };
  Color graph_lines_color = { 210 / 255.0, 210 / 255.0, 210 / 255.0, 1.0 };

  float height, width;

  for (i = 0; i <= 10; i++) {
    height = -0.8 + i * 1.6 / 10;
    Vertex v1 = {-0.8, height, 0, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a};
    Vertex v2 = {0.8, height, 0, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a};
    Primitive::line(v1, v2, 1);
    ostringstream ss;
    ss << i * (float) max_x / 10;
    std::string s(ss.str());
    Primitive::write(s, -0.9, height);

    width = -0.8 + i * 1.6 / 10;
    Vertex v3 = {width, -0.8, 0, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a};
    Vertex v4 = {width, 0.8, 0, graph_lines_color.r, graph_lines_color.g, graph_lines_color.b, graph_lines_color.a};
    Primitive::line(v3, v4, 1);
    ostringstream ss1;
    ss1 << i * (float) max_y / 10;
    std::string s1(ss1.str());
    Primitive::write(s1, width, -0.84);
  }

  GLfloat x, y;
  GLfloat offset = 0.8 / (max_x - min_x);
  x = -0.8 + 1.6 * X[0].x / (max_x - min_x);
  y = -0.8 + 1.6 * X[0].y / (max_y - min_y);
  Vertex old_v = {x, y, 0, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
  for (i = 0; i < X.size(); i++) {
    x = -0.8 + 1.6 * X[i].x / (max_x - min_x);
    y = -0.8 + 1.6 * X[i].y / (max_y - min_y);
    Vertex new_v = {x, y, 0, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Primitive::line(new_v, old_v, 1);
    Primitive::point(new_v, 10);
    Primitive::write(X[i].label, x + offset, y, 0);
    old_v = new_v;
  }
}

#endif
