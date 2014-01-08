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
#include "Explode.h"
#include "Powers.h"
#include <freeimage.h>


RNG randomGen;
ColDet cd;
Levels gameDiff;

/////// List of bullets ///////
std::vector<Bullet> bList;
/////// List of enemies ///////
std::vector<Enemy> eList;
/////// List of exploding enemies ///////
std::vector<Explode> explodeList;
/////// List of powerups ///////
std::vector<Powers> pList;
// Player information class
Player globalPlayer;

// Bullet information
float bulletTimer = 0.05; // Used to maintain 3 of bullets being spawned
float angleOfUser = 0.0;	// Angle to figure out the location of the player on the circle

// Light values, played with them to get a bright green look

 // Set emission material colours
GLfloat emitColorRed[] = {1.0, 0.0, 0.0, 1.0};
GLfloat emitColorBlue[] = {0.0, 0.0, 1.0, 1.0};
GLfloat Noemit[] = {0.0, 0.0, 0.0, 1.0}; 

// Objects in picture	Pos X,Y,Z, Vel X,Y,Z
float pos[10][6] =	{{0, -1, 0, 100, 1, 100},	// Ground position
					{0, 10, 0, 8, 5, 8},		// Spout 
					{-15, 0, 15, 8, 1, 8},		//gound
					{0, 50, 0, 10, 50, 10}, // Tower
					{-25, 25, 50, 10, 25, 10},   // Buidling 1
					{25, 25, 50, 10 ,25, 10},    // Buidling 2
					{25, 25, -50, 10, 25, 10},   // Buidling 3 
					{80, 20, 90, 20, 20 , 20},   // Building 4
					{-50, 35, -90, 10, 35 ,10} };// Buidling 5

// Coordinates
Coordinate playerSpawn(155.0, 15.0, 0);	// Players spawn position
Coordinate enemySpawn(155.0, 25.0, 0.0);	// Enemy spawn, changes

bool keyStates[256] = {false}; // Create an array of boolean values of length 256 (0-255)  

int backFaceCulling = 0;	// Backface culling 0 means not true

// Camera Related Settings
int axisRotate = 1; // x - 0, y - 1, z - 2, used to rotate around this axis
float angle = 0;
float angleSpeed = 0.0;

// Game State
int gameState = 1; // 1 - Menu, 2 - Game, 3 - Something else

// Texture gloabls
void* texturePic;
int imgWidth;   // Width of the texture image.
int imgHeight;  // Height of the texture image.
GLuint textures[4];


// Light up the screen
void light(){
	// lighting attributes
	GLfloat lightAmbient[]    = {0.1, 0.1, 0.1, 1.0};
	GLfloat lightDiffuse[]    = {1.0, 1.0, 1.0, 1.0};
	GLfloat lightSpecular[]    = {1.0, 1.0, 1.0, 1.0};
	GLfloat lightPosition1[]    = { -155 , 160, 0, 1};
	GLfloat lightPosition2[]    = { 155 , 160, 155, 1};
	
	//material attributes	
	GLfloat materialGreen[] = {0.0, 1.0, 0.0, 1.0}; //Green Color
	GLfloat materialWhite[] = {1.0, 1.0, 1.0, 1.0}; //White Color
	GLfloat materialRed[] = {1.0 , 0.0, 0.0, 1.0};
	
	// Enable lighting
	
	// Set lighting intensity and color
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular); 
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular); 
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);	
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	//material attributes set
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialGreen);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialRed);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialWhite);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 125.0);	 	 
	glEnable ( GL_COLOR_MATERIAL ) ;

}

void resetGame(){

	gameDiff.reset();
	angle = 0;
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
		angleOfUser += 1.0;
		if(angleOfUser > 360.0)
			angleOfUser = 0.0;
		globalPlayer.addXZMovement(angleOfUser);
	}
	if(keyStates['d'] || keyStates['D']){ // Right
		angleOfUser -= 1.0;
		if(angleOfUser < 0.0)
			angleOfUser = 360.0;
		globalPlayer.addXZMovement(angleOfUser);
	}
	if(keyStates[','] || keyStates['<']){ // Shoot right
		if(bulletTimer < 0.05){
			bulletTimer += 0.25;
			if(globalPlayer.getBullet() == 2){
				// Spawn one in the other direction if 2
				Bullet newBullet2(globalPlayer.getBullet(), false, angleOfUser, globalPlayer.getPosition());
				bList.push_back(newBullet2);	
			}else if(globalPlayer.getBullet() == 3){
				Coordinate bp(globalPlayer.getPosition());
				bp.setY(bp.getY() + 3.0);
				Bullet newBullet2(globalPlayer.getBullet(), true, angleOfUser, bp);
				bList.push_back(newBullet2);	
			}
			Bullet newBullet(globalPlayer.getBullet(), true, angleOfUser, globalPlayer.getPosition());
			bList.push_back(newBullet);			
		}
	}
	if(keyStates['.'] || keyStates['>']){ // Shoot left
		if(bulletTimer < 0.05){
			bulletTimer += 0.25;
			if(globalPlayer.getBullet() == 2){
				// Spawn one in the other direction if 2
				Bullet newBullet2(globalPlayer.getBullet(), true, angleOfUser, globalPlayer.getPosition());
				bList.push_back(newBullet2);	
			}else if(globalPlayer.getBullet() == 3){
				Coordinate bp(globalPlayer.getPosition());
				bp.setY(bp.getY() + 3.0);
				Bullet newBullet2(globalPlayer.getBullet(), false, angleOfUser, bp);
				bList.push_back(newBullet2);	
			}
			Bullet newBullet(globalPlayer.getBullet(), false, angleOfUser, globalPlayer.getPosition());
			bList.push_back(newBullet);			
		}
	}

}  

// Creates a new spawn point for enemies on the circle
float newEnemySpawn(){
	float degree = randomGen.random(0.0, 360.0);
	// Used to make sure enemies dont spawn on user
	int playerSpawnClose =  angleOfUser > degree ? ((int) angleOfUser) - (int) degree: ((int) degree ) - (int) angleOfUser;
	if(playerSpawnClose > 180)
		// Sometimes the player can be at 0-10 and enemy 350-360 and is very close
		playerSpawnClose = 360 - playerSpawnClose;

	if(playerSpawnClose < 5 && playerSpawnClose > -5)
		degree += randomGen.random(15.0, 65.0);
	
	float radian = degree * (M_PI/180);
	enemySpawn.setY(randomGen.random(1, 145));
	enemySpawn.setX(155 * cosf(radian));
	enemySpawn.setZ(155 * sinf(radian));
	return radian;

}

// Spawn power ups based on score
void spawnPowers(){
	
	if(gameDiff.getScore() > gameDiff.getPowerScore()){
		gameDiff.addPowerScore(350 + 80*gameDiff.getLevel());
		Coordinate powerSpawn;
		float degree = randomGen.random(0.0, 360.0);
		float radian = degree * (M_PI/180);
		powerSpawn.setY(randomGen.random(2, 148));
		powerSpawn.setX(155 * cosf(radian));
		powerSpawn.setZ(155 * sinf(radian));
		Powers powerUp(randomGen.random(1, 4), radian, powerSpawn);
		pList.push_back(powerUp);
	}	
}

// Function used to spawn enemies depending on the game difficulty
void spawnEnemies(){

	int gd = gameDiff.getDiff();	// Easy/Medium/Hard
	int lvl = gameDiff.getLevel();	// Level
	int newLvl = gameDiff.Update(); // Updates the level based on how many enemies have been killed
	bool bs = gameDiff.getBoss();	// Boss level
	int eg = eList.size();			// number of enemies in the game so far
	int numS;						// Number of new enemies to spawn
	float an;						// angle of enemy being spawned
	int et = 1;						// Enemy type to spawn
	bool direction;					// Direction to face
	int maxNumEnemies;				// Max Number of enemies to be on the board, based on difficulty, and current level

	// Constantly spawn enemies as long as there is:
	// Not a Boss Level
	// Number of enemies in the game is less than max number of enemies
	maxNumEnemies = 5 + newLvl * gd;	// GD = 1/2/3, levels go 1-10
	if(!bs && eg < maxNumEnemies ){		// NOT A BOSS LEVEL, enemies on screen less than MAX AMOUNT
		numS = maxNumEnemies - eg;
		// Get a new spawn location in the bounds			
		
		switch(gd){
		case 1:		// Easy
			if(lvl > 5)
				et = 5;	// Random enemies
			else if(lvl == 4)
				et = 2;
			else if(lvl == 3)
				et = 3;
			else if(lvl == 2)
				et = 2;
			else
				et = 3;
			for(int i = 0; i < numS; i++){
				// Find a random spawn
				an = newEnemySpawn();
				// Random direction
				if(randomGen.random(0.0, 1.0) > 0.5)
					direction = true;
				else
					direction = false;
				if(enemySpawn.getY() > 150)
					enemySpawn.setY(enemySpawn.getY() - 5);
				if(enemySpawn.getY() < 1)
					enemySpawn.setY(enemySpawn.getY() + 5);
				if(et == 5)
					et = randomGen.random(1,4); // between 1-3

				// Add enemy
				Enemy newEnemy(et, direction, an, enemySpawn);
				eList.push_back(newEnemy);				
			}
			break;
		case 2:		// Medium
		case 3:		// Hard
			if(lvl > 7)
				et = 5;
			else if(lvl == 7)
				et = 3;
			else if(lvl == 6)
				et = 1;
			else if(lvl == 5)
				et = 2;
			else if(lvl == 4)
				et = 5;
			else if(lvl == 3)
				et = 3;
			else if(lvl == 2)
				et = 2;
			else
				et = 1;
			
			for(int i = 0; i < numS; i++){
				// Find a random spawn
				an = newEnemySpawn();
				// Random direction
				if(randomGen.random(0.0, 1.0) > 0.5)
					direction = true;
				else
					direction = false;
				if(enemySpawn.getY() > 150)
					enemySpawn.setY(enemySpawn.getY() - 5);
				if(enemySpawn.getY() < 1)
					enemySpawn.setY(enemySpawn.getY() + 5);
				if(et == 5)
					et = randomGen.random(1,4);
				Enemy newEnemy(et, direction, an, enemySpawn);
				eList.push_back(newEnemy);				
			}
			break;
		}
		

	}else if (bs && eg == 0){	// Spawn boss once all enemies are dead and on level 10

		an = newEnemySpawn();
		// Random direction
		if(randomGen.random(0.0, 1.0) > 0.5)
			direction = true;
		else
			direction = false;
		if(enemySpawn.getY() > 150)
			enemySpawn.setY(enemySpawn.getY() - 5);
		if(enemySpawn.getY() < 1)
			enemySpawn.setY(enemySpawn.getY() + 5);
		
		Enemy newEnemy(4, direction, an, enemySpawn); // Boss spawn
		newEnemy.setBoss(true);
		newEnemy.setBossHealth(50 + (50*gd));	// 100-200 hits depending on difficulty
		newEnemy.setSpeed(1.0 + (0.6*gd));		// Set boss speed
		newEnemy.setSize(14 + (2.0*gd));
		eList.push_back(newEnemy);		

	}else if (bs && eg == 1){	// Boss spawned, move after taking damage
		if(eList[0].getBossHealth() == 0){
			printf("game over! you win!");
			resetGame();
			gameState = 1;
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
			
			bList.erase(bList.begin() + i);			
		}
	}	

	// Remove enemies with age == 0
	// This means they have collided
	for(size_t i = 0; i < eList.size(); i++){
		if(eList[i].getAge() == 0){
			if(!eList[i].getBoss()){	// Non bosses
				// Add exploding particles
				Explode ep(1, eList[i].getAngle(), eList[i].getPosition());
				explodeList.push_back(ep);
				// Remove the enemy from the list
				eList.erase(eList.begin() + i);			
				gameDiff.addKilled(1);
			}else if(eList[i].getBoss()){		// Boss
				Explode ep(4, eList[i].getAngle(), eList[i].getPosition());
				eList[i].relocateBoss();
				eList[i].setAge(1);
			}
		}
	}	

	// Remove explosions
	for(size_t i = 0; i < explodeList.size(); i++){
		if(explodeList[i].getAge() == 0){
			// Remove the explosion from the list
			explodeList.erase(explodeList.begin() + i);			
		}
	}	

	// Remove explosions
	for(size_t i = 0; i < pList.size(); i++){
		if(pList[i].getAge() == 0){
			// Remove the explosion from the list
			pList.erase(pList.begin() + i);			
		}
	}	
}

// Text to the screen
void scoreBoardText(char* score, char* level, char* lives){

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 200 , 0 , 200);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Score
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
    glTranslatef(120, 190 ,0); //set to this position with respect to the size of TEXT
    glScalef(0.05, 0.05, 0.05);
    for(size_t i = 0 ; i < strlen(score); i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, score[i]);
    }	
    glPopMatrix();

	// Level
	glPushMatrix();	
    glTranslatef(120, 180 ,0); //set to this position with respect to the size of TEXT
    glScalef(0.05, 0.05, 0.05);
    for(size_t i = 0 ; i < strlen(level); i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, level[i]);
    }	
    glPopMatrix();

	// Lives
	glPushMatrix();	
    glTranslatef(120, 170 ,0); //set to this position with respect to the size of TEXT
    glScalef(0.05, 0.05, 0.05);
    for(size_t i = 0 ; i < strlen(lives); i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, lives[i]);
    }	
    glPopMatrix();	
}

// Display method
void display(void){

	char str[30];
	char str2[30];
	char str3[30];

	// Gameplay
	if(gameState == 2){
		 
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glEnable (GL_BLEND); 
		glEnable(GL_NORMALIZE);
		glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
		glBlendFunc(GL_SRC_COLOR, GL_SRC_ALPHA_SATURATE);
		
		sprintf(str, "Score %d", gameDiff.getScore());
		if(gameDiff.getLevel() != 10)
			sprintf (str2, "Level: %d", gameDiff.getLevel());
		else
			sprintf (str2, "Level: BOSS");
		sprintf (str3, "Lives: %d", gameDiff.getLives());
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glClearColor(0, 0, 0, 1);
		glOrtho(-200, 200, -75, 125, -100, 350);		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		// Light it up everytime
		light();
		keyOperations();
		glLoadIdentity();

		// Camera
		// Look at it bro
		Coordinate pP1(globalPlayer.getPosition());

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
  
		// Draw tower
		glPushMatrix();		
		drawTower(pos[3], textures);		
		glPopMatrix();

		// Draw buidling 1
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();	
		drawBuilding(pos[4]);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		// Draw buidling 2
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();	
		drawBuilding(pos[5]);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		// Draw buidling 3
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();	
		drawBuilding(pos[6]);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		// Draw buidling 4
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();	
		drawBuilding(pos[7]);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		// Draw buidling 4
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();	
		drawBuilding(pos[8]);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		
		// Bullets
		for(size_t i = 0; i < bList.size(); i++){
			glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitColorRed);
			bList[i].Render();
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);
			glPopMatrix();
		}

		// Enemies
		for(size_t i = 0; i < eList.size(); i++){
			glPushMatrix();
			eList[i].Render();
			glPopMatrix();
		}

		// Explosions
		for(size_t i = 0; i < explodeList.size(); i++){
			glPushMatrix();
			explodeList[i].Render();
			glPopMatrix();
		}

		// Explosions
		for(size_t i = 0; i < pList.size(); i++){
			glPushMatrix();
			pList[i].Render();
			glPopMatrix();
		}
	
		// Draw player
		glPushMatrix();	
		globalPlayer.Render();
		glPopMatrix();

		//display score
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitColorBlue);	
		scoreBoardText(str, str2, str3);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);
	}else if(gameState == 1){		// Menu State
				
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		//glPushMatrix();	
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, 200 , 0 , 200);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Menu Boxes
		drawMainMenuBoxes();
		drawMainMenuText(gameDiff.getDiff());
	}
	//glFlush();
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
			gameState = 1;
			break;
		case '2':	// Add 1 enemy	
			gameState = 2;
			break;	
		case '3':
			gameDiff.setBoss(true);
			gameDiff.setLevel(10);
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
		case '-':
		case '_':
			angleSpeed += 0.1;
			glutPostRedisplay();
			break;
		case '=':
		case '+':
			angleSpeed -= 0.1;
			glutPostRedisplay();
			break;
	}
}

// Menu for the particle type
void menuParticleType(int value){	
	
	float an = newEnemySpawn();
	bool direction;
	// Random direction
	if(randomGen.random(0.0, 1.0) > 0.5)
		direction = true;
	else
		direction = false;
	if(enemySpawn.getY() > 150)
		enemySpawn.setY(enemySpawn.getY() - 5);
	if(enemySpawn.getY() < 1)
		enemySpawn.setY(enemySpawn.getY() + 5);

	Enemy newEnemy(value, direction, an, enemySpawn);
	eList.push_back(newEnemy);	

}

// Menu for quitting
void menuMain(int value){
	if (value == 3)
		exit(0);
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


// Function for the mouse button
// Left click spins counter clockwise
// Right click spins clockwise
void mouse(int button, int state, int x, int y){

	
	if(gameState == 1){ // Menus
		// Check for clicks inside box to start new game
		double dx = (double) x;	// X is normal
		double dy = (double) (glutGet(GLUT_WINDOW_HEIGHT) - y); // Height - y, y starts top to bottom
		// Convert mouse positions into window positions
		dx =  dx / (double) glutGet(GLUT_WINDOW_WIDTH)  * 200;
		dy = dy / (double) glutGet(GLUT_WINDOW_HEIGHT) * 200;
		
		// Check New Game				
		if(dx > 69.0 && dx < 130.0 && dy > 142.0 && dy < 163.0){
			gameState = 2;
			resetGame();
		}
		if(dx > 69.0 && dx < 130.0 && dy > 113.0 && dy < 133.0)
			exit(0);
			
		// Difficulties
		// Easy (40,80) - (70,100)
		if(dx > 39.9 && dx < 69.9 && dy > 83.7 && dy < 103.7)
			gameDiff.setDiff(1);
		// Medium (95,80) - (125,100)
		if(dx > 84.5 && dx < 114.5 && dy > 83.7 && dy < 103.7)
			gameDiff.setDiff(2);
		// Hard (130,80) - (160,100)
		if(dx > 129.7 && dx < 159.7 && dy > 83.7 && dy < 103.7)
			gameDiff.setDiff(3);
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

	// Lighting menu
	glutCreateMenu(menuLight);
	glutAddMenuEntry("On", 1);
	glutAddMenuEntry("Off", 2);

	// Particle other options
	glutCreateMenu(menuMain);
	glutAddSubMenu("Spawn Enemy", 1);
	glutAddSubMenu("Light", 2);
	glutAddMenuEntry("Quit", 3);

	glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

// Loads textures - function is given a file name and texture id
void loadTexture(const char *filename, int textID){

	FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(filename);	

	FIBITMAP* textureUnmodified = FreeImage_Load(format, filename, 0);

	FIBITMAP* textureConverted = FreeImage_ConvertTo24Bits(textureUnmodified);

	FreeImage_Unload(textureConverted);
	texturePic = FreeImage_GetBits(textureConverted);	
	
	if(texturePic){ // if the picture data exists      		 
		glBindTexture(GL_TEXTURE_2D, textures[textID]);		  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // Linear Min Filter
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // Linear Mag Filter	
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, texturePic);		 
		glEnable(GL_TEXTURE_2D);     
	}
}	

// Update the program
void update(int value){

	bool collide = false;	

	// Gameplay update
	if(gameState == 2){
		// Update the camera rotation
		angle += angleSpeed;
	
		// Used to avoid unlimited bullets
		if(bulletTimer > 0.05){
			bulletTimer -= 0.025;
		}
		// Update bullets, remove bullets that have expired and collided
		checkLists();

		globalPlayer.Update();

		// Update the bullets
		for (size_t i = 0; i < bList.size(); i++){
			bList[i].Update();
		}
		// Update the enemies
		for (size_t i = 0; i < eList.size(); i++){
			eList[i].Update(globalPlayer.getPosition(), angleOfUser);
		}
		// Update the explosions
		for (size_t i = 0; i < explodeList.size(); i++){
			explodeList[i].Update();
		}
		// Update the powerups
		for (size_t i = 0; i < pList.size(); i++){
			pList[i].Update();
		}

		// Check powerup collisions first
		// Now check if player has hit an enemy
		for(size_t i = 0; i < pList.size(); i++){
			// Check if player has already collided and make sure enemy is not dead
			if(collide == false && pList[i].getAge() != 0){
				if(cd.collide(pList[i].getPosition(), pList[i].getSize()+2,
					globalPlayer.getPosition(), globalPlayer.getSize())){
						// Collision
						pList[i].setAge(0);	
						switch(pList[i].getPowerType()){
							case 1:
								// DO FIRST POWERUP
								gameDiff.addLives(1);
								break;
							case 2:
								// DO FIRST POWERUP
								globalPlayer.setBullet(2);
								break;
							case 3:
								// DO FIRST POWERUP
								globalPlayer.setBullet(3);
								break;
						}

					}// if collision
			}// If collide
		}// For i

		// Got new positions, now check for collision with enemies
		// bullets with enemies
		for(size_t i = 0; i < bList.size(); i++){
			for(size_t j = 0; j < eList.size(); j++){
				
				// Boss collisions
				if(eList[j].getBoss()){
					if(bList[i].getAge() != 0 && eList[j].getAge() != 0){
						// Make sure bullets have not expired or collided so far
						if(cd.collide(bList[i].getPosition(), bList[i].getSize(),
												eList[j].getPosition(), eList[j].getSize())){
							// Remove boss health
							bList[i].setAge(0);
							eList[j].addBossHealth(-1);
							Explode ep(4, eList[j].getAngle(), eList[j].getPosition());
							explodeList.push_back(ep);
						}
					}
				}else if(bList[i].getAge() != 0 && eList[j].getAge() != 0){
					// Make sure bullets have not expired or collided so far
					if(cd.collide(bList[i].getPosition(), bList[i].getSize(),
											eList[j].getPosition(), eList[j].getSize())){
						// Collision
						gameDiff.addScore(eList[j].getEnemyType() * (10*gameDiff.getDiff()));
						//printf("Score = %d \n", gameDiff.getScore());
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
			gameDiff.addLives(-1);
			if(gameDiff.getLives() == 0)				
				globalPlayer.setPlayerStatus(2); // Dead			
			
			if(globalPlayer.getPlayerStatus() == 2){
				printf("Player has no remaining lives! Game Ended!\n");
				resetGame();
				gameState = 1;
			}

		}
		checkLists();
		spawnEnemies();
		spawnPowers();
	}else if(gameState == 1) {

	}
	// Redisplay the updates
	glutPostRedisplay();
	// Call it again
	glutTimerFunc(10, update, 0);
}

// Basic initalizations - menu setup and loading textures 
void init(void){	

	initMenus();
	glGenTextures(3, textures); //specify the number of textures
	//loadTexture("concrete.png",0);
	//loadTexture("grass.png",1);
	//loadTexture("brickwall.png",2);
	//loadTexture("brickwallb.png",3);
	
}

// Main
int main(int argc, char** argv){

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