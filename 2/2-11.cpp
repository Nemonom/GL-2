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
GLvoid Keyboard(unsigned char key, int x, int y);//키보드
void SpecialKeyboard(int key, int x, int y);

///////////////함수
void line();
void init(); 
void sin();
void cos();
void spring();
void nemo();
void draw();
void rotation();
void move(int what);
void move_sin();
void move_cos();
void move_spring();
///////////////전역변수

int asdf = 0;
float move_dot_x = 0;
float move_dot_y = 0;
int rotation_x = 0;
int rotation_y = 0;
int rotation_z = 0;


#define PI 3.141592
#define RADIAN(X) (PI / 180) * X

//좌표저장
GLfloat sin_point[1000][2];
GLfloat cos_point[1000][2];
GLfloat spring_point[2000][2];
GLfloat nemo_point[10][2];

//점
GLfloat sin_x = 0.0f, sin_y = 0.0f;
GLfloat cos_x = 0.0f, cos_y = 0.0f;
GLfloat spring_x = 0.0f, spring_y = 0.0f;
GLfloat nemo_x = 0.0f;

//시작점
#define start_x 200
#define start_sin_y 150
#define start_cos_y 250
#define start_spring_y 350
#define start_nemo_y 500
#define nemo_size 15

float scale = 1;
bool rotate_x = false, rotate_y = false, rotate_z = false;
bool ani = false;


void main(int argc, char *argv[]) {

	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);    // 윈도우의 위치지정 
	glutInitWindowSize(width, height);    // 윈도우의 크기 지정
	glutCreateWindow("2-11");    // 윈도우 생성 (윈도우 이름)  
	glutDisplayFunc(drawScene);    // 출력 함수의 지정
	glutTimerFunc(100, TimerFunction, 1); // 타이머 함수 설정
	init();
	glutKeyboardFunc(Keyboard);//키보드
	glutSpecialFunc(SpecialKeyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // 바탕색
	glClear(GL_COLOR_BUFFER_BIT);	

	line(); // 좌표축
	glPushMatrix();
	rotation(); // 회전
	draw(); // 그래프 그림
	glPopMatrix();

	glFlush(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(0, width, height, 0, -300, 300);
}

void SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		move(1);
		break;

	case GLUT_KEY_RIGHT:
		move(2);
		break;
	}
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		if (rotate_x)
			rotate_x = false;
		else
			rotate_x = true;
		break;

	case 'y':
		if (rotate_y)
			rotate_y = false;
		else
			rotate_y = true;
		break;

	case 'z':
		if (rotate_z)
			rotate_z = false;
		else
			rotate_z = true;
		break;

	case 'S':
		scale += 0.2;
		move_dot_x = 200 - sin_point[0][0] * scale;
		move_dot_y = 150 - sin_point[0][1] * scale;
		break;

	case 's':
		scale -= 0.2;
		move_dot_x = 200 - sin_point[0][0] * scale;
		move_dot_y = 150 - sin_point[0][1] * scale;
		break;

	case 'A':
		ani = false;
		break;

	case 'a':
		ani = true;
		break;

	case 'i':
		init();
		glLoadIdentity();
		Reshape(width, height);
		break;

	case 'q':
		PostQuitMessage(0);
		break;

	}
}

void TimerFunction(int value) {
	
	if (ani)
	{
		asdf += 1;
		move_sin();
		move_cos();
		move_spring();
	}
	glutPostRedisplay();   // 화면 재 출력
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정 
}

void line()
{
	//Y 축
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//점색
	glPointSize(1.0f);//점의 크기
	glBegin(GL_LINE_STRIP);
	glVertex3f(400.0f, 0.0f, 0.0f);//점의 좌표
	glVertex3f(400.0f, 600.0f, 0.0f);//점의 좌표
	glEnd();
	//X 축
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//점색
	glPointSize(1.0f);//점의 크기
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f, 300.0f, 0.0f);//점의 좌표
	glVertex3f(800.0f, 300.0f, 0.0f);//점의 좌표
	glEnd();
}

void init()
{
	ani = false, rotate_x = false, rotate_y = false, rotate_z = false;
	sin_x = 0.0f, sin_y = 0.0f;
	cos_x = 0.0f, cos_y = 0.0f;
	spring_x = 0.0f, spring_y = 0.0f;
	nemo_x = 0.0f;
	move_dot_x = 0, move_dot_y = 0;
	scale = 1; asdf = 0;

	rotation_x = 0, rotation_y = 0, rotation_z = 0;

	sin();
	cos();
	spring();
	nemo();
}

void sin()
{
	sin_x = 0;
	sin_y = 0;

	for (int i = 0; i<1000; ++i)
	{
		sin_x += 0.4;
		sin_y = sin(RADIAN(sin_x)) * 30;
		//sin_y = sin(RADIAN(sin_x + asdf)) * 30;

		sin_point[i][0] = start_x + sin_x;
		sin_point[i][1] = start_sin_y + sin_y;
	}
}
void cos()
{
	cos_x = 0; cos_y = 0;

	for (int i = 0; i<1000; ++i)
	{
		cos_x += 0.4;
		cos_y = cos(RADIAN(cos_x)) * 30;
		//cos_y = cos(RADIAN(cos_x + asdf)) * 30;

		cos_point[i][0] = start_x + cos_x;
		cos_point[i][1] = start_cos_y + cos_y;
	}
}
void draw()
{
	glPointSize(1.0f);//점의 크기
	glBegin(GL_POINTS);

	for (int i = 0; i < 1000; ++i)
	{
		glColor4f(1 - i / 1000.f, i / 1000.f, 1 - i / 1000.f, 1.0f);//점색
		glVertex3f(sin_point[i][0] * scale + move_dot_x * 2, sin_point[i][1] * scale + move_dot_y * 2, 0.0f);//점의 좌표
		glVertex3f(cos_point[i][0] * scale + move_dot_x * 2, cos_point[i][1] * scale + move_dot_y * 2, 0.0f);//점의 좌표
	}
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 1600; ++i)
	{
		glColor4f(1 - i / 1600.f, i / 1600.f, 1 - i / 1600.f, 1.0f);//점색
		glVertex3f(spring_point[i][0] * scale + move_dot_x * 2, spring_point[i][1] * scale + move_dot_y * 2, 0.0f);//점의 좌표
	}
	glEnd();

	for (int i = 0; i < 10; ++i)
	{
		glColor4f(1 - i / 10.f, i / 10.f, 1 - i / 10.f, 1.0f);//점색
		glRectf(nemo_point[i][0] - nemo_size, nemo_point[i][1] - nemo_size
			, nemo_point[i][0] + nemo_size, nemo_point[i][1] + nemo_size);
	}
	
}

void spring()
{
	float radius = 50;//반지름
	float Nums = 0;//x증가분

	for (int i = 0; i<1600; ++i)
	{
		spring_point[i][0] = (cos(RADIAN(i))*radius) + 550 + Nums;
		//spring_point[i][0] = (cos(RADIAN(i + asdf))*radius) + 550 + Nums;
		spring_point[i][1] = (sin(RADIAN(i))*radius) + start_spring_y;
		//spring_point[i][1] = (sin(RADIAN(i + asdf))*radius) + start_spring_y;

		Nums -= 0.2;
	}
}

void nemo()
{
	nemo_x = 0.0f;

	for (int i = 0; i < 10; i++)
	{
		nemo_x += 40;
		nemo_point[i][0] = start_x + nemo_x;
		nemo_point[i][1] = start_nemo_y;
	}
}

void rotation()
{
	if (rotate_x)
	{
		glTranslatef(400, 300, 0.0);
		glRotatef(rotation_x, 1.0, 0.0, 0.0); 
		glTranslatef(-400, -300, 0.0);
		rotation_x += 10;
	}

	if (rotate_y)
	{
		glTranslatef(400, 300, 0.0);
		glRotatef(rotation_y, 0.0, 1.0, 0.0);
		glTranslatef(-400, -300, 0.0);

		rotation_y += 10;
	}

	if (rotate_z)
	{
		glTranslatef(400, 300, 0.0);
		glRotatef(rotation_z, 0.0, 0.0, 1.0);
		glTranslatef(-400, -300, 0.0);
		rotation_z += 10;
	}
}

void move(int what)
{
	switch (what)
	{
	case 1: // left
		for (int i = 0; i < 1000; ++i)
		{
			sin_point[i][0] -= 5;
			cos_point[i][0] -= 5;
		}
		for (int i = 0; i < 1600; ++i)
		{
			spring_point[i][0] -= 5;
		}
		for (int i = 0; i < 10; ++i)
		{
			nemo_point[i][0] -= 5;
		}
		break;

	case 2: //right
		for (int i = 0; i < 1000; ++i)
		{
			sin_point[i][0] += 5;
			cos_point[i][0] += 5;
		}
		for (int i = 0; i < 1600; ++i)
		{
			spring_point[i][0] += 5;
		}
		for (int i = 0; i < 10; ++i)
		{
			nemo_point[i][0] += 5;
		}
		break;
	}

}

void move_sin()
{	
	sin_x = 0;
	for (int i = 0; i<1000; ++i)
	{
		sin_x += 0.4;
		sin_y = sin(RADIAN(sin_x + asdf)) * 30;
		sin_point[i][1] = start_sin_y + sin_y;
	}
}
void move_cos()
{
	cos_x = 0;
	for (int i = 0; i<1000; ++i)
	{
		cos_x += 0.4;
		cos_y = cos(RADIAN(cos_x + asdf)) * 30;
		cos_point[i][1] = start_cos_y + cos_y;
	}
}

void move_spring()
{
	float radius = 50;//반지름

	for (int i = 0; i<1600; ++i)
	{
		spring_point[i][1] = (sin(RADIAN(i + asdf))*radius) + start_spring_y;
	}
}