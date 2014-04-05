#ifndef _ROBOTINO_HPP_
#define _ROBOTINO_HPP_

// Includes
#include "rec/robotino/com/All.h"

// Includes perso
#include "Point.hpp"
#include "Objet.hpp"

// Class
class Robotino
{
public:
	Robotino();
	~Robotino();
	void runDeplacement();
	void moveTo(int x, int y, int phi);
	void orientTo(int phi);
	void moveTo(int x, int y);
	void stop();
	//void followPath(Path path);	
	void takeNearestPuck();
	void goToMachine(Objet machine);
	void goToPoint(Point point);
	void goToMachineAcessPoint(Objet machine);
	
private:
	bool transportAProduct;
	Product transportedProduct;
};

#endif //_ROBOTINO_HPP_
