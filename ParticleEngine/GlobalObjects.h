// Eric Gummerson	4585469
// DrawObjects.h
#include "Coordinate.h"

void drawTower(float c[6]){
	float w = c[3];
	float h = c[4];
	float d = c[5];

	// x,y,z in middle		bottom front left			bottom back left			top front left				top back left									
	float verticies[8][3] = {{c[0]-w,c[1]-h,c[2]-d}, {c[0]-w,c[1]-h,c[2]+d}, {c[0]-w,c[1]+h,c[2]-d}, {c[0]-w,c[1]+h,c[2]+d},
							{c[0]+w,c[1]-h,c[2]-d},  {c[0]+w,c[1]-h,c[2]+d}, {c[0]+w,c[1]+h,c[2]-d}, {c[0]+w,c[1]+h,c[2]+d}};	
						//	bottom front right			bottom back right		top front right					top back right	


	
	glColor4f(0.5, 0.5, 0.5, 1); 
	// Right Side
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[6]);
	glVertex3fv(verticies[7]);
	glVertex3fv(verticies[5]);
	glVertex3fv(verticies[4]);
	glEnd();
	
	// Back Side
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[1]);
	glVertex3fv(verticies[3]);
	glVertex3fv(verticies[7]);
	glVertex3fv(verticies[5]);
	glEnd();

	// Bottom
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[5]);
	glVertex3fv(verticies[4]);
	glVertex3fv(verticies[0]);
	glVertex3fv(verticies[1]);
	glEnd();

	// Top Side
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[2]);
	glVertex3fv(verticies[3]);
	glVertex3fv(verticies[7]);
	glVertex3fv(verticies[6]);
	glEnd();

	// Front Side
	glBegin(GL_POLYGON);	
	glVertex3fv(verticies[2]);
	glVertex3fv(verticies[6]);
	glVertex3fv(verticies[4]);
	glVertex3fv(verticies[0]);
	glEnd();
	
	// Left Side
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[1]);
	glVertex3fv(verticies[0]);
	glVertex3fv(verticies[2]);
	glVertex3fv(verticies[3]);
	glEnd();	

	// Circle
	glColor4f(1.0, 0.0, 0.0, 1);
	glTranslatef(c[0], c[1]+h, c[2]);
	glutSolidSphere(25, 15, 15);
	// triangle
	glColor4f(1.0, 0.0, 1.0, 1);	
	glTranslatef(0, 35, 0);
	glScalef(2.0, 25.0, 2.0);
	
	glutSolidCube(1.0);

	

}


void drawBuilding(float c[6]){
	float w = c[3];
	float h = c[4];
	float d = c[5];

	// x,y,z in middle		bottom front left			bottom back left			top front left				top back left									
	float verticies[8][3] = {{c[0]-w,c[1]-h,c[2]-d}, {c[0]-w,c[1]-h,c[2]+d}, {c[0]-w,c[1]+h,c[2]-d}, {c[0]-w,c[1]+h,c[2]+d},
							{c[0]+w,c[1]-h,c[2]-d},  {c[0]+w,c[1]-h,c[2]+d}, {c[0]+w,c[1]+h,c[2]-d}, {c[0]+w,c[1]+h,c[2]+d}};	
						//	bottom front right			bottom back right		top front right					top back right	


	
	glColor4f(0.5, 0.3, 0.9, 1); 
	// Right Side
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[6]);
	glVertex3fv(verticies[7]);
	glVertex3fv(verticies[5]);
	glVertex3fv(verticies[4]);
	glEnd();
	
	// Back Side
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[1]);
	glVertex3fv(verticies[3]);
	glVertex3fv(verticies[7]);
	glVertex3fv(verticies[5]);
	glEnd();

	// Bottom
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[5]);
	glVertex3fv(verticies[4]);
	glVertex3fv(verticies[0]);
	glVertex3fv(verticies[1]);
	glEnd();

	// Top Side
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[2]);
	glVertex3fv(verticies[3]);
	glVertex3fv(verticies[7]);
	glVertex3fv(verticies[6]);
	glEnd();

	// Front Side
	glBegin(GL_POLYGON);	
	glVertex3fv(verticies[2]);
	glVertex3fv(verticies[6]);
	glVertex3fv(verticies[4]);
	glVertex3fv(verticies[0]);
	glEnd();
	
	// Left Side
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[1]);
	glVertex3fv(verticies[0]);
	glVertex3fv(verticies[2]);
	glVertex3fv(verticies[3]);
	glEnd();	
}

// Draw the floor
void drawFloor(float c[6]){
	
	glColor4f(1.0, 1.0, 0, 1); // green	
	glRotatef(90 , 1.0 , 0.0, 0.0);
	glBegin(GL_POLYGON);
	GLUquadric *qobj = gluNewQuadric(); 	
    gluCylinder(qobj, 150, 150, 10, 50, 50);
    glEnd();
}




