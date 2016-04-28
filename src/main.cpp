#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

#include "constants_and_globals.h"
#include "custom_types.h"
#include "primitive.h"
#include "data_set_reader.h"
#include "bar_graph.h"
#include "scatter_plot.h"
#include "stem.h"
#include "scatter_plot_3d.h"
#include "stem_3d.h"
#include "utility.h"

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
