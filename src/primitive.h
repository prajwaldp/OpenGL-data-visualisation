#ifndef PRIMITIVE_H
#define PRIMITIVE_H

namespace Primitive {
  void point(Vertex, GLfloat);
  void line(Vertex, Vertex, GLfloat);
  void unfilled_quad(Vertex, Vertex, Vertex, Vertex, GLfloat);
  void filled_quad(Vertex, Vertex, Vertex, Vertex);
  void unfilled_cube(Vertex, Vertex, Vertex, Vertex, Vertex, Vertex, Vertex, Vertex, GLfloat);
  void write(string, GLfloat, GLfloat, GLfloat, string, string);
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

void Primitive::write(string text, GLfloat x, GLfloat y, GLfloat z=0, string align="left", string size="small") {
  int i;
  glColor4f(0, 0, 0, 1);

  glRasterPos3f(x, y, z);

  for (i = 0; text[i] != '\0'; i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    glutBitmapWidth(GLUT_BITMAP_HELVETICA_12, 20);
  }
}

#endif
