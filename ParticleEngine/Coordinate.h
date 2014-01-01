// Simple class which will contain x,y,z values
// Will be used with collision detection (i assume)

class Coordinate {		
	
	public:
		double x, y, z;
		Coordinate::Coordinate(){};
		Coordinate::~Coordinate(){};

		double Coordinate::getX(){
			return x;
		}
		double Coordinate::getY(){
			return y;
		}
		double Coordinate::getZ(){
			return z;
		}

		void Coordinate::setX(double x1){
			x = x1;
		}
		void Coordinate::setY(double y1){
			y = y1;

		}
		void Coordinate::setZ(double z1){
			z = z1;
		}

	Coordinate::Coordinate(double x1, double y1, double z1){
		x = x1;
		y = y1;
		z = z1;
	}

};