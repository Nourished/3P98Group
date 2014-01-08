// DrawObjects.h

#include "Coordinate.h"
#pragma once

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
	GLUquadric *qobj = gluNewQuadric(); 	
	gluQuadricTexture(qobj, GL_FALSE);	
	gluQuadricNormals(qobj, GLU_SMOOTH);	
	gluSphere(qobj, 25,15,15);
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
	GLUquadric *qobj = gluNewQuadric(); 	
	gluQuadricTexture(qobj, GL_TRUE);
	gluQuadricDrawStyle(qobj, GLU_FILL); 
	glPolygonMode(GL_FRONT, GL_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluCylinder(qobj, 150, 150, 10, 60, 40);
    glEnd();
}

// Draws boxes around the menu options
void drawMainMenuBoxes(){

	// New Game Box  
	glColor4f(0.0, 1.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(70.0, 140.0);
	glVertex2f(70.0, 160.0);

	glVertex2f(70.0, 160.0);
	glVertex2f(130.0, 160.0);

	glVertex2f(130.0, 160.0);
	glVertex2f(130.0, 140.0);

	glVertex2f(130.0, 140.0);
	glVertex2f(70.0, 140.0);
	glEnd();

	// Quit Box  
	glColor4f(0.0, 1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(70.0, 110.0);
	glVertex2f(70.0, 130.0);

	glVertex2f(70.0, 130.0);
	glVertex2f(130.0, 130.0);

	glVertex2f(130.0, 130.0);
	glVertex2f(130.0, 110.0);

	glVertex2f(130.0, 110.0);
	glVertex2f(70.0, 110.0);
	glEnd();

	// Easy Box (40,80) - (70,100)
	glColor4f(0.0, 0.5, 0.5, 1.0);
	glBegin(GL_LINES);
	glVertex2f(40.0, 80.0);
	glVertex2f(40.0, 100.0);

	glVertex2f(40.0, 100.0);
	glVertex2f(70.0, 100.0);

	glVertex2f(70.0, 100.0);
	glVertex2f(70.0, 80.0);

	glVertex2f(70.0, 80.0);
	glVertex2f(40.0, 80.0);
	glEnd();

	// Medium Box (85,80) - (115,100)
	glColor4f(1.0, 0.5, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(85.0, 80.0);
	glVertex2f(85.0, 100.0);

	glVertex2f(85.0, 100.0);
	glVertex2f(115.0, 100.0);

	glVertex2f(115.0, 100.0);
	glVertex2f(115.0, 80.0);

	glVertex2f(115.0, 80.0);
	glVertex2f(85.0, 80.0);
	glEnd();

	// Hard Box
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(130.0, 80.0);
	glVertex2f(130.0, 100.0);

	glVertex2f(130.0, 100.0);
	glVertex2f(160.0, 100.0);

	glVertex2f(160.0, 100.0);
	glVertex2f(160.0, 80.0);

	glVertex2f(160.0, 80.0);
	glVertex2f(130.0, 80.0);
	glEnd();
	
}


void drawMainMenuText(int gd){

	char *text = "New Game";
	// New Game  (70,140) - (130,160)
	glPushMatrix();	
	glTranslatef(82, 150 ,0); //set to this position with respect to the size of TEXT
	glColor3f(1.0, 0.0, 0.0);
	glScalef(0.05, 0.05, 0.05);
	for(size_t i = 0 ; i < strlen(text); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
	}	
	glPopMatrix();

	// Quit (70,110) - (130,130)
	text = "Quit";
	glPushMatrix();	
	glTranslatef(92, 120 ,0); //set to this position with respect to the size of TEXT
	glScalef(0.05, 0.05, 0.05);
	for(size_t i = 0 ; i < strlen(text); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
	}	
	glPopMatrix();

	// Easy (40,80) - (70,100)	
	
	if(gd == 1)
		text = "Easy !";
	else
		text = "Easy";
		
	glPushMatrix();	
	glColor3f(0.0, 0.5, 0.5);
	glTranslatef(44, 90 ,0); //set to this position with respect to the size of TEXT
	glScalef(0.05, 0.05, 0.05);
	for(size_t i = 0 ; i < strlen(text); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
	}	
	glPopMatrix();

	// Medium (95,80) - (125,100)
	if(gd == 2)
		text = "Medium !";
	else
		text = "Medium";
	glPushMatrix();
	glColor3f(1.0, 0.5, 0.0);
	glTranslatef(85, 90 ,0); //set to this position with respect to the size of TEXT
	glScalef(0.05, 0.05, 0.05);
	for(size_t i = 0 ; i < strlen(text); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
	}	
	glPopMatrix();

	// Hard (130,80) - (160,100)
	if(gd == 3)
		text = "Hard !";
	else
		text = "Hard";
	glPushMatrix();	
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(134, 90 ,0); //set to this position with respect to the size of TEXT
	glScalef(0.05, 0.05, 0.05);
	for(size_t i = 0 ; i < strlen(text); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
	}	
	glPopMatrix();
}

