#include <stdio.h>
#include <GL/glut.h>

void display_bargraph();
void display_pigraph();
void display_graph3();
void init_values();

void menu(int id)
{
  switch(id) {
  case 0: exit(0);
  case 1: display_bargraph();
    break;
  case 2: display_pigraph();
    break;
  case 3: display_graph3();
    break;
  case 4: init_values();
    break;
  }
  glutPostRedisplay();
}

void showmenu()
{
  glutCreateMenu(menu);
  glutAddMenuEntry("exit",0);
  glutAddMenuEntry("bar graph",1);
  glutAddMenuEntry("pi graph",2);
  glutAddMenuEntry("graph3",3);
  glutAddMenuEntry("add values",4);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0,0.0,1.0);
  /* contents of display function */
  glFlush();
}

int main(int argc, char **argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutCreateWindow("menu");
  glutInitWindowSize(500,500);
  showmenu();
  glClearColor(1.0,1.0,1.0,1.0);
  glutDisplayFunc(display);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,499,0,499);
  glutMainLoop();
}

void display_bargraph()
{
  /* enter code here */
}

void display_pigraph()
{
  /* enter the pie graph display code here */
}

void display_graph3()
{
  /* enter the code here */
}

void init_values()
{
  /* enter the values for some variables */
}
