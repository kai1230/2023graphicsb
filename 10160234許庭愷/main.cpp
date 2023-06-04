#include <opencv/highgui.h> ///�ϥ� OpenCV 2.1 ���²��, �u�n�� High GUI �Y�i
#include <opencv/cv.h>
#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"
GLMmodel * head = NULL;
GLMmodel * body = NULL; ///GLMmodel * gundam = NULL;
GLMmodel * leftarm1 = NULL, * leftarm2 = NULL;
GLMmodel * rightarm1 = NULL, * rightarm2 = NULL;
GLMmodel * leftfoot = NULL, * rightfoot = NULL;
GLMmodel * leftleg = NULL, * rightleg = NULL;

float teapotX = 0, teapotY = 0, oldX = 0, oldY = 0;
float angle[20] = {}, angle2[20] = {};///float angle = 0, angle2 = 0;
float NewAngle[20] = {}, NewAngle2[20] = {};
float OldAngle[20] = {}, OldAngle2[20] = {};
int ID = 0;
FILE * fout = NULL;
FILE * fin = NULL;

void timer(int t) {
    printf("�{�btimer(%d)\n", t);
    glutTimerFunc(20, timer, t+1); ///���W�]�w�U�@�Ӿx��

    float alpha = (t%50) / 50.0; ///0.0 ~ 1.0

    if(t%50==0){
        if(fin == NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<20; i++){
            OldAngle[i] = NewAngle[i];
            OldAngle2[i] = NewAngle2[i];
            fscanf(fin, "%f", &NewAngle[i] );
            fscanf(fin, "%f", &NewAngle2[i] );
        }
    }
    for(int i=0; i<20; i++){
        angle[i] = NewAngle[i] * alpha + OldAngle[i] * (1-alpha);
        angle2[i] = NewAngle2[i] * alpha + OldAngle2[i] * (1-alpha);
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if(key=='0') ID = 0;
    if(key=='1') ID = 1;
    if(key=='2') ID = 2;
    if(key=='3') ID = 3;
    if(key=='4') ID = 4;
    if(key=='5') ID = 5;
    if(key=='6') ID = 6;
    if(key=='7') ID = 7;
    if(key=='8') ID = 8;
    if(key=='9') ID = 9;
    if(key=='s'){ ///save�s�� �]�|�ʨ��ɮ�
        if(fout == NULL) fout = fopen("motion.txt", "w");
        for(int i=0; i<20; i++){
            fprintf(fout, "%.2f ", angle[i] );
            fprintf(fout, "%.2f ", angle2[i] );
        }
        fprintf(fout, "\n");
        printf("�g�F�@��\n");
    }
    if(key=='r'){ ///readŪ�� �]�|�ʨ��ɮ�
        if(fin == NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<20; i++){
            fscanf(fin, "%f", &angle[i] );
            fscanf(fin, "%f", &angle2[i] );
        }
        glutPostRedisplay();
    }
    if(key=='p'){ ///play���� �]�|�ʨ��ɮ�
        glutTimerFunc(0, timer, 0);
    }
}

int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCVŪ��
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV���m (�ݭncv.h)
    glEnable(GL_TEXTURE_2D); ///1. �}�ҶK�ϥ\��
    GLuint id; ///�ǳƤ@�� unsigned int ���, �s �K��ID
    glGenTextures(1, &id); /// ����Generate �K��ID
    glBindTexture(GL_TEXTURE_2D, id); ///�j�wbind �K��ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// �K�ϰѼ�, �W�L�]�˪��d��T, �N���жK��
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// �K�ϰѼ�, �W�L�]�˪��d��S, �N���жK��
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// �K�ϰѼ�, ��j�ɪ�����, �γ̪��I
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// �K�ϰѼ�, �Y�p�ɪ�����, �γ̪��I
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
void mouse(int button, int state, int x, int y) {
    oldX = x;
    oldY = y;
}
void motion(int x, int y) {
    teapotX += (x - oldX) / 150.0 * 10; ///teapotX = (x-150)/150.0;
    teapotY += (oldY - y) / 150.0 * 10; ///teapotY = (150-y)/150.0;
    angle[ID] += x - oldX;
    angle2[ID] += oldY - y;
    oldX = x;
    oldY = y;
    glutPostRedisplay();
    printf("  glTranslatef( %.2f, %.2f, 0 ); \n", teapotX, teapotY );
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glScalef(1.6,1.6,1.6);
        glTranslatef(0, -0.5, 0);///���U�@�b
        glPushMatrix();
            glColor3f(1,1,1);

            glRotatef(angle[0], 0, 1, 0); ///���骺���
            glScalef(0.04,0.04,0.04);
            glmDraw(body, GLM_MATERIAL|GLM_TEXTURE);///glmDraw(gundam, GLM_MATERIAL|GLM_TEXTURE);

            glPushMatrix();///����
                glTranslatef( -1.93, +14.73, 0 );
                glRotatef(angle[1], 0, 1, 0);
                glRotatef(angle2[1], 1, 0, 0);
                glTranslatef( 1.93, -14.73, 0 );
                ///glTranslatef(teapotX, teapotY, 0);
                ///glColor3f(1,1,0);
                glmDraw(leftarm1, GLM_MATERIAL|GLM_TEXTURE);

                glPushMatrix();
                    glTranslatef( -5.60, +14.53, 0 );
                    glRotatef(angle[2], 0, 1, 0);
                    glRotatef(angle2[2], 1, 0, 0);
                    glTranslatef( 5.60, -14.53, 0 );
                    ///glTranslatef(teapotX, teapotY, 0);

                    glmDraw(leftarm2, GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();
            glPopMatrix();


            glPushMatrix();///�k��
                glTranslatef( +1.80, +14.80, 0 );
                glRotatef(angle[3], 0, 1, 0);
                glRotatef(angle2[3], 1, 0, 0);
                glTranslatef( -1.80, -14.80, 0 );
                ///glTranslatef(teapotX, teapotY, 0);
                glmDraw(rightarm1, GLM_MATERIAL|GLM_TEXTURE);

                glPushMatrix();
                    glTranslatef( +5.40, +14.53, 0 );
                    glRotatef(angle[4], 0, 1, 0);
                    glRotatef(angle2[4], 1, 0, 0);
                    glTranslatef( -5.40, -14.53, 0 );
                    ///glTranslatef(teapotX, teapotY, 0);
                    glmDraw(rightarm2, GLM_MATERIAL|GLM_TEXTURE);
                glPopMatrix();
            glPopMatrix();

            glPushMatrix();
                glTranslatef( -0.07, +16.07, 0 );
                glRotatef(angle[5], 0, 1, 0);
                glRotatef(angle2[5], 1, 0, 0);
                glTranslatef( 0.07, -16.07, 0 );
                ///glTranslatef(teapotX, teapotY, 0);
                glmDraw(head, GLM_MATERIAL|GLM_TEXTURE);
            glPopMatrix();

            glPushMatrix();
                glTranslatef( -1.00, +10.93, 0 );
                glRotatef(angle[6], 0, 1, 0);
                glRotatef(angle2[6], 1, 0, 0);
                glTranslatef( 1.00, -10.93, 0 );
                ///glTranslatef(teapotX, teapotY, 0);
                glmDraw(leftleg, GLM_MATERIAL|GLM_TEXTURE);

                    glPushMatrix();
                        glTranslatef( -1.53, +7.27, 0 );
                        glRotatef(angle[7], 0, 1, 0);
                        glRotatef(angle2[7], 1, 0, 0);
                        glTranslatef( 1.53, -7.27, 0 );
                        ///glTranslatef(teapotX, teapotY, 0);
                        glmDraw(leftfoot, GLM_MATERIAL|GLM_TEXTURE);
                    glPopMatrix();
            glPopMatrix();

            glPushMatrix();
                glTranslatef( +0.80, +10.93, 0 );
                glRotatef(angle[8], 0, 1, 0);
                glRotatef(angle2[8], 1, 0, 0);
                glTranslatef( -0.80, -10.93, 0 );
                ///glTranslatef(teapotX, teapotY, 0);
                glmDraw(rightleg, GLM_MATERIAL|GLM_TEXTURE);

                glPushMatrix();
                    glTranslatef( +1.33, +7.13, 0 );
                    glRotatef(angle[9], 0, 1, 0);
                    glRotatef(angle2[9], 1, 0, 0);
                    glTranslatef( -1.33, -7.13, 0 );
                    ///glTranslatef(teapotX, teapotY, 0);
                    glmDraw(rightfoot, GLM_MATERIAL|GLM_TEXTURE);
                    glPopMatrix();
                glPopMatrix();
    glPopMatrix();




        glColor3f(0,1,0);
        glutSolidTeapot( 0.02);

    glPopMatrix();
    glutSwapBuffers();
}
#include "CMP3_MCI.h"

CMP3_MCI myMP3;
int main(int argc, char** argv)
{
    myMP3.Load("music.mp3");
    myMP3.Play();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("homework");

    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);


    body = glmReadOBJ("model/body.obj"); ///gundam = glmReadOBJ("model/Gundam.obj");
    head = glmReadOBJ("model/head.obj");
    leftarm1 = glmReadOBJ("model/leftarm1.obj");
    leftarm2 = glmReadOBJ("model/leftarm2.obj");
    leftleg = glmReadOBJ("model/leftleg.obj");
    rightarm1 = glmReadOBJ("model/rightarm1.obj");
    rightarm2 = glmReadOBJ("model/rightarm2.obj");
    rightleg = glmReadOBJ("model/rightleg.obj");
    rightfoot = glmReadOBJ("model/rightfoot.obj");
    leftfoot = glmReadOBJ("model/leftfoot.obj");

    myTexture("model/rock.jpg");
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}
