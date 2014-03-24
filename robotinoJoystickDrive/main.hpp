#ifndef _MAIN_HEADER_
#define _MAIN_HEADER_

/* Includes */
    //StdLib
    #include <iostream>

    //SFML
    #include <SFML/Graphics.hpp>

    // Perso
    #include "robotino_drive.hpp"


/* Global variables and constants*/
    // Joystick datas
    extern bool joyButtonPressed[31];
    extern float joyAxisValues[8];
   	extern sf::Mutex joyInfosMutex;


// Prototypes
void printJoysticksInfos();
void printJoystickStat();
void getJoystickStat(sf::RenderWindow& window);

#endif // _MAIN_HEADER_