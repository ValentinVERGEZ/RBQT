#ifndef _MYODOMETRY_HPP_
#define _MYODOMETRY_HPP_

// Includes
#include "rec/robotino/com/All.h"

// Includes perso

// Class
class MyOdometry : rec::robotino::com::Odometry
{
public:
	MyOdometry(rec::robotino::com::ComID id);
	~MyOdometry();
	int getX() const;
	int getY() const;
	int getPhi() const;
	void setOdometry(int x, int y, int phi);	
	void setX(int x);
	void setY(int y);
	void setPhi(int phi);
};

#endif //_MYODOMETRY_HPP_
