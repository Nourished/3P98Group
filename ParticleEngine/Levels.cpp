// Levels.cpp
// Class used to monitor the level of difficulty
#include "Levels.h"

Levels::~Levels(){
}

// Inital Bullet generation set fields
Levels::Levels(){
	numEnemiesKilled = 0;
	level = 1;
	boss = false;
	difficulty = 1;
}

// Add a number of enemies to the kill count
void Levels::addKilled(int a){
	numEnemiesKilled += a;
	Update();
	
}
// Remove a number of enemies to the kill count
void Levels::removeKilled(int a){
	numEnemiesKilled -= a;
	Update();
}

// Set a number of enemies to the kill count
void Levels::setKilled(int a){
	numEnemiesKilled = a;
	Update();
}

// Return the kill count
int Levels::getKilled(){
	return numEnemiesKilled;
}

// Increase the level by a
void Levels::increaseLevel(int a){
	level += a;
}

// Lower the level by a
void Levels::lowerLevel(int a){
	level -= a;
}

// Set the level to a
void Levels::setLevel(int a){
	level = a;
}

// Retuns the current level
int Levels::getLevel(){
	return level;
}

// Set boss to a
void Levels::setBoss(bool a){
	boss = a;
}

// Returns the boss bool, true = boss level, false = normal
bool Levels::getBoss(){
	return boss;
}

// Increase the difficulty by a
void Levels::increaseDiff(int a){
	difficulty += a;
}

// Decrease the difficulty by a
void Levels::lowerDiff(int a){
	difficulty -= a;
}

// Set the difficulty to a
void Levels::setDiff(int a){
	difficulty = a;
}

// Returns the difficulty
int Levels::getDiff(){
	return difficulty;
}

// Reset the game difficulty
void Levels::reset(){
	numEnemiesKilled = 0;
	level = 1;
	boss = false;
	difficulty = 1;
}

// Some form of update
void Levels::Update(){
	// Everything will be based on difficulty
	switch(difficulty){
	case 1: // Easy
		if(numEnemiesKilled == 10)
			setLevel(2);
		else if(numEnemiesKilled == 20)
			setLevel(3);
		else if(numEnemiesKilled == 30)
			setLevel(4);
		else if(numEnemiesKilled == 40)
			setLevel(5);
		else if(numEnemiesKilled == 50)
			setLevel(6);
		else if(numEnemiesKilled == 75)
			setLevel(7);
		else if(numEnemiesKilled == 100)
			setLevel(8);
		else if(numEnemiesKilled == 125)
			setLevel(9);
		else if(numEnemiesKilled == 150)
			setLevel(10);
		else if(numEnemiesKilled > 150)
			setBoss(true);
		break;
	case 2:	// Medium
		if(numEnemiesKilled == 15)
			setLevel(2);
		else if(numEnemiesKilled == 30)
			setLevel(3);
		else if(numEnemiesKilled == 45)
			setLevel(4);
		else if(numEnemiesKilled == 60)
			setLevel(5);
		else if(numEnemiesKilled == 80)
			setLevel(6);
		else if(numEnemiesKilled == 100)
			setLevel(7);
		else if(numEnemiesKilled == 125)
			setLevel(8);
		else if(numEnemiesKilled == 150)
			setLevel(9);
		else if(numEnemiesKilled == 200)
			setLevel(10);
		else if(numEnemiesKilled > 200)
			setBoss(true);
		break;
	case 3:	// Hard
		if(numEnemiesKilled == 5)
			setLevel(2);
		else if(numEnemiesKilled == 10)
			setLevel(3);
		else if(numEnemiesKilled == 15)
			setLevel(4);
		else if(numEnemiesKilled == 20)
			setLevel(5);
		else if(numEnemiesKilled == 25)
			setLevel(6);
		else if(numEnemiesKilled == 50)
			setLevel(7);
		else if(numEnemiesKilled == 75)
			setLevel(8);
		else if(numEnemiesKilled == 100)
			setLevel(9);
		else if(numEnemiesKilled == 150)
			setLevel(10);
		else if(numEnemiesKilled > 150)
			setBoss(true);
		break;
	}
		
}
