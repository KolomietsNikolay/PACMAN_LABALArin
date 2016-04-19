#include <GL\glut.h>
#include <math.h>
#include <windows.h>
#pragma comment(lib, "winmm.lib")

float ax, ay, x, y;
bool mbb = false, mbf = false, mbl = false, mbr = false, mbrotx = false, mbroty = false;

void PaintM()
{
	glLineWidth(4);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 0.0);
	double r = 0.1;
	double dx = -0.1;
	double dy = 0.1;

	for (int i = 0; dx <= 0.08; i++){

		dx += 0.001;
		double dyy = sqrt(pow(0.1, 2) - pow(dx, 2))-0.01;

		glVertex2f(dx, dy + dyy);
	}
	glEnd();


	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 0.0);
	 r = 0.1;
	 dx = -0.1;
	 dy = 0.1;

	for (int i = 0; dx <= 0.08; i++){

		dx += 0.001;
		double dyy = sqrt(pow(0.1, 2) - pow(dx, 2)) - 0.015;

		glVertex2f(dx, dy - dyy);
	}
	glEnd();
}

void PaintPreg()
{
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1, -0.65, 0.0);
	glVertex3f(-0.8, -0.65, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-0.8, 1, 0.0);
	glVertex3f(-1, 1, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-0.4, -1, 0.0);
	glVertex3f(-0.4, 0.65, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0.65, 0.0);
	glVertex3f(0, -1, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.25, -0.75, 0.0);
	glVertex3f(0.45, -0.75, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.45, 0.95, 0.0);
	glVertex3f(0.25, 0.95, 0.0);
	glEnd();
}

void DrawSq()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (mbrotx)ax += 0.05;
	if (mbroty)ax -= 0.05;
	if (mbb)y -= 0.0001;
	if (mbf)y += 0.0001;
	if (mbl)x -= 0.0001;
	if (mbr)x += 0.0001;

	if (x <= -0.7 && y >= -0.85){
		x = -500; y = -500;
		mciSendString(L"stop E:\\fon.mp3", NULL, 0, NULL);
		mciSendString(L"play E:\\crash.wav wait", NULL, 0, NULL);
	}

	if ((x >= -0.5 && x <= 0.1) && y <= 0.65){
		x = -500; y = -500;
		mciSendString(L"stop E:\\fon.mp3", NULL, 0, NULL);
		mciSendString(L"play E:\\crash.wav wait", NULL, 0, NULL);
		
	}

	if ((x >= 0.15 && x <= 0.55) && y >= -0.95){
		x = -500; y = -500;
		mciSendString(L"stop E:\\fon.mp3", NULL, 0, NULL);
		mciSendString(L"play E:\\crash.wav wait", NULL, 0, NULL);
	}
	if (x > 0.6 && x < 0.8)
	{
		mciSendString(L"stop E:\\fon.mp3", NULL, 0, NULL);
		mciSendString(L"play E:\\win.mp3", NULL, 0, NULL);
		x += 0.2;
	}
	//if (x >= 0.7 && y <= 0.85)x -= 0.001;
	PaintPreg();

	

	glPushMatrix();
	//PaintM();


	glTranslatef(x, y, 0);
	glRotatef(ax, 0, 0, 1);
	PaintM();

	glPopMatrix();
	glutSwapBuffers();
}

void keypres(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		mbrotx = true;
		break;
	case 's':
		mbroty = true;
		break;
	}
}

void keyUnpress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		mbrotx = false;
		break;

	case 's':
		mbroty = false;
		break;
	}
}

void special(int k, int x, int y)
{
	switch (k)
	{
	case GLUT_KEY_LEFT:
		mbl = true;
		break;
	case GLUT_KEY_RIGHT:
		mbr = true;
		break;
	case GLUT_KEY_UP:
		mbf = true;
		break;
	case GLUT_KEY_DOWN:
		mbb = true;
		break;

	}
}


void specialUp(int k, int x, int y)
{
	switch (k)
	{
	case GLUT_KEY_LEFT:
		mbl = false;
		break;
	case GLUT_KEY_RIGHT:
		mbr = false;
		break;
	case GLUT_KEY_UP:
		mbf = false;
		break;
	case GLUT_KEY_DOWN:
		mbb = false;
		break;

	}
}

void Initialize()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

int curWin;

void Idle(void)
{
	glutPostWindowRedisplay(curWin);
}

void visible(int vis)
{
	glutIdleFunc(Idle);
}

int main(int iArgc, char **cppArgv)
{

	x = -0.9;
	y = -0.9;
	ax = 0;
	ay = 0;

	mciSendString(L"play E:\\fon.mp3", NULL, 0, NULL);

	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(250, 200);
	glutCreateWindow("4 Laba");
	Initialize();
	glutDisplayFunc(DrawSq);

	glutVisibilityFunc(visible);
	glutKeyboardFunc(keypres);
	glutKeyboardUpFunc(keyUnpress);

	glutSpecialFunc(special);
	glutSpecialUpFunc(specialUp);

	curWin = glutGetWindow();

	glutMainLoop();
	return 0;
}