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


///////////////////////////콜백함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int v);
void Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);//키보드

 ///////////////함수
void line();
void draw_background(int i); // 그려
void rotation(int i); // 공전 - 원
void size_move(int i);

//////변수
float model_x[5] = { 0 }, model_y[5] = { 0 };
int angle[5] = { 0 };
int r[5] = { 0 };
int cnt = 0;
bool move_ok = false;

void main(int argc, char *argv[]) {

	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);    // 윈도우의 위치지정 
	glutInitWindowSize(width, height);    // 윈도우의 크기 지정
	glutCreateWindow("2-15");    // 윈도우 생성 (윈도우 이름)  
	glutDisplayFunc(drawScene);    // 출력 함수의 지정
	glutTimerFunc(100, TimerFunction, 1); // 타이머 함수 설정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);//키보드
	glutMouseFunc(Mouse);
	glutMainLoop();
}

GLvoid drawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // 바탕색
	glClear(GL_COLOR_BUFFER_BIT);

	//line(); // 좌표축

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


	glFlush(); // 화면에 출력하기
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