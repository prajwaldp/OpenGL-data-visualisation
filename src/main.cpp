#include <GL/glut.h>
#include <vector>
#include <iostream>

using namespace std;

const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 700;

typedef struct {
  GLfloat x, y, z;
  GLfloat r, g, b, a;
} Vertex;

typedef struct {
  GLfloat x, y, z;
} Data;

typedef struct {
  GLfloat r, g, b, a;
} Color;

typedef vector<Data> Dataset;

namespace Primitive {
  void point(Vertex, GLfloat);
  void line(Vertex, Vertex, GLfloat);
  void unfilled_quad(Vertex, Vertex, Vertex, Vertex, GLfloat);
  void filled_quad(Vertex, Vertex, Vertex, Vertex);
  void unfilled_cube(Vertex, Vertex, Vertex, Vertex, Vertex, Vertex, Vertex, Vertex, GLfloat);
};

void Primitive::point(Vertex v, GLfloat size) {
  glPointSize(size);
  glBegin(GL_POINTS);
  glColor4f(v.r, v.g, v.b, v.a);
  glVertex3f(v.x, v.y, v.z);
  glEnd();
}

void Primitive::line(Vertex v1, Vertex v2, GLfloat width) {
  glLineWidth(width);
  glBegin(GL_LINES);
  glColor4f(v1.r, v1.g, v1.b, v1.a);
  glVertex3f(v1.x, v1.y, v1.z);
  glColor4f(v2.r, v2.g, v2.b, v2.a);
  glVertex3f(v2.x, v2.y, v2.z);
  glEnd();
}

void Primitive::unfilled_quad(Vertex v1, Vertex v2, Vertex v3, Vertex v4, GLfloat width) {
  Primitive::line(v1, v2, width);
  Primitive::line(v2, v3, width);
  Primitive::line(v3, v4, width);
  Primitive::line(v4, v1, width);
}

void Primitive::filled_quad(Vertex v1, Vertex v2, Vertex v3, Vertex v4) {
  glBegin(GL_POLYGON);
  glColor4f(v1.r, v1.g, v1.b, v1.a);
  glVertex3f(v1.x, v1.y, v1.z);

  glColor4f(v2.r, v2.g, v2.b, v2.a);
  glVertex3f(v2.x, v2.y, v2.z);

  glColor4f(v3.r, v3.g, v3.b, v3.a);
  glVertex3f(v3.x, v3.y, v3.z);

  glColor4f(v4.r, v4.g, v4.b, v4.a);
  glVertex3f(v4.x, v4.y, v4.z);
  glEnd();
}

void Primitive::unfilled_cube(Vertex v1, Vertex v2, Vertex v3, Vertex v4, Vertex v5, Vertex v6, Vertex v7, Vertex v8, GLfloat width) {
  Primitive::unfilled_quad(v1, v2, v3, v4, width);
  Primitive::unfilled_quad(v5, v6, v7, v8, width);
  Primitive::line(v1, v5, width);
  Primitive::line(v2, v6, width);
  Primitive::line(v3, v7, width);
  Primitive::line(v4, v8, width);
}

class DataSetReader
{
public:
  Dataset read();
};

Dataset DataSetReader::read() {
  int i;

  Data item;
  Dataset tester;

  for (i = 1; i <= 10; i++) {
    item.x = i;
    item.y = i;
    item.z = i;

    tester.push_back(item);
  }

  return tester;
}

class BarGraph
{
public:
  void display();
};

void BarGraph::display()
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
    Vertex v1 = {current + 0.02, -0.8, 0, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Vertex v2 = {current + width - 0.04, -0.8, 0, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Vertex v3 = {current + width - 0.04, height, 0, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Vertex v4 = {current + 0.02, height, 0, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Primitive::filled_quad(v1, v2, v3, v4);
    current += width;
  }
}

class ScatterPlot
{
public:
  void display();
};

void ScatterPlot::display()
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
    Vertex v = {current + width / 2.f, height, 0, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Primitive::point(v, 10);
    current += width;
  }
}

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

class ScatterPlot3D {
public:
  void display();
};

void ScatterPlot3D::display() {

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
    Vertex v = {current + width / 2.f, y, z, graph_color.r, graph_color.g, graph_color.b, graph_color.a};
    Primitive::point(v, 10);
    current += width;
  }
  glPopMatrix();
}

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
    current += width;
  }
  glPopMatrix();
}


namespace Utility {
  void menu(int);
  void show_menu();
}

void Utility::menu(int id) {
  switch(id) {

  case 0: exit(0);

  case 1:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    BarGraph bar_graph;
    bar_graph.display();
    break;

  case 2:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ScatterPlot scatter_plot;
    scatter_plot.display();
    break;

  case 3:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Stem stem;
    stem.display();
    break;

  case 4:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ScatterPlot3D scatter_plot_3d;
    scatter_plot_3d.display();
    break;

  case 5:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Stem3D stem_3d;
    stem_3d.display();
    break;
  }

  glutPostRedisplay();
}

void Utility::show_menu() {
  glutCreateMenu(Utility::menu);
  glutAddMenuEntry("Quit", 0);
  glutAddMenuEntry("Bar Graph", 1);
  glutAddMenuEntry("Scatter Plot", 2);
  glutAddMenuEntry("Stem", 3);
  glutAddMenuEntry("3D Scatter Plot", 4);
  glutAddMenuEntry("3D Stem", 5);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display()
{
  glutSwapBuffers();
  glFlush();
}

void reshape(int w, int h)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutPostRedisplay();
}

void init()
{
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glClearColor(238.0 / 255, 236.0 / 255, 238.0 / 255, 1);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //Orthographic Projection
  glOrtho(-1.f, -1.f, -1.f, 1.f, 1.f, -1.f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("Data Visualization Project");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  init();
  Utility::show_menu();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glutMainLoop();

  return 0;
}
