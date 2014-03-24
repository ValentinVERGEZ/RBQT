/* Includes */
    //StdLib
    #include <iostream>

    //SFML
    #include <SFML/Graphics.hpp>

    // Perso
    #include "main.hpp"
    #include "robotino_drive.hpp"

/* Global variables and constants*/
    unsigned int usedJoystick=0;

    // Joystick datas
    bool joyButtonPressed[31]={false};
    float joyAxisValues[8]={0};
    sf::Mutex joyInfosMutex;

    // Thread periods
    const unsigned int JOY_THD_SLEEP(50);

/* Main */
int main( int argc, char **argv )
{
    std::string hostname = "172.26.94.17";
    if( argc > 1 )
    {
        hostname = argv[1];
    }

    //Environment
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Thread robotinoDriveThread(&rbqt::lleague::rec_robotino_thread,hostname);

    // Joystick infos
    printJoysticksInfos();
    std::cout << "Quel Joystick utiliser ? : ";
    std::cin >> usedJoystick;
    robotinoDriveThread.launch();

    // Algo
    while (window.isOpen())
    {
        // Check if events occured and process them
        getJoystickStat(window);

        // Draw window
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

/**
 * Print All Joysticks information
 */
void printJoysticksInfos()
{   
    //Environment
    std::string axisName[8] = {"X","Y","Z","R","u","V","PovX","PovY"};

    //Algo
    sf::Joystick::update();
    for(int i = 0; i < 8; i++)
    {
        if(sf::Joystick::isConnected(i))
        {
            // Joystick 0 connecté
            std::cout << std::endl << "----------------" << std::endl;
            std::cout << "Joystick " << i << " connecté" << std::endl;
            std::cout << "Nombre de boutons : " << sf::Joystick::getButtonCount(i) << std::endl;
            for(int j = 0; j < 8; j++)
            {
                if(sf::Joystick::hasAxis(i,(sf::Joystick::Axis)j))
                    std::cout << "Axe " << axisName[j] << std::endl;
            }
        }
        else
        {
            std::cout << "****************" << std::endl;
            std::cout << "Joystick " << i << " non connecté" << std::endl;
        }
    }
}

/**
 * Print used joystick status
 */
void printJoystickStat()
{
    //Environment
    bool stop(false);
    std::string axisName[8] = {"X","Y","Z","R","u","V","PovX","PovY"};

    //Algo
    while(stop == false)
    {
        // Display Buttons
        for(unsigned int i(0); i < sf::Joystick::getButtonCount(usedJoystick); i++)
        {
            joyInfosMutex.lock();
            std::cout << "Button " << i << (joyButtonPressed[i]?" PRESSED":" --") << std::endl;
            joyInfosMutex.unlock();
        }

        // Display axis
        for(int j(0); j < 8; j++)
        {

            if(sf::Joystick::hasAxis(usedJoystick,(sf::Joystick::Axis)j))
            {
                std::cout << "Axe " << axisName[j] << " value : ";
                joyInfosMutex.lock();
                std::cout << joyAxisValues[j] << std::endl;
                joyInfosMutex.unlock();
            }
        }

        sf::sleep(sf::milliseconds(JOY_THD_SLEEP));
    }
}

/**
 * Get used joystick status by polling events
 */
void getJoystickStat(sf::RenderWindow& window)
{
    //Environment
    sf::Event ev;

    //Algo
    while(window.pollEvent(ev))
    {
        // Processing event
        switch(ev.type)
        {
            case sf::Event::JoystickButtonPressed:
                if(ev.joystickButton.joystickId == usedJoystick)
                {
                    joyInfosMutex.lock();
                    joyButtonPressed[ev.joystickButton.button] = true;
                    joyInfosMutex.unlock();
                }
                break;

            case sf::Event::JoystickButtonReleased:
                if(ev.joystickButton.joystickId == usedJoystick)
                {
                    joyInfosMutex.lock();
                    joyButtonPressed[ev.joystickButton.button] = false;
                    joyInfosMutex.unlock();
                }
                break;

            case sf::Event::JoystickMoved:
                if(ev.joystickButton.joystickId == usedJoystick)
                {
                    joyInfosMutex.lock();
                    joyAxisValues[(int)ev.joystickMove.axis] = ev.joystickMove.position;
                    joyInfosMutex.unlock();
                }
                break;

            case sf::Event::Closed:
                window.close();
                break;

            // Any other cases
            default:
                // Nothing to do
                break;
        }    
    }   
}