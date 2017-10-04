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

#define big_size 150
#define small_size 20

///////////////////////////�ݹ��Լ�
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int v);
GLvoid Keyboard(unsigned char key, int x, int y);//Ű����

 ///////////////�Լ�
void init();
void line();
void draw_big_semo(); // �׷�
void draw_small_semo();
void move(); // ������ ����
void rotation(int i);
void draw();

////////////����
bool x_start = false;
bool start = false;
float big1[3][2] = { 0 };
float big2[3][2] = { 0 };
int x_angle = 0;
int angle = 0;
float small1_x = 0, small1_y = 0;
float small2_x = 0, small2_y = 0;
float small1[3][2] = { 0 };
float small2[3][2] = { 0 };

int move_cnt1 = 0;
int move_cnt2 = 0;

void main(int argc, char *argv[]) {

	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // ���÷��� ��� ����
	glutInitWindowPosition(100, 100);    // �������� ��ġ���� 
	glutInitWindowSize(width, height);    // �������� ũ�� ����
	glutCreateWindow("2-13");    // ������ ���� (������ �̸�)  
	glutDisplayFunc(drawScene);    // ��� �Լ��� ����
	glutTimerFunc(50, TimerFunction, 1); // Ÿ�̸� �Լ� ����
	init();
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);//Ű����
	glutMainLoop();
}

GLvoid drawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // ������
	glClear(GL_COLOR_BUFFER_BIT);

	line(); // ��ǥ��
	

	glPushMatrix();
	if (start)
		rotation(0);
	if (x_start)
		rotation(1);
	move();
	draw_big_semo();
	draw_small_semo();
	glPopMatrix();


	glFlush(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(-width / 2, width / 2, -height / 2, height / 2, -300, 300);
}


GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
	case 'S':
		start = true;
		break;

	case 'b':
	case 'B':
		x_start = true;
		break;
	}
}

void TimerFunction(int value) {
	glutPostRedisplay();   // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ���� 
}


void init()
{
	big1[0][0] = 0;	big1[0][1] = big_size;
	big1[1][0] = -big_size;	big1[1][1] = -big_size;
	big1[2][0] = big_size;	big1[2][1] = -big_size;

	big2[0][0] = 0;	big2[0][1] = big_size;
	big2[1][0] = -big_size;	big2[1][1] = -big_size;
	big2[2][0] = big_size;	big2[2][1] = -big_size;

	small1_x = big1[0][0]; small1_y = big1[0][1];
	small2_x = big2[0][0]; small2_y = big2[0][1];

	small1[0][0] = 0;	small1[0][1] = small_size;
	small1[1][0] = -small_size;	small1[1][1] = -small_size;
	small1[2][0] = small_size;	small1[2][1] = -small_size;

	small2[0][0] = 0;	small2[0][1] = small_size;
	small2[1][0] = -small_size;	small2[1][1] = -small_size;
	small2[2][0] = small_size;	small2[2][1] = -small_size;

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

void draw_big_semo()
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 3; ++i)
	{
		glColor4f(0.4 + 0.1 * i, 0.6 - 0.1 * i, 0.7 + 0.1 * i, 1.0f);//����
		glVertex3f(big1[i][0], big1[i][1], 0.0f);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 3; ++i)
	{
		glColor4f(0.4 + 0.1 * i, 0.6 - 0.1 * i, 0.7 + 0.1 * i, 1.0f);//����
		glVertex3f(0.0f, big2[i][1], big2[i][0]);
	}
	glEnd();
}

void rotation(int i)
{
	if (i == 1)
	{
		glRotatef(x_angle, 0.0, 0.0, 1.0);
		x_angle += 10;
	}
	else
	{
		glRotatef(angle, 0.0, 1.0, 0.0);
		angle += 10;
	}
}

void draw_small_semo()
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 3; ++i)
	{
		glColor4f(0.7 + 0.1 * i, 0.6 - 0.1 * i, 0.4 + 0.1 * i, 1.0f);//����
		glVertex3f(small1_x + small1[i][0], small1_y + small1[i][1], 0.0f);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 3; ++i)
	{
		glColor4f(0.7 + 0.1 * i, 0.6 - 0.1 * i, 0.4 + 0.1 * i, 1.0f);//����
		glVertex3f(0.0f, small2_y + small2[i][1], small2_x + small2[i][0]);
	}
	glEnd();
}

void move()
{
	float an = (big1[(move_cnt1 + 1) % 3][1] - big1[(move_cnt1) % 3][1])
		/ (big1[(move_cnt1 + 1) % 3][0] - big1[(move_cnt1) % 3][0]);
	float num = small1_y - an * small1_x;

	small1_x += ((big1[(move_cnt1 + 1) % 3][0] - big1[(move_cnt1) % 3][0])
		/ abs(big1[(move_cnt1 + 1) % 3][0] - big1[(move_cnt1) % 3][0])) * 6;
	small1_y = an * small1_x + num;

	//if() // ���������� ��ġ ��Ȯ�� �ű�� my_turn++; my_turn�� 4�� 1�ɶ����� my_turn-- free_turn���� ����
	RECT rect = { big1[(move_cnt1 + 1) % 3][0] - 4, big1[(move_cnt1 + 1) % 3][1] - 4
		, big1[(move_cnt1 + 1) % 3][0] + 4, big1[(move_cnt1 + 1) % 3][1] + 4 };
	RECT range = { small1_x - 2, small1_y - 2, small1_x + 2, small1_y + 2 };
	RECT InterSect;
	if (IntersectRect(&InterSect, &rect, &range)) // �浹�޿�
	{
		small1_x = big1[(move_cnt1 + 1) % 3][0];
		small1_y = big1[(move_cnt1 + 1) % 3][1];
		move_cnt1++;
	}
	
	float an2 = (big2[(move_cnt2 + 1) % 3][1] - big2[(move_cnt2) % 3][1])
		/ (big2[(move_cnt2 + 1) % 3][0] - big2[(move_cnt2) % 3][0]);
	float num2 = small2_y - an2 * small2_x;

	small2_x += ((big2[(move_cnt2 + 1) % 3][0] - big2[(move_cnt2) % 3][0])
		/ abs(big2[(move_cnt2 + 1) % 3][0] - big2[(move_cnt2) % 3][0])) * 8;
	small2_y = an2 * small2_x + num2;

	//if() // ���������� ��ġ ��Ȯ�� �ű�� my_turn++; my_turn�� 4�� 1�ɶ����� my_turn-- free_turn���� ����
	RECT rect2 = { big2[(move_cnt2 + 1) % 3][0] - 4, big2[(move_cnt2 + 1) % 3][1] - 4
		, big2[(move_cnt2 + 1) % 3][0] + 4, big2[(move_cnt2 + 1) % 3][1] + 4 };
	RECT range2 = { small2_x - 2, small2_y - 2, small2_x + 2, small2_y + 2 };
	RECT InterSect2;
	if (IntersectRect(&InterSect2, &rect2, &range2)) // �浹�޿�
	{
		small2_x = big2[(move_cnt2 + 1) % 3][0];
		small2_y = big2[(move_cnt2 + 1) % 3][1];
		move_cnt2++;
	}
	
}