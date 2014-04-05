#ifndef _MYDISTANCESENSOR_HPP_
#define _MYDISTANCESENSOR_HPP_

// Includes
#include "rec/robotino/com/All.h"

// Includes perso

// Class
class MyDistanceSensor : rec::robotino::com::DistanceSensor
{
public:
	MyDistanceSensor(rec::robotino::com::ComID id);
	~MyDistanceSensor();
	void setSensorNum();
	int getVoltage() const;
	int getHeading() const;
};

#endif //_MYDISTANCESENSOR_HPP_
