#include <GL/glut.h>    
#include <time.h>
#include <iostream>
#include <math.h>
#include <Windows.h>

using namespace std;

#define width 800
#define height 600

///////////////////////////콜백함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int v);
void Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);//키보드

///////////////함수
void init();
void line();
void background(int shape); // 그려
void rotation(); // 공전 - 원
void self_rotation(); // 자전 - 원
void move(int shape); // 배경따라 움직
void draw_player(int player_shape);
void size_move();
void draw();

void dongle();
void sin();
void tornado();
void zig();
void free_line();

//////변수
float player_x = 0, player_y = 0; // 삼각형 좌표
int shape = 0; // 배경도형
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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);    // 윈도우의 위치지정 
	glutInitWindowSize(width, height);    // 윈도우의 크기 지정
	glutCreateWindow("2-12");    // 윈도우 생성 (윈도우 이름)  
	glutDisplayFunc(drawScene);    // 출력 함수의 지정
	glutTimerFunc(100, TimerFunction, 1); // 타이머 함수 설정
	glutKeyboardFunc(Keyboard);//키보드
	glutMouseFunc(Mouse);
	init();
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // 바탕색
	glClear(GL_COLOR_BUFFER_BIT);

	line(); // 좌표축

	glPushMatrix();
	if (shape == 0)
		self_rotation();
	draw_player(player_shape);
	glPopMatrix();

	glFlush(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(-width/2, width/2, -height/2, height/2, -300, 300);
}


GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a': // 삼각
		player_shape = 0;
		break;

	case 'b': // 사각
		player_shape = 1;
		break;

	case 's':
		start = true;
		break;

	case '0': // 원
		shape = 0;
		start = false;
		break;

	case '1': // 사인
		shape = 1;
		start = false;
		break;

	case '2': // 회오리
		shape = 2;
		start = false;
		break;

	case '3': // 지그재그
		shape = 3;
		start = false;
		break;

	case '4': // 자유
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
	glutPostRedisplay();   // 화면 재 출력
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정 
}

void line()
{
	//Y 축
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//점색
	glPointSize(1.0f);//점의 크기
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, -300.0f, 0.0f);//점의 좌표
	glVertex3f(0, 300.0f, 0.0f);//점의 좌표
	glEnd();
	//X 축
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//점색
	glPointSize(1.0f);//점의 크기
	glBegin(GL_LINE_STRIP);
	glVertex3f(-400.0f, 0.0f, 0.0f);//점의 좌표
	glVertex3f(400.0f, 0.0f, 0.0f);//점의 좌표
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
	glColor4f(0.5f, 0.7f, 0.2f, 1.0f); //점색
	switch (player_shape)
	{
	case 0:
		glBegin(GL_POLYGON);
		glVertex3f(player_x - player_size, player_y - player_size, 0.0f);//점의 좌표
		glVertex3f(player_x + player_size, player_y - player_size, 0.0f);//점의 좌표
		glVertex3f(player_x, player_y + player_size, 0.0f);//점의 좌표	
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