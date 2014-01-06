// Main.cpp
#define _USE_MATH_DEFINES	// Pi variable

#include <vector>
#include "glut.h"
#include "GlobalObjects.h"
#include "RNG.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "ColDet.h"
#include "Levels.h"
#include <freeimage.h>

RNG randomGen;
ColDet cd;
Levels gameDiff;

/////// Number of bullets ///////
std::vector<Bullet> bList;
/////// Number of particles ///////
std::vector<Enemy> eList;
Player globalPlayer;

// Bullet information
float bulletTimer = 0.05; // Used to maintain 3 of bullets being spawned
int playerBulletType = 1; // Powerups alter the bullet types
float angleOfUser = 0.0;	// Angle to figure out the location of the player on the circle

// Light values, played with them to get a bright green look
float ambientLight[4] = {0.0, 0.0, 0.0, 1.0};
GLfloat qaBlack[] = {0.0, 0.0, 0.0, 1.0}; //Black Color
GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0}; //Green Color
GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0}; //White Color
GLfloat qaRed[] = {1.0, 0.0, 0.0, 1.0}; //White Color 
    // Set lighting intensity and color
GLfloat qaAmbientLight[]    = {0.1, 0.1, 0.1, 1.0};
GLfloat qaDiffuseLight[]    = {1, 1, 1, 1.0};
GLfloat qaSpecularLight[]    = {1.0, 1.0, 1.0, 1.0};
GLfloat emitLight[] = {0.9, 0.9, 0.9, 0.01};
GLfloat Noemit[] = {0.0, 0.0, 0.0, 1.0}; 
GLfloat qaLightPosition[]    = {25, 25, 0, 1};
// Objects in picture	Pos X,Y,Z, Vel X,Y,Z
float pos[5][6] =	{{0, -1, 0, 100, 1, 100},	// Ground position
					{0, 10, 0, 8, 5, 8},		// Spout 
					{-15, 0, 15, 8, 1, 8},		
					{0, 50, 0, 10, 50, 10}, // tower
					{-25, 25, 50, 10, 25, 10}};	//buidling 1

// Coordinates
Coordinate playerSpawn(155.0, 15.0, 0);	// Players spawn position
Coordinate enemySpawn(155.0, 25.0, 0.0);	// Enemy spawn, changes

bool keyStates[256] = {false}; // Create an array of boolean values of length 256 (0-255)  

int backFaceCulling = 0;	// Backface culling 0 means not true

// Camera Related Settings
int axisRotate = 1; // x - 0, y - 1, z - 2, used to rotate around this axis
float angle = 10;
float angleSpeed = 0.0;

// Texture gloabls
void* imgPixels;
int imgWidth;   // Width of the texture image.
int imgHeight;  // Height of the texture image.
GLuint textures[4];


// Light up the screen
void light(){
	 // Enable lighting
   // glEnable(GL_LIGHTING);
   // glEnable(GL_LIGHT0);

     // Set lighting intensity and color
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight); 

	 float materialAmbient[] = {1.0, 1.0, 1.0, 1.0};
	 float materialDiffuse[] = {1.0, 1.0, 1.0, 1.0};
	  float materialSpecular[] = {0.9, 0.9, 0.5, 1.0};
	  float materialShininess[] = { 128.0 };

	 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);	
	 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);	
	 glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);   	 
	// glEnable ( GL_COLOR_MATERIAL ) ;

}

void resetGame(){

	angle = 10;
	axisRotate = 1;
	angleSpeed = 0;			
	globalPlayer.setPosition(playerSpawn);
	angleOfUser = 222.0;
	globalPlayer.addXZMovement(222.0);

	// Remove bullets and enemy lists
	for(size_t i = 0; i < bList.size(); i++){		
		bList.erase(bList.begin() + i);			
	}
	for(size_t i = 0; i < eList.size(); i++){		
		eList.erase(eList.begin() + i);			
	}


	glutPostRedisplay();

}

// Keys operations that will be used a lot - movement and shooting
void keyOperations (void) {  
	if(keyStates['w'] || keyStates['W']){ // Up
		globalPlayer.addYMovement(1.3);
	}
	if(keyStates['s'] || keyStates['S']){ // Down
		globalPlayer.addYMovement(-1.3);
	}
	if(keyStates['a'] || keyStates['A']){ // Left
		angleOfUser += 0.8;
		globalPlayer.addXZMovement(angleOfUser);
	}
	if(keyStates['d'] || keyStates['D']){ // Right
		angleOfUser -= 0.8;
		globalPlayer.addXZMovement(angleOfUser);
	}
	if(keyStates[','] || keyStates['<']){ // Shoot right
		if(bulletTimer < 0.05){
			bulletTimer += 0.20;
			Bullet newBullet(playerBulletType, true, angleOfUser, globalPlayer.getPosition());
			bList.push_back(newBullet);			
		}
	}
	if(keyStates['.'] || keyStates['>']){ // Shoot left
		if(bulletTimer < 0.05){
			bulletTimer += 0.20;
			Bullet newBullet(playerBulletType, false, angleOfUser, globalPlayer.getPosition());
			bList.push_back(newBullet);			
		}
	}

}  

// Creates a new spawn point for enemies on the circle
float newEnemySpawn(){
	float degree = randomGen.random(0.0, 360.0);
	//if( (angleOfUser - degree) < 5 || (angleOfUser - degree) > -5)
	//	degree = angleOfUser + randomGen.random(120.0, 205.0);
	float radian = degree * (M_PI/180);
	enemySpawn.setY(randomGen.random(1, 145));
	enemySpawn.setX(155 * cosf(radian));
	enemySpawn.setZ(155 * sinf(radian));
	return radian;

}

// Function used to spawn enemies depending on the game difficulty
void spawnEnemies(){
	int gd = gameDiff.getDiff(); // Easy/Medium/Hard
	int lvl = gameDiff.getLevel(); // Level
	bool bs = gameDiff.getBoss(); // Boss level
	int eg = eList.size();		// number of enemies in the game so far
	int numS;					// Number of new enemies to spawn
	float an;					// angle of enemy being spawned
	int et = 1;					// Enemy type to spawn
	// Spawn enemies if less than lvl * 5 enemies on the board
	if(eg < lvl * 5){
		numS = (lvl * 5) - eg;
		// Get a new spawn location in the bounds
		
		
		
		switch(gd){
		case 1:		// Easy
			if(lvl > 6)
				et = 3;
			else if(lvl > 3)
				et = 2;
			else
				et = 1;
			
			for(int i = 0; i < numS; i++){
				an = newEnemySpawn();
				if(enemySpawn.getY() > 150)
					enemySpawn.setY(enemySpawn.getY() - 5);
				if(enemySpawn.getY() < 1)
					enemySpawn.setY(enemySpawn.getY() + 5);

				Enemy newEnemy(et, true, an, enemySpawn);
				eList.push_back(newEnemy);				
			}
			break;
		case 2:		// Medium
			if(lvl == 7)
				et = 3;
			else if(lvl == 6)
				et = 2;
			else if(lvl == 5)
				et = 1;
			else if(lvl == 4)
				et = 3;
			else if(lvl == 3)
				et = 3;
			else if(lvl == 2)
				et = 1;
			else
				et = 2;
			
			for(int i = 0; i < numS; i++){
				an = newEnemySpawn();
				if(enemySpawn.getY() > 150)
					enemySpawn.setY(enemySpawn.getY() - 5);
				if(enemySpawn.getY() < 1)
					enemySpawn.setY(enemySpawn.getY() + 5);

				Enemy newEnemy(et, true, an, enemySpawn);
				eList.push_back(newEnemy);				
			}
			break;
		}
		

	}


}


// Called from update, this will function checks the
// lists including, enemy and bullets. Removes them from the lists if they have collided!
void checkLists(){

	// Remove bullets with age == 0
	// This means they have expired or collided
	for(size_t i = 0; i < bList.size(); i++){
		if(bList[i].getAge() == 0){
			// Remove the bullet from the list
			glDisable(GL_LIGHT2);
			bList.erase(bList.begin() + i);			
		}
	}	

	// Remove enemies with age == 0
	// This means they have collided
	for(size_t i = 0; i < eList.size(); i++){
		if(eList[i].getAge() == 0){
			// Remove the enemy from the list
			eList.erase(eList.begin() + i);			
			gameDiff.addKilled(1);
		}
	}	



}

void output(char* text)
{
	int i;
	char* p = text;
	Coordinate pCord(globalPlayer.getPosition());
	//glClear(GL_DEPTH_BUFFER_BIT);
	//glDepthMask(GL_FALSE);

	glPushMatrix();
	
	glDisable(GL_DEPTH_TEST);
glDisable(GL_CULL_FACE);
glDisable(GL_TEXTURE_2D);
glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D( 0, 200 , 0 , 200);
     glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
	//gluLookAt(pP1.getX(), 55, pP1.getZ(), 0, 40, 0, 0, 1, 0);
    glTranslatef(pCord.getX(), pCord.getY()+25 ,0);
	//glRotatef(90, 0.0 , 1.0 , 0.0 );
    glScalef(0.4, 0.4, 0.4);
    for( i =0 ; i < strlen(text); i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, p[i]);
    }	 	
    glPopMatrix();
  //  glMatrixMode(GL_MODELVIEW);
	 // glLoadIdentity();
}


// Display method
void display(void){
	int i;
	char str[15];
	sprintf(str, "%d", gameDiff.getScore());
	//itoa (gameDiff.getScore(),str,10);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	//glOrtho(-200, 200, -75, 125, -100, 350);	
	//glMatrixMode(GL_MODELVIEW);
	// Light it up everytime
	//light();
	keyOperations();
	glLoadIdentity();

	// Camera
	// Look at it bro
	Coordinate pP1(globalPlayer.getPosition());
	Coordinate pP2(globalPlayer.getPosition());

	gluLookAt(pP1.getX(), 55, pP1.getZ(), 0, 40, 0, 0, 1, 0);
	
	


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

	// Draw ground
	glBindTexture(GL_TEXTURE_2D, textures[1]);
    glEnable(GL_TEXTURE_2D);
	glPushMatrix();
    drawFloor(pos[0]);	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaGreen);

   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);

    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 125.0); 
	
  
	// Draw tower

	glPushMatrix();
		glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition); 
	     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLight); 
	drawTower(pos[3], textures);
	  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);
	glPopMatrix();
	//glDisable(GL_TEXTURE_2D);

	// Draw buidling 1
	glBindTexture(GL_TEXTURE_2D, textures[2]);
    glEnable(GL_TEXTURE_2D);
	glPushMatrix();	
	drawBuilding(pos[4]);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	
	// Bullets
	for (size_t i = 0; i < bList.size(); i++){
		glPushMatrix();
		bList[i].Render();
		glPopMatrix();
	}

	// Enemies
	for (size_t i = 0; i < eList.size(); i++){
		glPushMatrix();
		eList[i].Render();
		glPopMatrix();
	}
	
	// Draw player
	glPushMatrix();
	
	globalPlayer.Render();
	glPopMatrix();

	//display score
	glColor4f(1.0, 1.0,  1.0, 1); // white
	output(str);
	
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
			globalPlayer.addXZMovement(222.0);
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
			Enemy newEnemy(1, true, angleOfUser, enemySpawn);
			eList.push_back(newEnemy);
			enemySpawn.setY(enemySpawn.getY() + 3.5);
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
	glutAddMenuEntry("Spawn Enemy 1", 1);
	glutAddMenuEntry("Spawn Enemy 2", 2);
	glutAddMenuEntry("Spawn Enemy 3", 3);


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

// Loads textures
void loadTexture(const char *filename, int textID){

	FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(filename);
	if(format == FIF_UNKNOWN){
        printf("Unknown file type for texture image file %s\n");       
    }

	FIBITMAP* bitmap = FreeImage_Load(format, filename, 0);

	if(!bitmap){
        printf("Failed to load image concrete.png \n");       
    }
	FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap);

	FreeImage_Unload(bitmap);
	imgPixels = FreeImage_GetBits(bitmap2);	// Get the data we need!
    imgWidth = FreeImage_GetWidth(bitmap2);
    imgHeight = FreeImage_GetHeight(bitmap2);

	if (imgPixels) {
		printf("\n Texture image loaded from file %s, size %dx%d\n", filename, imgWidth, imgHeight);
    }else {
        printf("Failed to get texture data from %s \n", filename);
    }

	if(imgPixels){ // The image data exists      		 
		glBindTexture(GL_TEXTURE_2D, textures[textID]);		  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // Linear Min Filter
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // Linear Mag Filter
		// glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		// glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, imgPixels);		 
		glEnable(GL_TEXTURE_2D);     
	}else { // The image data was not loaded, so don't attempt to use the texture.
        glDisable(GL_TEXTURE_2D);
	}
}

// Update the program
void update(int value){
	bool collide = false;
	
	// Update the camera rotation
	angle += angleSpeed;
	
	// Used to avoid unlimited bullets
	if(bulletTimer > 0.05){
		bulletTimer -= 0.025;
	}
	// Update bullets, remove bullets that have expired and collided
	checkLists();

	// Update the bullets
	for (size_t i = 0; i < bList.size(); i++){
		bList[i].Update();
	}
	// Update the enemies
	for (size_t i = 0; i < eList.size(); i++){
		eList[i].Update();
	}

	// Got new positions, now check for collision with enemies
	// First bullets with enemies
	for(size_t i = 0; i < bList.size(); i++){
		for(size_t j = 0; j < eList.size(); j++){
			// Make sure bullets have not expired or collided so far
			if(bList[i].getAge() != 0 && eList[j].getAge() != 0){
				if(cd.collide(bList[i].getPosition(), bList[i].getSize(),
										eList[j].getPosition(), eList[j].getSize())){
					// Collision
											gameDiff.addScore(eList[j].getEnemyType() * 10);
											printf("Score = %d \n", gameDiff.getScore());
					bList[i].setAge(0);
					eList[j].setAge(0);
				}// if collision
			}// if bullet/enemy age != 0

		}// for j
	}// for i

	// Now check if player has hit an enemy
	for(size_t i = 0; i < eList.size(); i++){
		// Check if player has already collided and make sure enemy is not dead
		if(collide == false && eList[i].getAge() != 0){
			if(cd.collide(eList[i].getPosition(), eList[i].getSize(),
				globalPlayer.getPosition(), globalPlayer.getSize())){
					// Collision
					eList[i].setAge(0);
					collide = true;
				}// if collision
		}// If collide and age != 0
	}// For i
	// Update bullets, remove bullets that have expired and collided
	if(collide){
		globalPlayer.addLives(-1);
		if(globalPlayer.numberofLives() != 0)
			globalPlayer.setPlayerStatus(2); // Reviving
		else {
			globalPlayer.setPlayerStatus(3); // Dead
			
		}
		if(globalPlayer.getPlayerStatus() == 3){
			printf("Player has no remaining lives! Game Ended!\n");
			globalPlayer.setLives(3);
			gameDiff.reset();
			resetGame();
		}

	}
	checkLists();
	spawnEnemies();
	// Redisplay the updates
	glutPostRedisplay();
	// Call it again
	glutTimerFunc(10, update, 0);
}

// Basic initalizations
void init(void){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(0, 0, 0, 1);
	glOrtho(-200, 200, -75, 125, -100, 350);	
	//glOrtho(-85, 85, -100, 200, -25, 200);	
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable (GL_BLEND); 
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	glBlendFunc(GL_SRC_COLOR, GL_SRC_ALPHA_SATURATE);
	
	
	glEnable(GL_NORMALIZE);

	//glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHTING);
   // glEnable(GL_LIGHT0);
	initMenus();
	glGenTextures(3, textures); //specify the number of textures
	loadTexture("concrete.png",0);
	loadTexture("grass.png",1);
	loadTexture("brickwall.png",2);
	loadTexture("brickwallb.png",3);
	
}

// Main
int main(int argc, char** argv)
{
	globalPlayer.setPosition(playerSpawn);
	glutInit(&argc, argv);		
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 500);
	glutCreateWindow("LAZER GAME");
	glutDisplayFunc(display);	
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	glutKeyboardUpFunc(keyUp);  
	init();
	
	glutTimerFunc(25, update, 0);
	glutMainLoop();			
	
	return 0;				
}