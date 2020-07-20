#include "Visualization.h"

void Visualization::render(const Scan& scan) {

	https://stackoverflow.com/questions/29750264/easiest-way-to-render-3d-points-on-screen-c-windows-visual-studio
	

	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.34, -0.11, 0.01);
	glVertex3f(-0.5, 0.7, -0.9);
	glVertex3f(0.8, 0.5, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0.3, 0.3, 0.2);
	glVertex3f(-0.2, 0.7, 0.32);
	glVertex3f(0.28, -0.53, 0.25);
	glVertex3f(0.93, 0.33, 0.52);
	glVertex3f(0.35, 0.17, -0.19);
	glVertex3f(0.48, -0.85, 0.18);
	glEnd();
	

	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);

	// Line 1
	glVertex3f(0.9f, -0.3f, -0.7f);
	glVertex3f(-0.5f, -0.4f, -0.1f);

	// Line 2
	glVertex3f(-0.5f, -0.4f, -0.3f);
	glVertex3f(-0.9f, -0.8f, -0.1f);

	glEnd();

	
}