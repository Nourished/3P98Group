// Levels.h

#pragma once
class Levels {	
	
	protected: 
		int numEnemiesKilled;	// Number of enemies killed
		int level;				// Levels 1-10
		bool boss;				// true if boss, false if normal
		int difficulty;			// 1 easy, 2 normal, 3 hard
		int score;

	public:
		// create a Levels with a given type, direction, angle on circle, and position
		Levels();
		~Levels();

	void addKilled(int a);
	void removeKilled(int a);
	void setKilled(int a);
	int getKilled();

	void addScore(int a);
	void setScore(int a);
	int getScore();
	
	void increaseLevel(int a);
	void lowerLevel(int a);
	void setLevel(int a);
	int getLevel();

	void setBoss(bool a);
	bool getBoss();

	void increaseDiff(int a);
	void lowerDiff(int a);
	void setDiff(int a);
	int getDiff();
	
	void reset();
	void Update();
	

};
