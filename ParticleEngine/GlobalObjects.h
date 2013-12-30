// Eric Gummerson	4585469
// DrawObjects.h

// When the user enables the target, a X will appear
void drawUserTarget(float c[3], float width, float height, float depth){
	float w = width;
	float h = height;
	float d = depth;

	// x,y,z in middle		bottom front left			bottom back left			top front left				top back left									
	float verticies[8][3] = {{c[0]-w,c[1]-h,c[2]-d}, {c[0]-w,c[1]-h,c[2]+d}, {c[0]-w,c[1]+h,c[2]-d}, {c[0]-w,c[1]+h,c[2]+d},
							{c[0]+w,c[1]-h,c[2]-d},  {c[0]+w,c[1]-h,c[2]+d}, {c[0]+w,c[1]+h,c[2]-d}, {c[0]+w,c[1]+h,c[2]+d}};	
						//	bottom front right			bottom back right		top front right					top back right	

	
	// One /
	glBegin(GL_POLYGON);
	glColor4f(0.1, 0.2, 0.5, 1.0); // blueish colour
	glVertex3fv(verticies[0]);
	glVertex3fv(verticies[1]);
	glVertex3fv(verticies[7]);
	glVertex3fv(verticies[6]);
	glEnd();
	
	// \ finishes the X
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[2]);
	glVertex3fv(verticies[3]);
	glVertex3fv(verticies[5]);
	glVertex3fv(verticies[4]);
	glEnd();

	// Other way One /
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[3]);
	glVertex3fv(verticies[7]);
	glVertex3fv(verticies[4]);
	glVertex3fv(verticies[0]);
	glEnd();
	
	// Other way  \ finishes the X
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[1]);
	glVertex3fv(verticies[5]);
	glVertex3fv(verticies[6]);
	glVertex3fv(verticies[2]);
	glEnd();
		
}

// Black hole that particles fall through
void drawHole(float c[6]){
	float w = c[3];
	float h = c[4];
	float d = c[5];


	// x,y,z in middle		bottom front left			bottom back left			top front left				top back left									
	float verticies[8][3] = {{c[0]-w,c[1]-h,c[2]-d}, {c[0]-w,c[1]-h,c[2]+d}, {c[0]-w,c[1]+h,c[2]-d}, {c[0]-w,c[1]+h,c[2]+d},
							{c[0]+w,c[1]-h,c[2]-d},  {c[0]+w,c[1]-h,c[2]+d}, {c[0]+w,c[1]+h,c[2]-d}, {c[0]+w,c[1]+h,c[2]+d}};	
						//	bottom front right			bottom back right		top front right					top back right	



	// Top face only
	glBegin(GL_POLYGON);
	glColor4f(0.0, 0.0, 0.0, 1); // black
	glVertex3fv(verticies[2]);
	glVertex3fv(verticies[3]);
	glVertex3fv(verticies[7]);
	glVertex3fv(verticies[6]);
	glEnd();
		
}

// Draw the floor
void drawFloor(float c[6]){
	float w = c[3];
	float h = c[4];
	float d = c[5];

	// x,y,z in middle		bottom front left			bottom back left			top front left				top back left									
	float verticies[8][3] = {{c[0]-w,c[1]-h,c[2]-d}, {c[0]-w,c[1]-h,c[2]+d}, {c[0]-w,c[1]+h,c[2]-d}, {c[0]-w,c[1]+h,c[2]+d},
							{c[0]+w,c[1]-h,c[2]-d},  {c[0]+w,c[1]-h,c[2]+d}, {c[0]+w,c[1]+h,c[2]-d}, {c[0]+w,c[1]+h,c[2]+d}};	
						//	bottom front right			bottom back right		top front right					top back right	


	
	glColor4f(0.2, 0.6, 0, 1); // green
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
	glColor4f(0.5, 0.6, 0, 1);
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

// Spout is a simple box with a circle on the top ish part
void drawSpout(float c[6]){
	float w = c[3];
	float h = c[4];
	float d = c[5];

	// x,y,z in middle		bottom front left			bottom back left			top front left				top back left									
	float verticies[8][3] = {{c[0]-w,c[1]-h,c[2]-d}, {c[0]-w,c[1]-h,c[2]+d}, {c[0]-w,c[1]+h,c[2]-d}, {c[0]-w,c[1]+h,c[2]+d},
							{c[0]+w,c[1]-h,c[2]-d},  {c[0]+w,c[1]-h,c[2]+d}, {c[0]+w,c[1]+h,c[2]-d}, {c[0]+w,c[1]+h,c[2]+d}};	
						//	bottom front right			bottom back right		top front right					top back right	


	
	glColor4f(1, 1, 0, 1);
	// Right Side
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[7]);
	glVertex3fv(verticies[6]);
	glVertex3fv(verticies[4]);
	glVertex3fv(verticies[5]);
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
	glColor4f(0.5, 0.6, 0, 1);
	glVertex3fv(verticies[2]);
	glVertex3fv(verticies[0]);
	glVertex3fv(verticies[4]);
	glVertex3fv(verticies[6]);
	glEnd();
	
	// Left Side
	glBegin(GL_POLYGON);
	glVertex3fv(verticies[1]);
	glVertex3fv(verticies[0]);
	glVertex3fv(verticies[2]);
	glVertex3fv(verticies[3]);
	glEnd();

	// Circle
	glColor4f(1.0, 0.0, 0, 1);
	glTranslatef(c[0], c[1]+h, c[2]);
	glutSolidSphere(5, 15, 15);
	
}


