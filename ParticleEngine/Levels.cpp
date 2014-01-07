// Levels.cpp
// Class used to monitor the level of difficulty
#include "Levels.h"

Levels::~Levels(){
}

// Inital Bullet generation set fields
Levels::Levels(){
	numEnemiesKilled = 0;
	level = 0;
	boss = false;
	difficulty = 1;
	lives = 3;
	score = 0;
	killsToLevel = 10;
}

// Add a number of enemies to the kill count
void Levels::addKilled(int a){
	numEnemiesKilled += a;
}

// Remove a number of enemies to the kill count
void Levels::removeKilled(int a){
	numEnemiesKilled -= a;
}

// Set a number of enemies to the kill count
void Levels::setKilled(int a){
	numEnemiesKilled = a;
}

// Return the kill count
int Levels::getKilled(){
	return numEnemiesKilled;
}

// Add up player score
void Levels::addScore(int a){
	score += a;	
}

// Set player score
void Levels::setScore(int a){
	score = a;	
}

// Return player score
int Levels::getScore(){
	return score;
}

// Add up player score
void Levels::addLives(int a){
	lives += a;	
}

// Set player score
void Levels::setLives(int a){
	lives = a;	
}

// Return player score
int Levels::getLives(){
	return lives;
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
int Levels::getKillsNeededToLevelUp(){
	return killsToLevel;
}

// Set the difficulty to a
void Levels::setKillsNeededToLevelUp(int a){
	killsToLevel = a;
}

// Returns the difficulty
int Levels::getDiff(){
	return difficulty;
}

// Reset the game difficulty
void Levels::reset(){
	numEnemiesKilled = 0;
	level = 0;
	boss = false;
	difficulty = 1;
	score = 0;
	lives = 3;
	killsToLevel = 10;
}

// Some form of update
int Levels::Update(){
	// Everything will be based on difficulty
	if(level == 0){
		level = 1;
		return level;
	}
	switch(difficulty){
	case 1: // Easy
		if(numEnemiesKilled >= killsToLevel){
			killsToLevel += 10;
			level += 1;
			if(level == 10)
				boss = true;
		}
		break;
	case 2: // Medium
		if(numEnemiesKilled >= killsToLevel){
			killsToLevel += 15;
			level += 1;
			if(level == 10)
				boss = true;
		}
		break;
	case 3: // Medium
		if(numEnemiesKilled >= killsToLevel){
			killsToLevel += 20;
			level += 1;
			if(level == 10)
				boss = true;
		}
		break;
		
	}
		
	return level;
}
