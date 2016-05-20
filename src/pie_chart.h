#ifndef PIE_CHART_H
#define PIE_CHART_H

class PieChart
{
 public:
  void display(GLint);
};

void PieChart::display(GLint numberOfSides=100)
{
  Dataset X;

  DataSetReader reader(1);
  X = reader.read();

  GLfloat sum = 0, cumulative_sum = 0;

  Vertex legend = { 0.8, 0, 0, 1, 1, 1, 1 };
  GLfloat color_r, color_g, color_b;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(20, (float) WINDOW_WIDTH / WINDOW_HEIGHT, 3, 7);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

  for (int k = 0; k < X.size(); k++) {
    sum += X[k].x;
  }

  for (int k = 0; k < X.size(); k++) {
    cumulative_sum += X[k].x;
    X[k].x = cumulative_sum;
  }

  GLfloat x = 0, y = 0, z = 0, radius = 0.5;

  for (int j = 0; j < X.size(); j++) {

    int numberOfVertices = numberOfSides + 2;

    GLfloat angle = 2.0f * M_PI * (X[j].x / sum);

    cout << angle << endl;

    GLfloat circleVerticesX[numberOfVertices];
    GLfloat circleVerticesY[numberOfVertices];
    GLfloat circleVerticesZ[numberOfVertices];

    circleVerticesX[0] = x;
    circleVerticesY[0] = y;
    circleVerticesZ[0] = z;

    for ( int i = 1; i < numberOfVertices; i++ ) {
      circleVerticesX[i] = x + ( radius * cos( i * angle / numberOfSides ) );
      circleVerticesY[i] = y + ( radius * sin( i * angle / numberOfSides ) );
      circleVerticesZ[i] = z;
    }

    GLfloat allCircleVertices[(numberOfVertices) * 3];

    for ( int i = 0; i < numberOfVertices; i++ ) {
      allCircleVertices[i * 3] = circleVerticesX[i];
      allCircleVertices[( i * 3 ) + 1] = circleVerticesY[i];
      allCircleVertices[( i * 3 ) + 2] = circleVerticesZ[i];
    }

    color_r = rand() % 256;
    color_g = rand() % 256;
    color_b = rand() % 256;
    glColor3ub(color_r, color_g, color_b);

    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, allCircleVertices );
    glDrawArrays( GL_TRIANGLE_FAN, 0, numberOfVertices);
    glDisableClientState( GL_VERTEX_ARRAY );

    Primitive::write(X[j].label, legend.x, legend.y, legend.z);
    legend.y -= 0.06;

  }
}

#endif
