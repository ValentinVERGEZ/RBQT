/* Includes */
	// Perso
	#include "robotino_drive.hpp"

	// Namespaces
	using namespace rbqt::lleague;

	// Global variables and constants
	MyCom com;
	rec::robotino::com::OmniDrive omniDrive;
	rec::robotino::com::Bumper bumper;

/* Functions and methods definition */
	/* Functions */


	void rbqt::lleague::init( const std::string& hostname )
	{
		// Initialize the actors

		// Connect
		std::cout << "Connecting..." << std::endl;
		com.setAddress( hostname.c_str() );

		com.connect();

		std::cout << std::endl << "Connected" << std::endl;
	}

	void rbqt::lleague::drive()
	{
		while( com.isConnected() && !joyButtonPressed[0])
		{

			float m1,m2,m3;
			joyInfosMutex.lock();
			omniDrive.project( &m1, &m2, &m3, -5*(int)joyAxisValues[sf::Joystick::Y], -5*(int)joyAxisValues[sf::Joystick::X], -3*(int)joyAxisValues[sf::Joystick::R] );
			joyInfosMutex.unlock();

			rec::iocontrol::remotestate::SetState setState;
			setState.speedSetPoint[0] = m1;
			setState.speedSetPoint[1] = m2;
			setState.speedSetPoint[2] = m3;

			com.setSetState( setState );

			com.waitForUpdate();
		}
	}

	void rbqt::lleague::destroy()
	{
		com.disconnect();
	}

	int rbqt::lleague::rec_robotino_thread(std::string hostname)
	{
		try
		{
			init( hostname );
			drive();
			destroy();
		}
		catch( const rec::robotino::com::ComException& e )
		{
			std::cerr << "Com Error: " << e.what() << std::endl;
		}
		catch( const std::exception& e )
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
		catch( ... )
		{
			std::cerr << "Unknow Error" << std::endl;
		}

		return 0;
	}

	/* Methods */
	MyCom::MyCom()
	{
	}

	void MyCom::errorEvent( Error error, const char* errorString )
	{
		std::cerr << "Error: " << errorString << std::endl;
	}

	void MyCom::connectedEvent()
	{
		std::cout << "Connected." << std::endl;
	}

	void MyCom::connectionClosedEvent()
	{
		std::cout << "Connection closed." << std::endl;
	}

	void MyCom::modeChangedEvent( bool isPassiveMode )
	{
		if( isPassiveMode )
		{
			std::cout << "Connected int passive mode." << std::endl;
		}
	}