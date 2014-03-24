/* Includes */
    //StdLib
    #include <iostream>

    //SFML
    #include <SFML/Graphics.hpp>

    // Perso
    #include "main.hpp"
    #include "Map.hpp"
    #include "Objet.hpp"
    #include "Point.hpp"

/* Global variables and constants*/

    // Thread periods
    const unsigned int JOY_THD_SLEEP(50);

/* Main */
int main()
{
    //Environment
    Map mapRobocup;

    #ifdef GRAPHIC
        // Fenêtre de dessin
        sf::RenderWindow windowMap(sf::VideoMode(1125, 600), "Robocup Area");

    // Algo
    while (windowMap.isOpen())
    {
        // Gestion de tous les events depuis la dernière itération
        sf::Event event;
        while (windowMap.pollEvent(event))
        {
            // Fermeture de la fenêtre si demandée
            if (event.type == sf::Event::Closed)
                windowMap.close();
        }

        // Draw window
        windowMap.clear(sf::Color::White);
        mapRobocup.drawObjects(windowMap);
        windowMap.display();
    }

    #endif

    return 0;
}

