#include <GL/glut.h>    
#include <time.h>
#include <iostream>
#include <math.h>
#include <Windows.h>

using namespace std;

#define width 800
#define height 600

///////////////////////////�ݹ��Լ�
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int v);
void Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);//Ű����

///////////////�Լ�
void init();
void line();
void background(int shape); // �׷�
void rotation(); // ���� - ��
void self_rotation(); // ���� - ��
void move(int shape); // ������ ����
void draw_player(int player_shape);
void size_move();
void draw();

void dongle();
void sin();
void tornado();
void zig();
void free_line();

//////����
float player_x = 0, player_y = 0; // �ﰢ�� ��ǥ
int shape = 0; // ��浵��
int player_shape = 0;
float player_size = 20;
float free_dot[5][2] = { 0 };
float dot[1000][2] = { 0 };

bool start = false; bool bigger = false;
int mouse_count = 0;
int angle = 0;

void main(int argc, char *argv[]) {

	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // ���÷��� ��� ����
	glutInitWindowPosition(100, 100);    // �������� ��ġ���� 
	glutInitWindowSize(width, height);    // �������� ũ�� ����
	glutCreateWindow("2-12");    // ������ ���� (������ �̸�)  
	glutDisplayFunc(drawScene);    // ��� �Լ��� ����
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸� �Լ� ����
	glutKeyboardFunc(Keyboard);//Ű����
	glutMouseFunc(Mouse);
	init();
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // ������
	glClear(GL_COLOR_BUFFER_BIT);

	line(); // ��ǥ��

	glPushMatrix();
	if (shape == 0)
		self_rotation();
	draw_player(player_shape);
	glPopMatrix();

	glFlush(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(-width/2, width/2, -height/2, height/2, -300, 300);
}


GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a': // �ﰢ
		player_shape = 0;
		break;

	case 'b': // �簢
		player_shape = 1;
		break;

	case 's':
		start = true;
		break;

	case '0': // ��
		shape = 0;
		start = false;
		break;

	case '1': // ����
		shape = 1;
		start = false;
		break;

	case '2': // ȸ����
		shape = 2;
		start = false;
		break;

	case '3': // �������
		shape = 3;
		start = false;
		break;

	case '4': // ����
		shape = 4;
		start = false;
		for (int i = 0; i < 5; ++i)
		{
			free_dot[i][0] = 0;
			free_dot[i][1] = 0;
		}
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (shape == 4 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		free_dot[mouse_count][0] = x;
		free_dot[mouse_count][1] = y;
		mouse_count++;
	}
}

void TimerFunction(int value) {
	size_move();
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

void init()
{
	mouse_count = 0;
	angle = 0;
	start = false;
	player_x = 0, player_y = 0;
	player_size = 20;
}

void background(int shape)
{
	switch (shape)
	{
	case 0:

		break;

	case 1:

		break;

	case 2:

		break;

	case 3:

		break;

	case 4:

		break;
	}

}

void self_rotation()
{
	glTranslatef(player_x, player_y, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glTranslatef(-player_x, -player_y, 0.0);
	angle+=5;
}

void move(int shape)
{
	switch (shape)
	{
	case 0:
		//player_x = 
		//player_y = 
		break;

	case 1:

		break;

	case 2:

		break;

	case 3:

		break;

	case 4:

		break;
	}
}

void draw_player(int player_shape)
{
	glColor4f(0.5f, 0.7f, 0.2f, 1.0f); //����
	switch (player_shape)
	{
	case 0:
		glBegin(GL_POLYGON);
		glVertex3f(player_x - player_size, player_y - player_size, 0.0f);//���� ��ǥ
		glVertex3f(player_x + player_size, player_y - player_size, 0.0f);//���� ��ǥ
		glVertex3f(player_x, player_y + player_size, 0.0f);//���� ��ǥ	
		glEnd();
		break;

	case 1:
		glRectf(player_x - player_size, player_y - player_size, player_x + player_size, player_y + player_size);
		break;
	}
}

void size_move()
{
	if (player_size < 10)
		bigger = true;
	else if (player_size > 25)
		bigger = false;

	if (bigger)
		player_size *= 1.1;
	else
		player_size *= 0.9;
}