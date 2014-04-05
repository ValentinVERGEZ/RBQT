#ifndef _MYCAMERA_HPP_
#define _MYCAMERA_HPP_

// Includes
#include "rec/robotino/com/All.h"

// Includes perso

// Class
class MyBumper : rec::robotino::com::Bumper
{
public:
	MyBumper(rec::robotino::com::ComID id);
	~MyBumper();
	int getValue() const;
};

#endif //_MYCAMERA_HPP_
