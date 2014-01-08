// Enemy.cpp


#define _USE_MATH_DEFINES	// Pi variable

#include "Enemy.h"
#include "glut.h"
#include <cstdlib>
#include <cstdio>
#include <math.h>

GLfloat emitLightRed[] = {1.0, 0.0, 0.0, 1.0};
GLfloat emitLightGreen[] = {0.0, 1.0, 0.0, 1.0};
GLfloat emitLightBlue[] = {0.0, 0.0, 1.0, 1.0};
GLfloat NoEmission[] = {0.0, 0.0, 0.0, 1.0}; 

Enemy::~Enemy(){
}

// Inital Enemy generation set fields
Enemy::Enemy(int bType, bool d, float angleStart, Coordinate p){
	pos = p;
	angle = angleStart;
	dir = d;
	enemyType = bType;
	age = 1;
	alpha = 1.0;
	enemy2Rotation = 0.0;
	enemy3Rotation = 0.0;
	bossRotation = 0.0;
	boss = false;

	switch(enemyType){
		case 1:	// Default Enemy
			colour[0] = 0.0;
			colour[1] = 1.0;
			colour[2] = 0.0;
			speed = 0.4;
			size = 4;
			break;
		case 2:	// second Enemy type
			colour[0] = 0.0;
			colour[1] = 0.8;
			colour[2] = 0.4;
			speed = 0.7;
			size = 4.0;
			break;
		case 3:	// third Enemy type
			colour[0] = 1.0;
			colour[1] = 0.0;
			colour[2] = 1.0;
			speed = 0.9;
			size = 3.5;
			break;
		case 4:	// boss Enemy type
			colour[0] = 1.0;
			colour[1] = 0.5;
			colour[2] = 0.0;
			speed = 1.5;
			size = 10.0;
			break;
		}	
}



// Returns the age value
int Enemy::getAge(){
	return age;
}

// Sets the age value
void Enemy::setAge(int aStatus){
	age = aStatus;
}

// Returns the boss value
bool Enemy::getBoss(){
	return boss;
}

// Sets the boss boolean
void Enemy::setBoss(bool b){
	boss = b;
}

// Returns the boss health
int Enemy::getBossHealth(){
	return bossHealth;
}

// Sets the boss health
void Enemy::setBossHealth(int b){
	bossHealth = b;
}

// Add b to the bosses health
void Enemy::addBossHealth(int b){
	bossHealth += b;
	if(bossHealth % 5 == 0){
		addColour(0.0, 0.10, 0.0);
		relocateBoss();
	}
}

// Relocate the boss after taking damage
void Enemy::relocateBoss(){

	angle += 180 ;
	if(angle > 360.0)
		angle -= 360.0;

	float radian = angle * (M_PI/180);
	pos.x = 155 * cosf(radian);
	pos.z = 155 * sinf(radian);
	pos.y = rand() % 140 + 5;

}

// Returns the size of the enemy
float Enemy::getSize(){
	return size;
}

// Set Enemy size
void Enemy::setSize(float newSize){
	size = newSize;
}

// Returns the size of the enemy
float Enemy::getAngle(){
	return angle;
}

// Set Enemy size
void Enemy::setAngle(float newAngle){
	angle = newAngle;
}


// Set the speed
void Enemy::setSpeed(double sp){	
		speed = sp;	
}


// Set the colour
void Enemy::setColour(float r, float g, float b){
	colour[0] = r;
	colour[1] = g;
	colour[2] = b;
}

// Add the colour
void Enemy::addColour(float r, float g, float b){
	colour[0] += r;
	colour[1] += g;
	colour[2] += b;

	// Max/min colours
	if(colour[0] > 1.0)
		colour[0] = 1.0;
	else if(colour[0] < 0.0)
		colour[0] = 0.0;

	if(colour[1] > 1.0)
		colour[1] = 1.0;
	else if(colour[1] < 0.0)
		colour[1] = 0.0;

	if(colour[2] > 1.0)
		colour[2] = 1.0;
	else if(colour[2] < 0.0)
		colour[2] = 0.0;

}

// Set the Enemy type
void Enemy::setEnemyType(int a){
	enemyType = a;
}

// Returns the EnemyType
int Enemy::getEnemyType(){
	return enemyType;
}

// Set the alpha (visibility) of the Enemy
void Enemy::setAlpha(double alp){
	alpha = alp;
}


// Set the position
void Enemy::setPosition(Coordinate p){
	pos = p;
}

// Return the Enemys position
Coordinate Enemy::getPosition(){
	return pos;
}


// update the Enemy
// This will calculate the new pos for the enemy
// Depending on the enemy, goes in a straight line or heads towards the player
void Enemy::Update(Coordinate pp, float pa){
	float ar, range;
	float radian = angle * (M_PI/180);

	switch(enemyType){
	case 1:	// First enemy type
		// Move the Enemy in a straight line
		if(dir){
			// Right
			angle += 1.4 * speed;
			if(angle > 360.0)
				angle -= 360.0;
			 radian = angle * (M_PI/180);
			pos.x = 155 * cosf(radian);
			pos.z = 155 * sinf(radian);
		}else {
			// Left
			angle -= 1.4 * speed;
			if(angle < 0.0)
				angle += 360.0;
			 radian = angle * (M_PI/180);
			pos.x = 155 * cosf(radian);
			pos.z = 155 * sinf(radian);
		}
		break;
	case 2:	// Second enemy, moves close to player when in range
		// Move towards player if within a range
		// Angle between player and enemy
		ar = angle > pa ? angle - pa: pa - angle; // Bigger angle - smaller angle
		// Make sure angle is the smallest angle
		if(ar > 180)
			ar = 360 - ar;
		range = (155*2) * M_PI * ar / 360;	// Distance between player/enemy
		if(range > 200){
			// Straight line if too far
			if(dir){
				// Right
				angle += 0.9 * speed;
				if(angle > 360.0)
					angle -= 360.0;
				 radian = angle * (M_PI/180);
				pos.x = 155 * cosf(radian);
				pos.z = 155 * sinf(radian);
			}else {
				// Left
				angle -= 0.9 * speed;
				if(angle < 0.0)
					angle += 360.0;
				 radian = angle * (M_PI/180);
				pos.x = 155 * cosf(radian);
				pos.z = 155 * sinf(radian);
			}
		}else {
			// In range start 
			// Move y direction closer
			pos.y = pos.getY() > pp.getY() ? pos.y - 0.2 : pos.y + 0.2;
			// Move towards player angle
			if(pa > angle)
				angle += 0.75 * speed;
			else
				angle -= 0.75 * speed;
			if(angle > 360.0)
				angle -= 360.0;
			if(angle < 0.0)
				angle += 360.0;
			 radian = angle * (M_PI/180);
			pos.x = 155 * cosf(radian);
			pos.z = 155 * sinf(radian);
			
		}

		if ( enemy2Rotation >=360 ){ //update enemy donut rotation
			 enemy2Rotation = 0;
		}else{
			enemy2Rotation += 10;
		}
		

		break;
	case 3: // third enemy
		// Move towards player always		
		// Move y direction closer
		pos.y = pos.getY() > pp.getY() ? pos.y - 0.2 : pos.y + 0.2;
		// Move towards player angle
		if(pa > angle)
			angle += 0.45 * speed;
		else
			angle -= 0.45 * speed;

		if(angle > 360.0)
			angle -= 360.0;
		if(angle < 0.0)
			angle += 360.0;

		radian = angle * (M_PI/180);
		pos.x = 155 * cosf(radian);
		pos.z = 155 * sinf(radian);

		if ( enemy3Rotation >=360 ){ //update enemy donut rotation
			 enemy3Rotation = 0;
		}else{
			enemy3Rotation += 10;
		}

		break;
	case 4:		// boss
		// Move towards player always		
		// Move y direction closer
		pos.y = pos.getY() > pp.getY() ? pos.y - 0.2 : pos.y + 0.2;
		// Move towards player angle
		if(pa > angle)
			angle += 0.45 * speed;
		else
			angle -= 0.45 * speed;

		if(angle > 360.0)
			angle -= 360.0;
		if(angle < 0.0)
			angle += 360.0;

	    radian = angle * (M_PI/180);
		pos.x = 155 * cosf(radian);
		pos.z = 155 * sinf(radian);

		if ( bossRotation >=360 ){ //update enemy donut rotation
			 bossRotation = 0;
		}else{
			bossRotation += 10;
		}

		break;
	}
	
}


// Render the Enemy
void Enemy::Render(){

	GLUquadric *qobj;

	glPushMatrix();
	glColor4f(colour[0], colour[1], colour[2], alpha);	// Colour it
	//glTranslated(pos.x, pos.y, pos.z);			// Translate to its position
	switch (enemyType){					// Draw the specific type of Enemy
		case 1:
			glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLightRed);
			glColor4f(1.0, 0.0, 0.0, 1.0);	
			glTranslatef(pos.x, pos.y, pos.z);
			glutWireCube(size);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, NoEmission);
			glPopMatrix();

			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLightGreen); 
			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0, 1.0);  //top front right
			glTranslatef(pos.x + (size/2), pos.y + 1 +(size/2), pos.z + (size/2));
			glRotatef(-45, 1.0, 0.0, 0.0);
			glScalef(2.0, 2.0 , 2.0);
			glutWireTetrahedron();
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0,1.0,0.0 ,1.0); //top back right
			glTranslatef(pos.x + (size/2) , pos.y + 1 + (size/2), pos.z - (size/2));
			glRotatef(-45, 1.0, 0.0, 0.0);
			glScalef(2.0, 2.0 , 2.0);
			glutWireTetrahedron();
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0 ,1.0); //top front left
			glTranslatef(pos.x - (size/2) , pos.y + 1 + (size/2), pos.z + (size/2));
			glRotatef(45, 1.0, 0.0, 0.0);
			glScalef(2.0, 2.0 , 2.0);
			glutWireTetrahedron();
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0 ,1.0); //top back left
			glTranslatef(pos.x - (size/2) , pos.y + 1 + (size/2), pos.z - (size/2));
			glRotatef(45, 1.0, 0.0, 0.0);
			glScalef(2.0, 2.0 , 2.0);
			glutWireTetrahedron();
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0 ,1.0); //bottom front right
			glTranslatef(pos.x + (size/2) , pos.y - 1 - (size/2), pos.z + (size/2));
			glRotatef(45, 0.0, 0.0, 1.0);
			glScalef(2.0, 2.0 , 2.0);
			glutWireTetrahedron();
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0 ,1.0); //bottom back right
			glTranslatef(pos.x + (size/2), pos.y - 1 - (size/2), pos.z - (size/2));
			glRotatef(-45, 0.0, 0.0, 1.0);
			glScalef(2.0, 2.0 , 2.0);
			glutWireTetrahedron();
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0 ,1.0); //bottom front left
			glTranslatef(pos.x - (size/2), pos.y - 1 - (size/2), pos.z + (size/2));
			glRotatef(45, 0.0, 0.0, 1.0);
			glScalef(2.0, 2.0 , 2.0);
			glutWireTetrahedron();
			glPopMatrix();

			glPushMatrix();
			glColor4f(0.0, 1.0, 0.0 ,1.0); //bottom back left
			glTranslatef(pos.x - (size/2) , pos.y - 1 - (size/2), pos.z - (size/2));
			glRotatef(-45, 0.0, 0.0, 1.0);
			glScalef(2.0, 2.0 , 2.0);
			glutWireTetrahedron();
			glPopMatrix();	
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, NoEmission);
			break; 

		case 2: //enemy type 2
			glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLightRed); 
			glColor4f(1.0, 0.0, 0.0 , 1.0);	
			glTranslatef(pos.x, pos.y, pos.z);
			glutSolidSphere(size/3, 25, 25);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, NoEmission);
			glPopMatrix();

			glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLightGreen); 
			glColor4f(0.0, 1.0, 0.0 , 1.0);		
			glTranslatef(pos.x, pos.y, pos.z);
			glRotated(enemy2Rotation , 1.0 , 0.0 , 0.0);
			glutSolidTorus(size/3, size , 50, 50);	 
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, NoEmission);
			glPopMatrix();

			glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLightBlue); 
			glColor4f(0.0, 0.0, 1.0 , 1.0);
			glTranslatef(pos.x, pos.y, pos.z);
			glRotated(enemy2Rotation , 0.0 , 1.0 , 0.0);
			glutSolidTorus(size/3, size*2.0 , 50, 50);	
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, NoEmission);
			glPopMatrix();

			break;
		case 3: //enemy type 3
			
			

			glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLightRed); 
			glColor4f(1.0, 0.0, 1.0 , 1.0);	
			glTranslatef(pos.x, pos.y, pos.z);
			glRotatef(enemy3Rotation, 0.0 , 0.0 , 1.0);
			glScalef(size,size,size);
			glutSolidTetrahedron();
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, NoEmission);
			glPopMatrix();			

			glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLightBlue); 
			glColor4f(0.4, 0.3, 1.0 , 1.0);
			glTranslatef(pos.x, pos.y, pos.z);
			glRotated(enemy3Rotation , 0.0 , 1.0 , 0.0);
			glutSolidTorus(size/3, size*3.0 , 50, 50);	
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, NoEmission);
			glPopMatrix();

			glPopMatrix();
			break;
		case 4: //boss
			glPushMatrix();
			glTranslatef(pos.x, pos.y, pos.z);		
			glRotated(bossRotation , 1.0 , 0.0 , 1.0);
			glColor3f(colour[0], colour[1], colour[2]);
			glRotatef(90.0, 0.0 , 1.0 , 0.0);
			glutSolidCube(size);			
			glPopMatrix();
			break;
			
	}
	glPopMatrix();
}