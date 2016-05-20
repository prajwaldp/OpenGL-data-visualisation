#include <GL/glut.h>
#include <FTGL/ftgl.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include "constants_and_globals.h"
#include "custom_types.h"
#include "primitive.h"
#include "data_set_reader.h"
#include "plot.h"
#include "bar_graph.h"
#include "scatter_plot.h"
#include "stem.h"
#include "scatter_plot_3d.h"
#include "stem_3d.h"
#include "pie_chart.h"
#include "utility.h"

void key(unsigned char k, int x, int y)
{
  switch (k) {
  case 'h':
    if (theta_y > 0) {
      theta_y -= 5;
    }
    ScatterPlot3D scatter_plot_3d;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scatter_plot_3d.display();

    break;

  case 'l':
    if (theta_y < 90) {
      theta_y += 5;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scatter_plot_3d.display();

  case 'j':
    if (theta_x > 0) {
      theta_x -= 5;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scatter_plot_3d.display();

    break;

  case 'k':
    if (theta_x < 90) {
      theta_x += 5;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scatter_plot_3d.display();
  }
}

void display()
{
  FTTextureFont font("/usr/share/fonts/TTF/Inconsolata-Bold.ttf");

  font.FaceSize(72);
  glPushMatrix();
  Utility::set_perspective();
  glColor3f(1, 1, 1);
  //font.Render("Hello");
  Utility::set_orthographic();
  glPopMatrix();

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
  Utility::set_orthographic();
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
  glutKeyboardFunc(key);

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
