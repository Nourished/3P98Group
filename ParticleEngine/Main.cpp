// Eric Gummerson	4585469
// Main.cpp
// Main file for the particle engine
// Commands listed when program starts
// NEW GIT SHEET

#include <vector>
#include "glut.h"
#include "Particle.h"
#include "GlobalObjects.h"
#include "RNG.h"


RNG randomGen;

/////// Number of particles ///////
std::vector<Particle> pList;
// Global information about the particle list
int numberOfParticles = 20;	// number of particles allowed
int spawnSettings = 1;		// where the particle is spawning and headed
int sizeSettings = 2;		// size
int shapeSettings = 1;		// shape of particle
int colourSettings = 5;		// 5 is random 1-4 red green blue yellow
int tornadoEffect = 0;	// Hurricane effect 0 no, 1 yes
double gSpeed = 5.0;		// Speed

// Light values, played with them to get a bright green look
float ambientLight[4] = {0.3, .4, 1.0, 1.0};
float lightPos[4] = {-20, 25, 15, 1};

// Objects in picture	Pos X,Y,Z, Vel X,Y,Z
float pos[4][6] =	{{0, -1, 0, 65, 1, 65},		// Ground position
					{0, 10, 0, 8, 5, 8},		// Spout 
					{-15, 0, 15, 8, 1, 8}};	// Empty hole

// X for user controlled particle aiming
float userVel[3] = {-25, 15, -20};	// wasd + ef keys controls a point to aim

int backFaceCulling = 0;	// Backface culling 0 means not true

// Camera Related Settings
int axisRotate = 1; // x - 0, y - 1, z - 2, used to rotate around this axis
float angle[3] = {10, 25, 10};
float angleSpeed = 0.0;

// Light up the screen
void light(){
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
}

// Called from update, this will check the particle list
// Remove the particles that have died of age or out of boundaries
// Resize the list if particles were removed from user
// Adds x number of particles to get it back to the proper size
void checkParticles(){

	int numElements = pList.size();	
	// If particles were removed, resize the list
	if(numElements > numberOfParticles)
		pList.resize(numberOfParticles);

	// Soft reset, the particle has stopped moving, or off screen
	for(size_t i = 0; i < pList.size(); i++){
		if(pList[i].isAlive() == 0){
			// Add new elements to the list
			pList.erase(pList.begin() + i);
			// Or reset their position
			//pList[i].resetPosition();
		}
	}

	// Calculate the number of particles in the list and 
	// subtract it from the current particle number allowed
	double p[3];
	double v[3];
	float co[3];	

	numElements = pList.size();
	if(numElements < numberOfParticles){
		// Add x number of particles
		// Give it a the position specified
		for(int i = 0; i < numberOfParticles-numElements; i++){
			Particle newPart;

			// Spawn settings determined by user
			// 1 for normal out of box
			// 2 for out of box but towards a user generated velocity
			// 3 for a small spray
			// 4 for a large spray
			switch(spawnSettings){
				case 1: // default
					p[0]  = randomGen.stdDeviation(pos[1][0], 2.0);
					p[1]  = randomGen.stdDeviation(pos[1][1], 3.0);
					p[2]  = randomGen.stdDeviation(pos[1][2], 2.0);
					// Velocity
					v[0] = randomGen.stdDeviation(-1.7, 5.2);
					v[1]  = randomGen.stdDeviation(21.0, 3.0);
					v[2] = randomGen.stdDeviation(-2.6, 4.0);

					break;
				case 2: // special user
					p[0]  = randomGen.stdDeviation(pos[1][0], 3.0);
					p[1]  = randomGen.stdDeviation(pos[1][1], 3.0);
					p[2]  = randomGen.stdDeviation(pos[1][2], 4.0);
					// Velocity
					v[0] = userVel[0];
					v[1]  = userVel[1];
					v[2] = userVel[2];
					break;
				case 3:
					p[0]  = randomGen.stdDeviation(pos[1][0], 2.0);
					p[1]  = randomGen.stdDeviation(pos[1][1], 3.0);
					p[2]  = randomGen.stdDeviation(pos[1][2], 2.0);
					// Velocity
					v[0] = randomGen.stdDeviation(0, 1.2);
					v[1]  = randomGen.stdDeviation(19.0, 1.0);
					v[2] = randomGen.stdDeviation(3, 0.5);

					break;
				case 4:
					p[0]  = randomGen.stdDeviation(pos[1][0], 2.0);
					p[1]  = randomGen.stdDeviation(pos[1][1], 3.0);
					p[2]  = randomGen.stdDeviation(pos[1][2], 2.0);
					// Velocity
					v[0] = randomGen.stdDeviation(0, 10);
					v[1]  = randomGen.stdDeviation(19.0, 5.0);
					v[2] = randomGen.stdDeviation(0, 10);

					break;
			}

			// Colour settings based on menu
			switch(colourSettings){
				case 1: // default
					co[0] = 1.0;
					co[1] = 0.0;
					co[2] = 0.0;			
				case 2:
					co[0] = 0.0;
					co[1] = 1.0;
					co[2] = 0.0;	
					break;
				case 3:
					co[0] = 0.0;
					co[1] = 0.0;
					co[2] = 1.0;	
					break;
				case 4:
					co[0] = 1.0;
					co[1] = 1.0;
					co[2] = 0.0;	
					break;
				case 5:
					co[0] = randomGen.random(0.01, 1.0);
					co[1] = randomGen.random(0.01, 1.0);
					co[2] = randomGen.random(0.01, 1.0);			
			}

			// Set the values
			newPart.setPosition(p[0], p[1], p[2]);
			newPart.setVelocity(v[0], v[1], v[2]);
			newPart.setColour(co[0], co[1], co[2]);  //Colour
			newPart.setSize(sizeSettings);
			newPart.setParticleType(shapeSettings);
			newPart.setSpeed(randomGen.random(gSpeed-1.5, gSpeed+1.5));
			// Add it to the list
			pList.push_back(newPart);
		}
	}

}


// Display method
void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	// Light it up everytime
	light();
	glLoadIdentity();
	// Look at it bro
	gluLookAt(0, 4, 10, 0, 1, 1, 0, 2, 0);
	// Rotate based on user selection
	switch(axisRotate){
		case 0:
			glRotatef(angle[0], 1, 0, 0);
			break;
		case 1:
			glRotatef(angle[1], 0, 1, 0);
			break;
		case 2:
			glRotatef(angle[2], 0, 0, 1);
			break;
	}
	// Draw ground
	glPushMatrix();
	drawFloor(pos[0]);
	glPopMatrix();
	// Draw spout
	glPushMatrix();
	drawSpout(pos[1]);
	glPopMatrix();
	// Draw black hole
	glPushMatrix();
	drawHole(pos[2]);
	glPopMatrix();

	// Draw user target if the mode is enabled
	if(spawnSettings == 2){
		glPushMatrix();
		drawUserTarget(userVel, 2, 2, 2);
		glPopMatrix();
	}

	// Draw Particles
	for (int i = 0; i < numberOfParticles; i++){
		glPushMatrix();
		// Tornado causes the particles to be skeewed by the camera rotation
		// High speeds cause the particles to bounce and spin in circles
		// on the floor 
		if(tornadoEffect){
			switch(axisRotate){
				case 0:
					glRotatef(angle[0], 1, 0, 0);
					break;
				case 1:
					glRotatef(angle[1], 0, 1, 0);
					break;
				case 2:
					glRotatef(angle[2], 0, 0, 1);
					break;
			}
		}
		// Render the particle and draw it
		pList[i].Render();
		glPopMatrix();
	}
	glFlush();
	glutSwapBuffers();
}

// Keyboard function
void keys(unsigned char key, int x, int y){
	switch(key){

		case 0x1B:	// Quit - free memory
			exit(0);
			return;
			break;
		case 'R':	// Reset to 5 particles
			numberOfParticles = 5;			
		case 'r':	// Reset keep same amount of particles
							// Reset camera angles, speed, spawn settings
			angle[0] = 10;
			angle[1] = 25;
			angle[2] = 10;
			axisRotate = 1;
			angleSpeed = 0;
			spawnSettings = 1;
			colourSettings = 5;
			shapeSettings = 1;
			sizeSettings = 2;
			printf("%d Particles on Screen.  ", numberOfParticles);
			printf("Particles will resume original random behaviour\n");
			for (int i = 0; i < numberOfParticles; i++){
				pList[i].resetPosition();
			}
			glutPostRedisplay();
			break;
		case 'z':	// Change rotation axis to z
			axisRotate = 2;
			printf("Rotating around z axis now!\n");
			break;
		case 'x':	// Change rotation axis to x
			axisRotate = 0;
			printf("Rotating around x axis now!\n");
			break;
		case 'y':	// Change rotation axis to y
			axisRotate = 1;
			printf("Rotating around y axis now!\n");
			break;	
		case 'h':	// Hurricane affect
			if(tornadoEffect == 1){
				printf("TORNADO MODE DISABLED\n");
				tornadoEffect = 0;
				angleSpeed = 0;
			}else {
				printf("TORNADO MODE ENABLED\n");
				tornadoEffect = 1;
				angleSpeed = 0.6;
			}
			break;
		case '`':	// User target
		case '~':
			if(spawnSettings == 1){
				spawnSettings = 2;
				printf("Particles will travel towards the X\n");
			}
			else {
				spawnSettings = 1;
				printf("Particles will resume original random behaviour\n");
			}
			break;
		case 'c':	// Spray mode, hit to toggle between tight and loose
			if(spawnSettings < 3 || spawnSettings == 4){
				spawnSettings = 3;
				printf("Particles will travel in a tight spray\n");
			}
			else if(spawnSettings == 3){
				spawnSettings = 4;
				printf("Particles will travel in a loose spray\n");
			}	
			break;
		case 'w':	// Y Dir Up
			userVel[1] += 0.5;
			break;
		case 's':	// Y Dir Down
			userVel[1] -= 0.5;
			break;
		case 'a':	// X Dir Left
			userVel[0] -= 0.5;
			break;
		case 'd':	// x Dir Right
			userVel[0] += 0.5;
			break;
		case 'e':	// z Dir Far
			userVel[2] -= 0.5;
			break;
		case 'f':	// z Dir Close
			userVel[2] += 0.5;
			break;
		case 'q':	// Add more particles by 3
			numberOfParticles += 3;
			break;
		case '1':	// Add 1 more particle
			numberOfParticles += 1;
			break;
		case 'Q':	// Remove particles
			numberOfParticles -= 5;
			if(numberOfParticles <= 0)
				numberOfParticles = 1;
			break;
		case 'b':	// Back face culling
			if(backFaceCulling){
				printf("Back Face Culling Disabled\n");
				glDisable(GL_CULL_FACE);
				backFaceCulling = 0;
			}else {
				printf("Back Face Culling Enabled\n");
				glFrontFace(GL_CW);
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
				backFaceCulling = 1;
			}
			break;
		case 't':	// Speed of particles increased
			gSpeed += 0.5;
			if(gSpeed > 8)
				gSpeed = 8;
			for (int i = 0; i < numberOfParticles; i++){
				pList[i].setSpeed(randomGen.random(gSpeed, gSpeed+2.0));
			}
			glutPostRedisplay();
			break;
		case 'T':	// Speed of particles decreased
			gSpeed -= 0.5;
			if(gSpeed < 1.0)
				gSpeed = 1.0;
			for (int i = 0; i < numberOfParticles; i++){
				pList[i].setSpeed(randomGen.random(gSpeed-2, gSpeed));
			}
			glutPostRedisplay();
			break;
	}
}

// Menu for the particle type
void menuParticleType(int value){
	shapeSettings = value;
	switch(value){
		case 1:
			for (int i = 0; i < numberOfParticles; i++){
				pList[i].setParticleType(1);
				glPopMatrix();
			}
			break;		
		case 2:
			for (int i = 0; i < numberOfParticles; i++){
				pList[i].setParticleType(2);
				glPopMatrix();
			}
			break;

		case 3:
			for (int i = 0; i < numberOfParticles; i++){
				pList[i].setParticleType(3);
				glPopMatrix();
			}
		break;

		case 4:
			for (int i = 0; i < numberOfParticles; i++){
				pList[i].setParticleType(4);
				glPopMatrix();
			}
		break;

		case 5:
			for (int i = 0; i < numberOfParticles; i++){
				pList[i].setParticleType(5);
				glPopMatrix();
			}
		break;
	}
		
}

// Menu for quitting
void menuMain(int value){
	if (value == 5)
		exit(0);
}

// Menu for the colours
void menuColour(int value){
	colourSettings = value;
	switch(value){
		case 1:
			for (int i = 0; i < numberOfParticles; i++){
				pList[i].setColour(1, 0, 0);
			}
			break;
		case 2:
			for (int i = 0; i < numberOfParticles; i++){
				pList[i].setColour(0, 1, 0);
			}
			break;
		case 3:
			for (int i = 0; i < numberOfParticles; i++){
				pList[i].setColour(0, 0, 1);
			}
			break;
		case 4:
			for (int i = 0; i < numberOfParticles; i++){
				pList[i].setColour(1, 1, 0);
			}
			break;
		case 5:
			for (int i = 0; i < numberOfParticles; i++){
				pList[i].setColour(randomGen.random(0.01, 1.0), randomGen.random(0.01, 1.0),
									randomGen.random(0.01, 1.0));
			}
			break;
	}
}

// Menu for the enabling/disabling lighting
void menuLight(int value){
	switch(value){
		case 1:
			glEnable(GL_LIGHT0);
			break;
		case 2:
			glDisable(GL_LIGHT0);
			break;
	}
}

// Menu for the particle size
void menuSize(int value){
	sizeSettings = value;
	switch(value){
		case 1:
			for (int i = 0; i < numberOfParticles; i++){
					pList[i].setSize(1);
				}
			break;
		case 2:
			for (int i = 0; i < numberOfParticles; i++){
					pList[i].setSize(2);
				}
			break;
		case 3:
			for (int i = 0; i < numberOfParticles; i++){
					pList[i].setSize(3);
				}
			break;
		case 4:
			for (int i = 0; i < numberOfParticles; i++){
					pList[i].setSize(4);
				}
			break;
		case 5:
			for (int i = 0; i < numberOfParticles; i++){
					pList[i].setSize(5);
				}
			break;
	}
}

// Function for the mouse button
// Left click spins counter clockwise
// Right click spins clockwise
void mouse(int button, int state, int x, int y){

	if(button == GLUT_LEFT_BUTTON){
		angleSpeed += 0.1;
		glutPostRedisplay();
	}else if(button == GLUT_RIGHT_BUTTON){
		angleSpeed -= 0.1;
		glutPostRedisplay();
	}
}

// Initalize the menus and print the commands
void initMenus(){

	printf("Particle Engine\nEsc: Quit\nR: Reset the system back to 5 particles\nr: Reset the system with the same number of particles"
			"\nq: Add 3 particles\nQ: Remove 5 particles\n1: Add 1 Particle\n");
	printf("t: Increases speed of the particles\nT: decreases the speed of particles\nh: Enables/Disables the hurricane effect");
	printf("c: Toggle between loose and tight sprays");	
	printf("z: Switch camera angle to rotate around z axis\nx: Switch camera angle to rotate around x axis\n");
	printf("y: Switch camera angle to rotate around y axis\n");
	printf("b: Enable/Disable Back Face Culling\n\n~ enables or disables the user target."
			"This will be a\ntarget on the screen to alter where the particle moves towards\n");
	printf("To change this use\nw: move Y direction up\ns: move Y direction down\na: move X direction"
			" left\nd: move X direction right\n");
	printf("e: move Z direction left\nf: move Z direction right\n");
	printf("MOUSE\nLeft Click: Increase counter clockwise rotation\nRight Click:"
			" Increase clockwise rotation\nMiddle Click to access the menu!\n");
	
	// Particle type menu
	glutCreateMenu(menuParticleType);
	glutAddMenuEntry("Sphere", 1);
	glutAddMenuEntry("Cube", 2);
	glutAddMenuEntry("Wire Sphere", 3);
	glutAddMenuEntry("Wire Cube", 4);
	glutAddMenuEntry("Points", 5);

	// Particle colour menu
	glutCreateMenu(menuColour);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Yellow", 4);
	glutAddMenuEntry("stdDeviationom", 5);

	// Particle size menu
	glutCreateMenu(menuSize);
	glutAddMenuEntry("1", 1);
	glutAddMenuEntry("2", 2);
	glutAddMenuEntry("3", 3);
	glutAddMenuEntry("4", 4);
	glutAddMenuEntry("5", 5);

	// Lighting menu
	glutCreateMenu(menuLight);
	glutAddMenuEntry("On", 1);
	glutAddMenuEntry("Off", 2);

	// Particle other options
	glutCreateMenu(menuMain);
	glutAddSubMenu("Shape", 1);
	glutAddSubMenu("Colour", 2);
	glutAddSubMenu("Size", 3);
	glutAddSubMenu("Light", 4);
	glutAddMenuEntry("Quit", 5);

	glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

// Update the program
void update(int value){

	// Check the particle list
	checkParticles();

	// Update the camera rotation
	switch(axisRotate){
		case 0:
			angle[0] += angleSpeed;
			break;
		case 1:
			angle[1] += angleSpeed;
			break;
		case 2:
			angle[2] += angleSpeed;
			break;
	}
	// Update the particles
	for (int i = 0; i < numberOfParticles; i++){
		pList[i].Update();
	}

	// Redisplay the updates
	glutPostRedisplay();
	// Call it again
	glutTimerFunc(10, update, 0);
}

// Basic initalizations
void init(void){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(1, 1, 1, 1);
	glOrtho(-100, 100, -100, 100, -100, 100);	
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable (GL_BLEND); 
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	initMenus();
	
}

// Main
int main(int argc, char** argv)
{
	// Create a particle list
	for (int i = 0; i < numberOfParticles; i++){
		Particle newPart;	
		newPart.resetPosition();
		pList.push_back(newPart);
	}
	
	glutInit(&argc, argv);		
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Particle Fountain");
	glutDisplayFunc(display);	
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);	
	init();
	
	glutTimerFunc(25, update, 0);
	glutMainLoop();			
	
	return 0;				
}