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
    Point *startPoint,*endPoint;
    std::vector<Point*> chemin;

    mapRobocup.getPointAt(6,9,startPoint);
    mapRobocup.getPointAt(8,5,endPoint);
    mapRobocup.computeAStar(chemin,startPoint,endPoint);

    std::cout << "Taille du chemin trouvé : " << chemin.size() << std::endl;


    std::cout << "Depart : " << startPoint->getLigne() << "," << startPoint->getColonne() << std::endl;
    for (unsigned int i = 0; i < chemin.size(); ++i)
    {
        std::cout << "\tPoint : " << chemin[i]->getLigne() << "," << chemin[i]->getColonne() << " f :" << chemin[i]->getF()  << " g :" << chemin[i]->getG()  << " h :" << chemin[i]->getH() << std::endl;
    }
    std::cout << "Arrivee : " << endPoint->getLigne() << "," << endPoint->getColonne() << std::endl;

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

