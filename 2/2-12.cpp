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

#define start_point -250

///////////////////////////�ݹ��Լ�
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int v);
void Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);//Ű����

///////////////�Լ�
void init();
void line();
void draw_background(int shape); // �׷�
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

//////����
float player_x = 0, player_y = 0; // �ﰢ�� ��ǥ
int shape = 0; // ��浵��
int player_shape = 0;
float player_size = 20;
float free_dot[5][2] = { 0 };
float dot[1000][2] = { 0 };
float dot_x = 0, dot_y = 0;
int move_cnt = 0;
int my_turn = 1;


bool bigger = false;
bool zig_turn = false;
bool turn = false;
bool free_turn = false;
int mouse_count = 0;
float angle = 0;


void main(int argc, char *argv[]) {

	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // ���÷��� ��� ����
	glutInitWindowPosition(100, 100);    // �������� ��ġ���� 
	glutInitWindowSize(width, height);    // �������� ũ�� ����
	glutCreateWindow("2-12");    // ������ ���� (������ �̸�)  
	glutDisplayFunc(drawScene);    // ��� �Լ��� ����
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸� �Լ� ����
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);//Ű����
	glutMouseFunc(Mouse);
	init();	shape = 0; dongle();
	glutMainLoop();
}

GLvoid drawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // ������
	glClear(GL_COLOR_BUFFER_BIT);

	line(); // ��ǥ��
	draw_background(shape);

	glPushMatrix();
	if (shape == 0 || shape == 2)
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
		
	case '0': // ��
		init();
		shape = 0;
		dongle();
		break;

	case '1': // ����
		init();
		shape = 1;
		sin();
		break;

	case '2': // ȸ����
		init();
		shape = 2;
		tornado();
		break;

	case '3': // �������
		init();
		shape = 3;
		zig();
		break;

	case '4': // ����
		init();
		shape = 4;
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
		free_dot[mouse_count % 6][0] = x - width/2;
		free_dot[mouse_count % 6][1] = -(y - height/2);
		if (mouse_count % 6 == 0)
		{
			player_x = free_dot[mouse_count % 6][0];
			player_y = free_dot[mouse_count % 6][1];
			my_turn = 1; free_turn = false;
		}
		mouse_count++;


	}
}

void TimerFunction(int value) {
	size_move();
	move(shape);
	glutPostRedisplay();   // ȭ�� �� ���
	if (shape == 4)
		glutTimerFunc(20, TimerFunction, 1); // Ÿ�̸��Լ� �� ���� 
	else
		glutTimerFunc(10, TimerFunction, 1); // Ÿ�̸��Լ� �� ���� 
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
	player_x = 0, player_y = 0;
	player_size = 20;
	dot_x = 0, dot_y = 0;
	move_cnt = 0;
	turn = false;
	my_turn = 1;
}

void draw_background(int shape)
{
	switch (shape)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		glPointSize(1.0f);//���� ũ��
		glBegin(GL_POINTS);

		for (int i = 0; i < 1000; ++i)
		{
			glColor4f(0.4f, i / 1100.f, i / 1100.f, 1.0f);//����
			glVertex3f(dot[i][0], dot[i][1], 0.0f);//���� ��ǥ
		}
		glEnd();
		break;
	case 4:
		glBegin(GL_LINE_STRIP);

		for (int i = 0; i < mouse_count%6; ++i)
		{
			glColor4f(0.4f, 0.7f, 0.8f, 1.0f);//����
			glVertex3f(free_dot[i][0], free_dot[i][1], 0.0f);//���� ��ǥ
		}
		glEnd();
		break;
	}

}

void self_rotation()
{
	glTranslatef(player_x, player_y, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glTranslatef(-player_x, -player_y, 0.0);
	if (shape == 0)
		angle -= 0.36;
	else if (shape == 2 && turn == false)
		angle -= 1;
	else if (shape == 2 && turn == true)
		angle += 1;
}

void move(int shape)
{
	switch (shape)
	{
	case 0:
		player_x = dot[move_cnt % 1000][0];
		player_y = dot[move_cnt % 1000][1];
		move_cnt++;
		break;
	case 1:
	case 2:
	case 3:
		player_x = dot[move_cnt % 1000][0];
		player_y = dot[move_cnt % 1000][1];
		if (move_cnt == 1000 && turn == false)
			turn = true;
		else if (move_cnt == 0 && turn == true)
			turn = false;

		if (turn)
			move_cnt--;
		else
			move_cnt++;
		break;

	case 4:
		if (mouse_count % 6 == 5)
		{
			if (free_turn == false)
			{
				float an = (free_dot[my_turn][1] - free_dot[my_turn - 1][1])
					/ (free_dot[my_turn][0] - free_dot[my_turn - 1][0]);
				float num = player_y - an * player_x;

				player_x += ((free_dot[my_turn][0] - free_dot[my_turn - 1][0])
					/ abs(free_dot[my_turn][0] - free_dot[my_turn - 1][0])) * 2;
				player_y = an * player_x + num;

				//if() // ���������� ��ġ ��Ȯ�� �ű�� my_turn++; my_turn�� 4�� 1�ɶ����� my_turn-- free_turn���� ����
				RECT rect = { free_dot[my_turn][0] - 2, free_dot[my_turn][1] - 2
				, free_dot[my_turn][0] + 2, free_dot[my_turn][1] + 2 };
				RECT range = { player_x - 2, player_y - 2, player_x + 2, player_y + 2 };
				RECT InterSect;
				if (IntersectRect(&InterSect, &rect, &range)) // �浹�޿�
				{
					player_x = free_dot[my_turn][0];
					player_y = free_dot[my_turn][1];
					if (my_turn == 4)
					{
						free_turn = true;
					}
					else
						my_turn++;
				}
			}	
			else if (free_turn == true)
			{
				float an2 = (free_dot[my_turn-1][1] - free_dot[my_turn][1])
					/ (free_dot[my_turn-1][0] - free_dot[my_turn][0]);
				float num2 = player_y - an2 * player_x;

				player_x += ((free_dot[my_turn-1][0] - free_dot[my_turn][0])
					/ abs(free_dot[my_turn-1][0] - free_dot[my_turn][0])) * 2;
				player_y = an2 * player_x + num2;

				//if() // ���������� ��ġ ��Ȯ�� �ű�� my_turn++; my_turn�� 4�� 1�ɶ����� my_turn-- free_turn���� ����
				RECT rect2 = { free_dot[my_turn-1][0] - 2, free_dot[my_turn-1][1] - 2
					, free_dot[my_turn-1][0] + 2, free_dot[my_turn-1][1] + 2 };
				RECT range2 = { player_x - 2, player_y - 2, player_x + 2, player_y + 2 };
				RECT InterSect;
				if (IntersectRect(&InterSect, &rect2, &range2)) // �浹�޿�
				{
					player_x = free_dot[my_turn-1][0];
					player_y = free_dot[my_turn-1][1];
					if (my_turn == 1)
					{
						free_turn = false;
					}
					else
						my_turn--;
				}
			}
			
		}
		break;
	}
}

void draw_player(int player_shape)
{
	switch (player_shape)
	{
	case 0:
		glBegin(GL_POLYGON);
		glColor4f(0.8f, 0.5f, 0.5f, 1.0f); //����
		glVertex3f(player_x - player_size, player_y - player_size, 0.0f);//���� ��ǥ
		glColor4f(0.7f, 0.8f, 0.7f, 1.0f); //����
		glVertex3f(player_x + player_size, player_y - player_size, 0.0f);//���� ��ǥ
		glColor4f(0.4f, 0.6f, 0.9f, 1.0f); //����
		glVertex3f(player_x, player_y + player_size, 0.0f);//���� ��ǥ	
		glEnd();
		break;

	case 1:
		glBegin(GL_POLYGON);
		glColor4f(0.8f, 0.5f, 0.5f, 1.0f); //����
		glVertex3f(player_x - player_size, player_y - player_size, 0.0f);//���� ��ǥ
		glColor4f(0.7f, 0.7f, 0.7f, 1.0f); //����
		glVertex3f(player_x + player_size, player_y - player_size, 0.0f);//���� ��ǥ
		glColor4f(0.4f, 0.7f, 0.6f, 1.0f); //����
		glVertex3f(player_x + player_size, player_y + player_size, 0.0f);//���� ��ǥ
		glColor4f(0.2f, 0.6f, 0.9f, 1.0f); //����
		glVertex3f(player_x - player_size, player_y + player_size, 0.0f);//���� ��ǥ
		glEnd();
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
		player_size *= 1.05;
	else
		player_size *= 0.95;
}

void dongle()
{
	angle = 0;
	for (int i = 0; i < 1000; ++i)
	{
		dot[i][0] = 200 * sin(RADIAN(angle));
		dot[i][1] = 200 * cos(RADIAN(angle));
		angle += 0.36;
	}
}

void sin()
{
	for (int i = 0; i<1000; ++i)
	{
		dot_x += 0.54;
		dot_y = sin(RADIAN(dot_x)) * 100;

		dot[i][0] = start_point + dot_x;
		dot[i][1] = dot_y;
	}
}

void tornado()
{
	float r = 0;
	angle = 0;
	for (int i = 0; i < 1000; ++i)
	{
		dot[i][0] = r * sin(RADIAN(angle));
		dot[i][1] = r * cos(RADIAN(angle));
		angle += 1;
		r += 0.2;
	}
}

void zig()
{
	for (int i = 0; i<1000; ++i)
	{
		dot_x += 0.5;

		if (i % 200 == 0)
		{
			if (zig_turn)
				zig_turn = false;
			else
				zig_turn = true;
		}
		if (zig_turn)
			dot_y += 1;
		else
			dot_y -= 1;

		dot[i][0] = start_point + dot_x;
		dot[i][1] = -100+dot_y;
	}
}
