#ifndef UTILITY_H
#define UTILITY_H

namespace Utility {
  void menu(int);
  void show_menu();
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
    ScatterPlot3D scatter_plot_3d;
    scatter_plot_3d.display();
    break;

  case 6:
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
  glutAddMenuEntry("Plot", 1);
  glutAddMenuEntry("Bar Graph", 2);
  glutAddMenuEntry("Scatter Plot", 3);
  glutAddMenuEntry("Stem", 4);
  glutAddMenuEntry("3D Scatter Plot", 5);
  glutAddMenuEntry("3D Stem", 6);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

#endif
