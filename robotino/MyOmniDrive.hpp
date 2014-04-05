#ifndef _MYOMNIDRIVE_HPP_
#define _MYOMNIDRIVE_HPP_

// Includes
#include "rec/robotino/com/All.h"

// Includes perso

// Class
class MyOmniDrive : rec::robotino::com::OmniDrive
{
public:
	MyOmniDrive(rec::robotino::com::ComID id);
	~MyOmniDrive();
	void setAllVelocities(int vx, int vy, int vphi);	
	void setVx(int vx);
	void setVy(int vy);
	void setVphi(int vphi);
	int getVx() const;
	int getVy() const;
	int getVphi() const;

private:
	int _vx, _vy, _vphi;
};

#endif //_MYOMNIDRIVE_HPP_
