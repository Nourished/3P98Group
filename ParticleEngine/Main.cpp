// Eric Gummerson	4585469
// Main.cpp
// Main file for the particle engine
// Commands listed when program starts
// NEW GIT SHEET

//PHILLYCHEESE WAS HERE 6474606842

#include <vector>
#include "glut.h"
#include "GlobalObjects.h"
#include "RNG.h"
#include "Player.h"
#include "Bullet.h"
#include "Particle.h"

#include <freeimage.h>

RNG randomGen;

/////// Number of bullets ///////
std::vector<Bullet> bList;
/////// Number of particles ///////
std::vector<Particle> pList;
Player globalPlayer;
// Global information about the game
int numberOfBullets = 0;
int numberOfParticles = 50;
float bulletTimer = 0.4;
int playerBulletType = 1;
float angleOfUser = 0.0;
// Light values, played with them to get a bright green look
float ambientLight[4] = {0.3, .4, 1.0, 1.0};
float lightPos[4] = {90, 70, 0, 1};

// Objects in picture	Pos X,Y,Z, Vel X,Y,Z
float pos[5][6] =	{{0, -1, 0, 100, 1, 100},	// Ground position
					{0, 10, 0, 8, 5, 8},		// Spout 
					{-15, 0, 15, 8, 1, 8},		
					{0, 50, 0, 10, 50, 10}, // tower
					{-25, 25, 50, 10, 25, 10}};	//buidling 1

// X for user controlled particle aiming
Coordinate playerSpawn(155, 15.0, 0);	// Players spawn position

bool keyStates[256] = {false}; // Create an array of boolean values of length 256 (0-255)  
int backFaceCulling = 0;	// Backface culling 0 means not true

// Camera Related Settings
int axisRotate = 1; // x - 0, y - 1, z - 2, used to rotate around this axis
float angle = 10;
float angleSpeed = 0.0;

void* imgPixels;
int imgWidth;   // Width of the texture image.
int imgHeight;  // Height of the texture image.

// Light up the screen
void light(){
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
}

void keyOperations (void) {  
	if(keyStates['w'] || keyStates['W']){ // Up
		globalPlayer.addYMovement(1.0);
	}
	if(keyStates['s'] || keyStates['S']){ // Down
		globalPlayer.addYMovement(-1.0);
	}
	if(keyStates['a'] || keyStates['A']){ // Left
		angleOfUser += 1.2;
		globalPlayer.addXZMovement(angleOfUser);
	}
	if(keyStates['d'] || keyStates['D']){ // Right
		angleOfUser -= 1.2;
		globalPlayer.addXZMovement(angleOfUser);
	}
	if(keyStates[','] || keyStates['<']){ // Shoot right
		if(bulletTimer < 0.05){
			Bullet newBullet(playerBulletType, true, angleOfUser, globalPlayer.getPosition());
			numberOfBullets++;
			bList.push_back(newBullet);
			bulletTimer += 0.20;
		}
	}
	if(keyStates['.'] || keyStates['>']){ // Shoot left
		if(bulletTimer < 0.05){
			Bullet newBullet(playerBulletType, false, angleOfUser, globalPlayer.getPosition());
			numberOfBullets++;
			bList.push_back(newBullet);
			bulletTimer += 0.20;
		}
	}

}  




// Called from update, this will remove bullets that have expired
void checkBullets(){

	// Soft reset, the particle has stopped moving, or off screen
	for(size_t i = 0; i < bList.size(); i++){
		if(bList[i].getAge() == 0){
			// Add new elements to the list
			bList.erase(bList.begin() + i);
			numberOfBullets--;
		}
	}	

}


// Display method
void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	// Light it up everytime
	light();
	keyOperations();
	glLoadIdentity();

	// Camera
	//glPushMatrix();
	//gluLookAt(0, 4, 10, 0, 1, 1, 0, 2, 0);
	// Look at it bro
	Coordinate pP(globalPlayer.getPosition());
	gluLookAt(pP.getX(), pP.getY(), pP.getZ(), 0, pP.getY(), 0, 0, 1, 0);	

	//glPopMatrix();
	// Rotate based on user selection
	switch(axisRotate){
		case 0:
			glRotatef(angle, 1, 0, 0);
			break;
		case 1:
			glRotatef(angle, 0, 1, 0);
			break;
		case 2:
			glRotatef(angle, 0, 0, 1);
			break;
	}
	 //(GL_TEXTURE_2D, 0, GL_RGBA, 
      //      0, 0, 64, 64, 0);
	
	// Draw ground
	glPushMatrix();
    drawFloor(pos[0]);	
	glPopMatrix();	 

	// Draw tower
	glPushMatrix();
	drawTower(pos[3]);
	glPopMatrix();


	// Draw buidling 1
	glPushMatrix();	
	drawBuilding(pos[4]);
	glPopMatrix();

	// Particles (Enemies)
	//for (int i = 0; i < numberOfParticles; i++){
	//	glPushMatrix();
	//	pList[i].Render();
	//	glPopMatrix();
	//}

	// Bullets
	for (int i = 0; i < numberOfBullets; i++){
		glPushMatrix();
		bList[i].Render();
		glPopMatrix();
	}
	
	// Draw player
	glPushMatrix();	
	globalPlayer.Render();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}



void keyUp (unsigned char key, int x, int y) {  
	keyStates[key] = false; // Set the state of the current key to not pressed  
}  

// Keyboard function
void keys(unsigned char key, int x, int y){
	keyStates[key] = true;
	switch(key){

		case 0x1B:	// Quit - free memory
			exit(0);
			return;
			break;
		case 'r':	// Reset keep same amount of particles
							// Reset camera angles, speed, spawn settings
			angle = 10;
			axisRotate = 1;
			angleSpeed = 0;			
			globalPlayer.setPosition(playerSpawn);
			angleOfUser = 222.0;
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
		case '1':	// Add 1 enemy			
			break;		
		case 'b':	// Back face culling
			if(backFaceCulling){
				printf("Back Face Culling Disabled\n");
				glDisable(GL_CULL_FACE);
				backFaceCulling = 0;
			}else {
				printf("Back Face Culling Enabled\n");
				glFrontFace(GL_CCW);
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
				backFaceCulling = 1;
			}
			break;
	}
}


// Menu for the particle type
void menuParticleType(int value){	
	switch(value){
		case 1:
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
	switch(value){
		case 1:
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
	switch(value){
		case 1:			
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

	printf("Particle Engine\nEsc: Quit\nR: Reset\nz: Switch camera angle to rotate around z axis");
	printf("\nx: Switch camera angle to rotate around x axis\n");
	printf("y: Switch camera angle to rotate around y axis\n");
	printf("b: Enable/Disable Back Face Culling\n");
	printf("w: move Y direction up\ns: move Y direction down\na: move player left"
			"\nd: move player right\n");
	printf("MOUSE\nLeft Click: Increase counter clockwise rotation\nRight Click:"
			" Increase clockwise rotation\nMiddle Click to access the menu!\n");
	
	// Particle type menu
	glutCreateMenu(menuParticleType);
	glutAddMenuEntry("Sphere", 1);
	glutAddMenuEntry("Cube", 2);
	glutAddMenuEntry("Wire Sphere", 3);


	// Particle colour menu
	glutCreateMenu(menuColour);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);


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

void loadTexture(){
	FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename("concrete.png");
	if (format == FIF_UNKNOWN) {
        printf("Unknown file type for texture image file %s\n");
       
    }

	 FIBITMAP* bitmap = FreeImage_Load(format, "concrete.png", 0);

	 if (!bitmap) {
        printf("Failed to load image concrete.png \n");       
    }
	  FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap);
	  FreeImage_Unload(bitmap);
	  imgPixels = FreeImage_GetBits(bitmap2);  // Get the data we need!
      imgWidth = FreeImage_GetWidth(bitmap2);
      imgHeight = FreeImage_GetHeight(bitmap2);

	  if (imgPixels) {
        printf("\n Texture image loaded from file concrete.png, size %dx%d\n", 
                          imgWidth, imgHeight);
    }
    else {
        printf("Failed to get texture data from concrete.png \n");
    }

	if ( imgPixels ) { // The image data exists      
		 int format;
         format = GL_RGB;    
         // format = GL_BGR;
		  glBindTexture(GL_TEXTURE_2D, 0);
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // Linear Min Filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // Linear Mag Filter
         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGB,      GL_UNSIGNED_BYTE, imgPixels);
         glEnable(GL_TEXTURE_2D);
     
	} else { // The image data was not loaded, so don't attempt to use the texture.
          glDisable(GL_TEXTURE_2D);
	  }
}

// Update the program
void update(int value){

	// Update bullets, remove bullets that have expired
	checkBullets();
	bulletTimer -= 0.03;

	// Update the camera rotation
	angle += angleSpeed;
			
	// Update the particles
	//for (int i = 0; i < numberOfParticles; i++){
	//	pList[i].Update();
	//}

	// Update the bullets
	for (int i = 0; i < numberOfBullets; i++){
		bList[i].Update();
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
	glOrtho(-75, 75, -100, 200, -25, 200);	
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable (GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	initMenus();
	loadTexture();
}

// Main
int main(int argc, char** argv)
{
	globalPlayer.setPosition(playerSpawn);
	glutInit(&argc, argv);		
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Particle Fountain");
	glutDisplayFunc(display);	
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	glutKeyboardUpFunc(keyUp);  
	init();
	
	glutTimerFunc(25, update, 0);
	glutMainLoop();			
	
	return 0;				
}