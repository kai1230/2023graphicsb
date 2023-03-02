#include<GL/glut.h>
#include<stdio.h>
float X=0,Y=0,Z=0;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_POLYGON);
      glVertex2f(-0.35, 0.85);
      glVertex2f(-0.52, 0.75);
      glVertex2f(-0.56, 0.58);
      glVertex2f(-0.63, 0.26);
      glVertex2f(-0.44, -0.07);
      glVertex2f(-0.21, -0.21);
      glVertex2f(0.07, -0.19);
      glVertex2f(0.32, -0.05);
      glVertex2f(0.39, 0.43);
      glVertex2f(0.31, 0.69);
      glVertex2f(0.07, 0.81);
      glVertex2f(-0.16, 0.88);
      glVertex2f(-0.37, 0.85);
      glEnd();
    glutSwapBuffers();
}
void mouse(int button,int state,int x,int y)
{
    X=(x-150)/150.0;
    Y=-(y-150)/150.0;
    if(state==GLUT_DOWN)printf("  glVertex2f(%.2f, %.2f);\n",X,Y);
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week03");
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutMainLoop();
}
