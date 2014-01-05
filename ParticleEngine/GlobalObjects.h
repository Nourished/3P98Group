// Eric Gummerson	4585469
// DrawObjects.h
#include "Coordinate.h"

void drawTower(float c[6], GLuint textures[4]){
	float w = c[3];
	float h = c[4];
	float d = c[5];

	glBindTexture(GL_TEXTURE_2D, textures[0]);
    glEnable(GL_TEXTURE_2D);

	// x,y,z in middle		bottom front left			bottom back left			top front left				top back left									
	float verticies[8][3] = {{c[0]-w,c[1]-h,c[2]-d}, {c[0]-w,c[1]-h,c[2]+d}, {c[0]-w,c[1]+h,c[2]-d}, {c[0]-w,c[1]+h,c[2]+d},
							{c[0]+w,c[1]-h,c[2]-d},  {c[0]+w,c[1]-h,c[2]+d}, {c[0]+w,c[1]+h,c[2]-d}, {c[0]+w,c[1]+h,c[2]+d}};	
						//	bottom front right			bottom back right		top front right					top back right	

	
	
	glColor4f(1.0, 1.0,  1.0, 1); // white
	// Right Side
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0, 1.0);
	glVertex3fv(verticies[6]);
	glTexCoord2d(0.0, 0.0);
	glVertex3fv(verticies[4]);
	glTexCoord2d(1.0, 0.0);
	glVertex3fv(verticies[5]);
	glTexCoord2d(1.0, 1.0);
	glVertex3fv(verticies[7]);
	glEnd();
	
	// Back Side
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0, 0.0);
	glVertex3fv(verticies[1]);
	glTexCoord2d(0.0, 1.0);
	glVertex3fv(verticies[3]);
	glTexCoord2d(1.0, 1.0);
	glVertex3fv(verticies[7]);
	glTexCoord2d(1.0, 0.0);
	glVertex3fv(verticies[5]);
	glEnd();

	// Bottom
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[1]);
	glVertex3fv(verticies[0]);
	glVertex3fv(verticies[4]);
	glVertex3fv(verticies[5]);
	glEnd();

	// Top Side
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[2]);
	glVertex3fv(verticies[6]);
	glVertex3fv(verticies[7]);
	glVertex3fv(verticies[3]);
	glEnd();

	// Front Side
	glBegin(GL_POLYGON);	
	glTexCoord2d(0.0, 0.0);
	glVertex3fv(verticies[0]);
	glTexCoord2d(1.0, 0.0);
	glVertex3fv(verticies[4]);
	glTexCoord2d(1.0, 1.0);
	glVertex3fv(verticies[6]);
	glTexCoord2d(0.0, 1.0);
	glVertex3fv(verticies[2]);
	glEnd();
	
	// Left Side	
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0, 0.0);
	glVertex3fv(verticies[1]);
	glTexCoord2d(1.0, 0.0);
	glVertex3fv(verticies[0]);
	glTexCoord2d(1.0, 1.0);
	glVertex3fv(verticies[2]);
	glTexCoord2d(0.0, 1.0);
	glVertex3fv(verticies[3]);
	glEnd();		
	glDisable(GL_TEXTURE_2D);


	   

	// Circle
	glBindTexture(GL_TEXTURE_2D, textures[3]);
    glEnable(GL_TEXTURE_2D);
	glColor4f(1.0, 0.0, 0.0, 1); // red	
	glTranslatef(c[0], c[1]+h, c[2]);
	glRotatef(90 , 1.0 , 0.0, 0.0);	
	glBegin(GL_POLYGON);
	//gluQuadricTexture 
		
	GLUquadric *qobj = gluNewQuadric(); 	
	gluQuadricTexture(qobj, GL_FALSE);
	//gluQuadricDrawStyle(qobj, GLU_FILL); 
	//glPolygonMode(GL_FRONT, GL_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	//glScaled(0.1, 0.1, 0.1);
    //gluCylinder(qobj, 150, 150, 10, 60, 40);
	gluSphere(qobj, 25,15,15);

	//glColor4f(1.0, 0.0, 0.0, 1);
	//glTranslatef(c[0], c[1]+h, c[2]);
	//glutSolidSphere(25, 15, 15);
	//glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_2D);

	// triangle
	glRotatef(-90 , 1.0 , 0.0, 0.0);	
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


	
	glColor4f(1.0, 1.0,  1.0, 1); // white
	// Right Side
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0, 1.0);
	glVertex3fv(verticies[6]);
	glTexCoord2d(0.0, 0.0);
	glVertex3fv(verticies[4]);
	glTexCoord2d(1.0, 0.0);
	glVertex3fv(verticies[5]);
	glTexCoord2d(1.0, 1.0);
	glVertex3fv(verticies[7]);
	glEnd();
	
	// Back Side
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0, 0.0);
	glVertex3fv(verticies[1]);
	glTexCoord2d(0.0, 1.0);
	glVertex3fv(verticies[3]);
	glTexCoord2d(1.0, 1.0);
	glVertex3fv(verticies[7]);
	glTexCoord2d(1.0, 0.0);
	glVertex3fv(verticies[5]);
	glEnd();

	// Bottom
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[1]);
	glVertex3fv(verticies[0]);
	glVertex3fv(verticies[4]);
	glVertex3fv(verticies[5]);
	glEnd();

	// Top Side
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[2]);
	glVertex3fv(verticies[6]);
	glVertex3fv(verticies[7]);
	glVertex3fv(verticies[3]);
	glEnd();

	// Front Side
	glBegin(GL_POLYGON);	
	glTexCoord2d(0.0, 0.0);
	glVertex3fv(verticies[0]);
	glTexCoord2d(1.0, 0.0);
	glVertex3fv(verticies[4]);
	glTexCoord2d(1.0, 1.0);
	glVertex3fv(verticies[6]);
	glTexCoord2d(0.0, 1.0);
	glVertex3fv(verticies[2]);
	glEnd();
	
	// Left Side	
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0, 0.0);
	glVertex3fv(verticies[1]);
	glTexCoord2d(1.0, 0.0);
	glVertex3fv(verticies[0]);
	glTexCoord2d(1.0, 1.0);
	glVertex3fv(verticies[2]);
	glTexCoord2d(0.0, 1.0);
	glVertex3fv(verticies[3]);
	glEnd();	
}

// Draw the floor
void drawFloor(float c[6]){
	
	glColor4f(1.0, 1.0, 0, 1); // green	
	glRotatef(90 , 1.0 , 0.0, 0.0);	
	glBegin(GL_POLYGON);
	//gluQuadricTexture 
		
	GLUquadric *qobj = gluNewQuadric(); 	
	gluQuadricTexture(qobj, GL_TRUE);
	gluQuadricDrawStyle(qobj, GLU_FILL); 
	glPolygonMode(GL_FRONT, GL_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	//glScaled(0.1, 0.1, 0.1);
    gluCylinder(qobj, 150, 150, 10, 60, 40);
    glEnd();
}




