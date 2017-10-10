#include <GL/glut.h>    
#include <time.h>
#include <iostream>
#include <math.h>
#include <Windows.h>

using namespace std;

#define width 800
#define height 600

#define PI 3.141592
#define RADIAN(X) (PI / 180) * X


///////////////////////////�ݹ��Լ�
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int v);
void Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);//Ű����

 ///////////////�Լ�
void line();
void draw_background(int i); // �׷�
void rotation(int i); // ���� - ��
void size_move(int i);

//////����
float model_x[5] = { 0 }, model_y[5] = { 0 };
int angle[5] = { 0 };
int r[5] = { 0 };
int cnt = 0;
bool move_ok = false;

void main(int argc, char *argv[]) {

	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // ���÷��� ��� ����
	glutInitWindowPosition(100, 100);    // �������� ��ġ���� 
	glutInitWindowSize(width, height);    // �������� ũ�� ����
	glutCreateWindow("2-15");    // ������ ���� (������ �̸�)  
	glutDisplayFunc(drawScene);    // ��� �Լ��� ����
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸� �Լ� ����
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);//Ű����
	glutMouseFunc(Mouse);
	glutMainLoop();
}

GLvoid drawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // ������
	glClear(GL_COLOR_BUFFER_BIT);

	//line(); // ��ǥ��

	glPushMatrix();
	for (int i = 0; i < cnt; ++i)
	{
		glPushMatrix();
		rotation(i);
		if (move_ok)
		{
			size_move(i);
		}
		draw_background(i);
		glPopMatrix();
		if (i == 4)
			break;
	}
	glPopMatrix();


	glFlush(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(-width / 2, width / 2, -height / 2, height / 2, -50, 50);
}


GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
		if (move_ok)
			move_ok = false;
		else
			move_ok = true;
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		r[cnt%5] = 0; angle[cnt%5] = 0;
		model_x[cnt%5] = x - width / 2;
		model_y[cnt%5] = -(y - height / 2);
		cnt++;
	}
}

void TimerFunction(int value) {
	glutPostRedisplay();   // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ���� 
}

void line()
{
	//Y ��
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//����
	glPointSize(1.0f);//���� ũ��
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, -300.0f, 0.0f);//���� ��ǥ
	glVertex3f(0, 300.0f, 0.0f);//���� ��ǥ
	glEnd();
	//X ��
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//����
	glPointSize(1.0f);//���� ũ��
	glBegin(GL_LINE_STRIP);
	glVertex3f(-400.0f, 0.0f, 0.0f);//���� ��ǥ
	glVertex3f(400.0f, 0.0f, 0.0f);//���� ��ǥ
	glEnd();
}

void draw_background(int i)
{	
	switch (i)
	{
	case 0:
		glutWireSphere (r[i], 10, 10); 
		break;

	case 1:
		glutWireTorus(r[i] - 5, r[i]+5, 10, 10);
		break;

	case 2:
		glutSolidSphere(r[i], 10, 10);
		break;

	case 3:
		glutWireTeapot(r[i]);
		break;

	case 4:
		glutWireCone(r[i], r[i]*2, 10, 10);
		break;
	}
		
}

void rotation(int i)
{
	glTranslatef(model_x[i], model_y[i], 0.0);
	if (move_ok)
		glRotatef(angle[i], 0.0, 0.0, 1.0);
	angle[i]++;
}

void size_move(int i)
{
	if (r[i] < 10)
		r[i]++;
}