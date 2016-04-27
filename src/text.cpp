#include <stdio.h>
#include <GL/glut.h>

void drawBitmapText(char *string,float x,float y)
{
  char *c;
  glRasterPos2f(x, y); // location of the text

  for (c=string; *c != '\0'; c++)
    {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);// displaying in a given font
    }
}

void init()
{
  glClearColor(0.0,0.0,0.0,0.0);
}


void reshape(int w,int h)
{

  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,w,h,0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

}


void render(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glColor3f(0,1,0);
  drawBitmapText("str",200,200);

  glutSwapBuffers();
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

  glutInitWindowSize(500,500);

  glutInitWindowPosition(100,100);
  glutCreateWindow("OpenGL Fonts");

  glutDisplayFunc(render);
  glutIdleFunc(render);
  glutReshapeFunc(reshape);

  glutMainLoop();
  return 0;
}
