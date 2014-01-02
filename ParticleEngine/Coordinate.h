// Simple class which will contain x,y,z values
// Will be used with collision detection (i assume)
#ifndef _COORDINATE_
#define _COORDINATE_

class Coordinate {		
	
	public:
		float x, y, z;

		Coordinate::Coordinate(){
			x = y = z = 0.0;
		}
		Coordinate::~Coordinate(){}

		Coordinate::Coordinate(float x1, float y1, float z1){
			x = x1;
			y = y1;
			z = z1;
		};

		float Coordinate::getX(){
			return x;
		}
		float Coordinate::getY(){
			return y;
		}
		float Coordinate::getZ(){
			return z;
		}

		void Coordinate::setX(float x1){
			x = x1;
		}
		void Coordinate::setY(float y1){
			y = y1;

		}
		void Coordinate::setZ(float z1){
			z = z1;
		}

	

};

#endif