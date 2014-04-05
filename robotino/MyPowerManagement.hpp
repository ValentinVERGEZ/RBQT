#ifndef _MYPOWERMANAGEMENT_HPP_
#define _MYPOWERMANAGEMENT_HPP_

// Includes
#include "rec/robotino/com/All.h"

// Includes perso

// Class
class MyPowerManagement : rec::robotino::com::PowerManagement
{
public:
	MyPowerManagement(rec::robotino::com::ComID id);
	~MyPowerManagement();
	int getCurrent() const;
	int getVoltage() const;	
};

#endif //_MYPOWERMANAGEMENT_HPP_
