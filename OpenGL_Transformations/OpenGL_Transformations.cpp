#include "stdafx.h"
/*
* Copyright (c) 1993-1997, Silicon Graphics, Inc.
* ALL RIGHTS RESERVED
* Permission to use, copy, modify, and distribute this software for
* any purpose and without fee is hereby granted, provided that the above
* copyright notice appear in all copies and that both the copyright notice
* and this permission notice appear in supporting documentation, and that
* the name of Silicon Graphics, Inc. not be used in advertising
* or publicity pertaining to distribution of the software without specific,
* written prior permission.
*
* OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
*/
/*
* robot.c
* This program shows how to composite modeling transformations
* to draw translated and rotated hierarchical models.
* Interaction: pressing the s and e keys (shoulder and elbow)
* alters the rotation of the robot arm.
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
static int shoulder = 0, elbow = 0;
double rotate_y = 0;
double rotate_x = 0;
#define M_PI 3.14159265357
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 1.5, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();

	// This is the part of body
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(2, 0.0, 0.0);
	glPushMatrix();
	glScalef(4.0, 2.2, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(1.0, -1.5, 0.0);
	//glTranslatef(1.0, -1.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	//glTranslatef(1.0, 1.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutWireCube(1.0);
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();

	int rings = 10;
	int sectors = 10;
	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	float radius = 1;
	float v[100][3];
	int s, r, t = 0;

	for (r = 0; r < rings; r++) {
		for (s = 0; s < sectors; s++) {
			//float const z = cos(2 * M_PI * r * R);
			//float const x = sin(2 * M_PI * r * R) * cos(2 * M_PI * s * S);
			//float const y = sin(2 * M_PI * r * R) * sin(2 * M_PI * s * S);

			float const y = sin(-M_PI / 2 + M_PI * r * R);
			float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
			float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

			v[t][0] = x * radius;
			v[t][1] = y * radius;
			v[t][2] = z * radius;

			t++;

		}
	}

	t = 0;
	int index[400];

	for (r = 0; r < rings - 1; r++) {
		for (s = 0; s < sectors; s++) {
			index[4 * t + 0] = r * sectors + s;
			index[4 * t + 1] = r * sectors + (s + 1);
			index[4 * t + 2] = (r + 1) * sectors + (s + 1);
			index[4 * t + 3] = (r + 1) * sectors + s;
			t++;
		}
	}


	for (int i = 0; i < 89; i++)
	{
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glVertex3fv(v[index[4 * i + 0]]);
		glVertex3fv(v[index[4 * i + 1]]);
		glVertex3fv(v[index[4 * i + 2]]);
		glVertex3fv(v[index[4 * i + 3]]);
		glPopMatrix();

	}
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 's':
		shoulder = (shoulder + 5) % 360;
		glutPostRedisplay();
		break;
	case 'w':
		shoulder = (shoulder - 5) % 360;
		glutPostRedisplay();
		break;
	case 'd':
		elbow = (elbow + 5) % 360;
		glutPostRedisplay(); break;
	case 'e':
		elbow = (elbow - 5) % 360;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
