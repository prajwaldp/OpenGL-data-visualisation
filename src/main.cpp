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
#include "plot_3d.h"
#include "scatter_plot_3d.h"
#include "pie_chart.h"
#include "utility.h"

int splash_screen_displayed = 0;

void key(unsigned char k, int x, int y)
{
  Plot3D plot_3d;
  ScatterPlot3D scatter_plot_3d;

  switch (k) {
  case 'h':
    if (theta_y > 0) {
      theta_y -= 5;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scatter_plot_3d.display();

    break;

  case 'l':
    if (theta_y < 90) {
      theta_y += 5;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scatter_plot_3d.display();

    break;

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

    break;

  case 'u':
    if (theta_y_2 > 0) {
      theta_y_2 -= 5;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    plot_3d.display();

    break;

  case 'p':
    if (theta_y_2 < 90) {
      theta_y_2 += 5;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    plot_3d.display();

    break;

  case 'i':
    if (theta_x_2 > 0) {
      theta_x_2 -= 5;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    plot_3d.display();

    break;

  case 'o':
    if (theta_x_2 < 90) {
      theta_x_2 += 5;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    plot_3d.display();

    break;
  }
}

void display_splash()
{
  FTPixmapFont font("/home/prajwal/workspace/projects/cpp/visualize/Inconsolata-Bold.ttf");

  font.FaceSize(50);
  glColor3f(0, 0, 0);
  glRasterPos3f(-0.8, 0.6, 0);
  font.Render("Data Visualization using OpenGL");

  font.FaceSize(25);
  glColor3f(15 / 255.0, 15 / 155.0, 15 / 255.0);
  glRasterPos3f(-0.8, 0, 0);
  font.Render("Prajwal D Prakash");
  glRasterPos3f(-0.8, -0.1, 0);
  font.Render("1BY13CS053");

  glRasterPos3f(-0.8, -0.3, 0);
  font.Render("Ravi C");
  glRasterPos3f(-0.8, -0.4, 0);
  font.Render("1BY13CS061");

  font.FaceSize(25);
  glColor3f(50 / 255.0, 50 / 155.0, 50 / 255.0);
  glRasterPos3f(0.4, -0.8, 0);
  font.Render("Right click to continue");
}

void display()
{
  if (splash_screen_displayed == 0) {
    display_splash();
    splash_screen_displayed = 1;
  }
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
