#ifndef _ROBOTINO_DRIVE_HEADER_
#define _ROBOTINO_DRIVE_HEADER_

/* Includes */
	// Std
	#define _USE_MATH_DEFINES
	#include <cmath>
	#include <iostream>

	// Robotino
	#include "rec/robotino/com/all.h"
	#include "rec/core_lt/utils.h"
	#include "rec/core_lt/Timer.h"
	#include "rec/core_lt/Thread.h"

	// Perso
	#include "main.hpp"

/* Class declaration */
namespace rbqt
{
	namespace lleague
	{
		class MyCom : public rec::robotino::com::Com
		{
		public:
			MyCom();
			void errorEvent( Error error, const char* errorString );
			void connectedEvent();
			void connectionClosedEvent();
			void modeChangedEvent( bool isPassiveMode );
		};

		/* Protoypes */
		//rotate vector in by deg degrees and store the output in out
		void rotate( const float* in, float* out, float deg );
		void init( const std::string& hostname );
		void drive();
		void destroy();
		int rec_robotino_thread(std::string hostname = "127.0.0.1:8093");			
	}
}




#endif // _ROBOTINO_DRIVE_HEADER_