#include <GL/glut.h>
#include <vector>
#include <iostream>

using namespace std;

const int WINDOW_WIDTH = 640*2;
const int WINDOW_HEIGHT = 480;

typedef struct {
  GLfloat x, y, z;
  GLfloat r, g, b, a;
} Vertex;

typedef struct
{
  GLfloat x, y, z;
} Data;

namespace Primitive {
  void point(Vertex, GLfloat);
  void line(Vertex, Vertex, GLfloat);
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

/*
class DataSetReader
{
public:
  dataset read();
};

dataset DataSetReader::read() {
  int i;

  example item;
  dataset tester;

  for (i = 1; i <= 5; i++) {
    item.x = i;
    item.y = i;
    item.label = "New";

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

  int max_x, max_y, win_x, win_y;
  int start_x, start_y, end_x, end_y;

  dataset X;

  DataSetReader reader;
  X = reader.read();

  max_x = 0;
  max_y = 0;

  for (i = 0; i < X.size(); i++) {
    if (max_x < X[i].x) {
      max_x = X[i].x;
    }

    if (max_y < X[i].y) {
      max_y = X[i].y;
    }
  }

  win_x = max_x + 3;
  win_y = max_y + 3;

  gluOrtho2D(0, win_x, 0, win_y);

  start_x = 1;
  start_y = 1;

  end_x = win_x - 2;
  end_y = win_y - 2;

  glColor3f(109.0 / 255, 174.0 / 255, 219.0 / 255);

  // drawing x axis

  glBegin(GL_LINES);
  glVertex2f(start_x, start_y);
  glVertex2f(end_x + 1, start_y);

  glVertex2f(end_x + 1, start_y);
  glVertex2f(end_x + 1, end_y + 1);

  glVertex2f(end_x + 1, end_y + 1);
  glVertex2f(start_x, end_y + 1);

  glVertex2f(start_x, start_y);
  glVertex2f(start_x, end_y + 1);

  glEnd();

  // draw graph lines

  glColor3f(219.0 / 255, 214.0 / 255, 214.0 / 255);

  for (i = 1; i <= X.size(); i++) {
    glBegin(GL_LINES);
    glVertex2f(start_x, start_y + i);
    glVertex2f(end_x + 1, start_y + i);
    glEnd();
  }

  // plotting histogram

  glLineWidth(250.0 / X.size());
  glColor3f(23.0 / 255, 55.0 / 255, 83.0 / 255);
  for (i = 0; i < X.size(); i++) {
    glBegin(GL_LINES);
    glVertex3f(X[i].x + start_x, start_y, 1);
    glVertex3f(X[i].x + start_x, X[i].y + start_y, 1);
    glEnd();
  }

}
*/

void display()
{
  Vertex v1 = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f};
  Vertex v2 = {1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f};
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
  float ratio;

  ratio = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glClearColor(238.0 / 255, 236.0 / 255, 238.0 / 255, 1);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //Orthographic Projection
  glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
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

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glutMainLoop();

  return 0;
}
