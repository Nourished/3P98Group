// Eric Gummerson	4585469
// RNG.cpp
// Random Number Generator
// Used to randomize the particles

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "RNG.h"

// Initalize the seed
RNG::RNG(){
	seed = (unsigned)time(NULL);
	srand(seed);
}

RNG::~RNG(){}

// Returns a double between low and high
double RNG::random(double low, double high){
	return (rand1()*(high - low))+low;
}

// Returns an int between low and high
int RNG::random(int low, int high){
	return (int) random((double) low, (double) high);
}

// Returns a double between 0.0 and 1.0
double RNG::rand1(){
	return ((double)rand()/(double)RAND_MAX);
}

// Returns a double that follows the mean m with standard deviation s
// Another way to get a random pattern, but pretty similar to random()
double RNG::stdDeviation(double m, double s)	{				        
	double high = m+s;
	double low = m-s;
	return (rand1()*(high - low))+low;
}

