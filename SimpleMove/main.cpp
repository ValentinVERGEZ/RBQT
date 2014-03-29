// Team RBQT - Valentin VERGEZ et Nathan MARTIN - Polytech Lille

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "rec/robotino/com/all.h"
#include "rec/core_lt/utils.h"
#include "rec/core_lt/Timer.h"
#include "rec/core_lt/Thread.h"

using namespace rec::robotino::com;


class MyInfo : public Info
{
public:
	MyInfo()
	{
	}

	void infoReceivedEvent( const char* text )
	{
		std::cout << text << std::endl;
	}
};

class MyCom : public Com
{
	public:
		MyCom()
		{
		}

		void errorEvent( Error error, const char* errorString )
		{
			std::cerr << "Error: " << errorString << std::endl;
		}

		void connectedEvent()
		{
			std::cout << "Connected." << std::endl;
		}

		void connectionClosedEvent()
		{
			std::cout << "Connection closed." << std::endl;
		}
};

MyCom com;
OmniDrive omniDrive;
Bumper bumper;
Odometry odometry;
MyInfo info;

void init( const std::string& hostname )
{
	odometry.setComId( com.id() );
	omniDrive.setComId( com.id() );
	bumper.setComId( com.id() );
	info.setComId( com.id() );

  	// Connect
  	std::cout << "Connecting..." << std::endl;
  	com.setAddress( hostname.c_str() );

   	//com.setAutoUpdateEnabled( false );
	com.connect();

  	std::cout << std::endl << "Connected" << std::endl;
}

void destroy()
{
  com.disconnect();
}

// function of movement. Return 1 on success else -1 
int one_move(float x_order,float y_order)
{
	//declarations
	float distanceX=0.0; //in m
	float distanceY=0.0; //in m
	float phi=0.0; //orientation in deg
	float velocityX=100, velocityY=100, velocityPhi=50;//velocity in function of the direction


	rec::core_lt::Timer timer;
	timer.start();

	//set position of the beginning
	odometry.set( 0, 0, 0 );

	std::cout << "x = " << odometry.x() << "  y =" << odometry.y() << " phi =  " << odometry.phi() << std::endl;
	
	//calculate distance to do
	distanceX = x_order-odometry.x();
	distanceY = y_order-odometry.y();

	std::cout << "x = " << odometry.x() << "  y =" << odometry.y() << " phi =  " << odometry.phi() << std::endl;
	std::cout << "distanceX = " << distanceX << "  distanceY" << distanceY << std::endl;
	
	// diagonal movements
	// if (x_order > distanceX && y_order > distanceY) 
	// 	{
	// 		phi=0;
	// 		velocityX=100;
	// 		velocityY=100;
	// 	}
	// if (x < distanceX && y > distanceY)
	// 	{
	// 		phi=0;
	// 		velocityX=-100;
	// 		velocityY=100;
	// 	}

	//if ((x > distanceX && y < distanceY) || (x < distanceX && y < distanceY)) phi=180;
	
	// linear movements on Y
	if (distanceX == 0 && y_order > odometry.y() ) 
		{
			phi= 0;
			velocityX=0;
			velocityY=200;
		}
	else{
		if(distanceX == 0 && y_order < odometry.y())
			phi = 0;
			velocityX=0;
			velocityY=-200; 
		}
	std::cout << " odometry.y()  " << odometry.y() << " distanceY  " << distanceY <<std::endl;
	std::cout << " 3odometry.y()  " << odometry.y() << " velocityY  " << velocityY <<std::endl;
	
	// linear movements on X
	if (distanceY == 0 && x_order > odometry.x() ) 
		{
			phi= 0;
			velocityX=200;
			velocityY=0;
		}
	else{
		if(distanceY == 0 && x_order < odometry.x())
			{
				phi = 0;
				velocityX=-200;
				velocityY=0; 
			}
		}
	std::cout << " odometry.y()  " << odometry.y() << " distanceY  " << distanceY <<std::endl;

//MOVE
	do 
	{
		omniDrive.setVelocity( 0, 0, velocityPhi ); //in rad/sec ?
		//std::cout << "odometry of phi =" << odometry.phi() << " phi = "<< phi << std::endl;
	}
	while(odometry.phi() < phi );
	
	if(velocityX > 0){
		//positive case: x wanted positive
		do 
		{
			omniDrive.setVelocity( velocityX, 0, 0 ); //in m/sec
			//std::cout << "odometry of X =" << odometry.x() << " x wanted = "<< distanceX << std::endl;
		}
		while(odometry.x() < distanceX );
	}
	else
	{
		if(velocityX < 0)
		{
			// x wanted negative
			do 
			{
				omniDrive.setVelocity( velocityX, 0, 0 ); //in m/sec
				//std::cout << "odometry of X =" << odometry.x() << " x wanted = "<< distanceX << std::endl;
			}
			while(odometry.x() > distanceX);
		}
	}
	
	if(velocityY>0)
	{
		do 
		{
			omniDrive.setVelocity( 0, velocityY, 0 ); //in m/sec		
			std::cout << "1) odometry of Y =" << odometry.y() << " y wanted = "<< distanceY << "with velocity = " << velocityY << std::endl;
		}
		while(odometry.y() < distanceY);
	}
	else
	{
		if(velocityY < 0){	
			do 
			{
				omniDrive.setVelocity( 0, velocityY, 0 ); //in m/sec		
				std::cout << "2) odometry of Y =" << odometry.y() << " and   y wanted = "<< distanceY << "with velocity = " << velocityY <<std::endl;
			}
			while(odometry.y() > distanceY);
		}
	}	

	//com.update();
	rec::core_lt::msleep( 20 );
	
	return 1;
}


// ------- MAIN -------

int main( int argc, char **argv )
{
	std::string hostname = "192.168.1.40";
	if( argc > 1 )
	{
		hostname = argv[1];
	}

	init( hostname );

	std::cout << "Fin init  " << std::endl;

	one_move(0,200);
	//rec::core_lt::msleep( 2000 );

  // std::cout << "Press any key to exit..." << std::endl;
  // rec::core_lt::waitForKey();
return 1;
}



/*
// DEFINE
#define INVALID_ODOMETRYID -1

// function of movement. Return 1 on success else -1 
int one_move(float x,float y,int OdometryId)
{
	//declarations
	float distanceX=0; //in mm
	float distanceY=0; //in mm

	//calculate distance to do
	distanceX = x-Odometry_x(OdometryId);
	distanceY = y-Odometry_y(OdometryId);
	
	// diagonal movements
	if ((x > distanceX && y > distanceY) || (x < distanceX && y > distanceY)) phi=0;
	if ((x > distanceX && y < distanceY) || (x < distanceX && y < distanceY)) phi=180;
	
	// linear movements
	if (distanceX == 0 && y > Odometry_y) phi=45;
	else phi = 135;
	if (distanceY == 0 && x > Odometry_x) phi=45;
	else phi = 315;

	Odometry_set(Odometry_x(abs(OdometryId),Odometry_y(abs(OdometryId)), phi);

	
	return 1;
}



int main(argv,argc){
	// creation of odometry object
	OdometryId = Odometry_construct();
	
	std::cout << "\nAffichage: \tXrobotino: " << Odometry_x(OdometryId) << "Yrobotino:\t" << Odometry_x(OdometryId) << "Phi_robotino\t" << phi << std::endl;

	//destruction of odometry object
	Odometry_destroy(OdometryId); //return true on success

return 1;
}

*/