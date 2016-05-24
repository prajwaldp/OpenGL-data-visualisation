#ifndef UTILITY_H
#define UTILITY_H

namespace Utility {
  void menu(int);
  void show_menu();
  void set_perspective();
  void set_orthographic();
}

void Utility::menu(int id) {
  switch(id) {

  case 0: exit(0);

  case 1:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Plot plot;
    plot.display();
    break;

  case 2:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    BarGraph bar_graph;
    bar_graph.display();
    break;

  case 3:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ScatterPlot scatter_plot;
    scatter_plot.display();
    break;

  case 4:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Stem stem;
    stem.display();
    break;

  case 5:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Plot3D plot_3d;
    plot_3d.display();
    break;

  case 6:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ScatterPlot3D scatter_plot_3d;
    scatter_plot_3d.display();
    break;

  case 7:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PieChart pie_chart;
    pie_chart.display();
    break;
  }

  glutPostRedisplay();
}

void Utility::show_menu() {
  glutCreateMenu(Utility::menu);
  glutAddMenuEntry("Quit", 0);
  glutAddMenuEntry("Plot", 1);
  glutAddMenuEntry("Bar Graph", 2);
  glutAddMenuEntry("Scatter Plot", 3);
  glutAddMenuEntry("Stem", 4);
  glutAddMenuEntry("3D Plot", 5);
  glutAddMenuEntry("3D Scatter Plot", 6);
  glutAddMenuEntry("Pie Chart", 7);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Utility::set_orthographic()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //Orthographic Projection
  glOrtho(-1.f, -1.f, -1.f, 1.f, 1.f, -1.f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Utility::set_perspective()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, (float) WINDOW_WIDTH / WINDOW_HEIGHT, 1, 1000);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 500, 0, 0, 0, 0, 1, 0);
}

#endif
