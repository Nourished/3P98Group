// Eric Gummerson	4585469
// RNG.h

#pragma once
class RNG{
private:
	 int seed;
public:
	RNG();
	~RNG();
	double random(double low, double high);
	int random(int low, int high);
	double rand1();
	double stdDeviation(double m, double s);

};
