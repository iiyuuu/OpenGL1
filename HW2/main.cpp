/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#if __APPLE__
    #include <GLUT/glut.h>
#else
    #include <glut.h>
#endif

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1};
int windowWidth = 800, windowHeight = 600;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {
    // TODO: Your code here!
	for (int i = 0; i < 10; i++) {
		int theta = 36 * i;
		glPushMatrix();
		glRotatef(theta, 0, 0, 1);//angle and which axis to rotate around
		glTranslatef(1, 0, 0);//translate the entire matrix 
		glutSolidTeapot(0.25);
		glPopMatrix();
	}
	
}

void problem2() {
    // TODO: Your code here!
	//for loop 
	float size = 1.0/4.0;//4 units over 16 steps
	float scale = 1.0;
	float move = -2;
	for (float i = 0.0; i < 16; i++) {
		glPushMatrix();
		scale = scale + 3 * i/128;//gets bigger each step til its 4x bigger
		glScalef(1, scale, 3);//ups the y-axis

		glTranslatef(move, size/2, size/2);//up so the corner is against the origin
		move += size;//move to the right each step
		glutSolidCube(size);
		glPopMatrix();
	}
}

void problem3() {
    // TODO: Your code here!
	//probably odd number and even in a separate loop

	bool matrix[6][11] = {};

	int num_rows = 6;
	double num_cols = 11.0;
	float left_bound = -2.5;
	float top_bound = 1.0;

	for (int row = 0; row < num_rows; row++) {
		int num_spaces = num_rows - row - 1;
		//float start_point = (-num_cols - 1)/ 4.0;
		int col = 0;
		for (col; col < num_spaces; col++) {
			matrix[row][col] = false;
		}

		for (int iter = 0; iter <= row; iter++) {
			matrix[row][col] = true;
			col++;
			if (col < num_cols) {
				matrix[row][col] = false;
				col++;
			}
			
		}
	}

	for (int row = 0; row < num_rows; row++) {
		for (int col = 0; col < num_cols; col++){
			glPushMatrix();
			glTranslatef(left_bound + col/2.0, top_bound - row/2.0, 0);
			if (matrix[row][col]) {
				glutSolidTeapot(0.25);
			}
			glPopMatrix();
		}
	}
}

void problem4() {
	// TODO: Your code here! star finger!


	glColor3f(0.578f, 0.0f, 0.824);
	glDisable(GL_LIGHTING);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.25f, 0.27f, -0.25f);
	glVertex3f(0.25f, 0.27f, -0.25f);
	glVertex3f(0.0f, 0.27f, 0.25f);
	glEnd();
	
	glEnable(GL_LIGHTING);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, 0);
	glScalef(1, 2, 1);
	glutSolidCube(0.5);
	glPopMatrix();

	//thumb joint 1
	glPushMatrix();
	glScalef(1, 1, 2);
	glRotatef(-15, 0, 1, 0);
	glTranslatef(0.25, 0, 0.25);
	glutSolidCube(0.15);
	glPopMatrix();

	//thumb joint 2
	glPushMatrix();
	glScalef(2, 1, 1);
	glTranslatef(0, 0, 0.85);
	glutSolidCube(0.15);
	glPopMatrix();

	glPushMatrix();
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		if (i < 2){
			glScalef(1, 1, 2);
			glTranslatef(-0.27 + 0.17 * i, 0.2, 0.3);
		}
		else {
			glTranslatef(-0.27 + 0.17 * i, 0.2, 1.25);
			glScalef(1, 1, 12);

		}
		glutSolidCube(0.15);
		glPopMatrix();

		glPushMatrix();
		if (i < 2) {
			glScalef(1, 2, 1);
			glTranslatef(-0.27 + 0.17 * i, 0, 0.75);
			glutSolidCube(0.15);
			glPopMatrix();
		}
		glPushMatrix();
		if (i < 2) {
			glScalef(1, 1, 1.5);
			glTranslatef(-0.27 + 0.17 * i, -0.1, 0.45);
			glutSolidCube(0.15);
			glPopMatrix();
		}
	}
	glPopMatrix();

}

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
		glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis
		glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis
		glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot,0,1,0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
