#ifndef _HEADER_MAP_
#define _HEADER_MAP_

#include "Point.hpp"
#include "Objet.hpp"

#ifdef GRAPHIC
    //SFML
    #include <SFML/Graphics.hpp>
#endif

class Map
{
public:
	Map();
	~Map();

#ifdef GRAPHIC
	int drawObjects(sf::RenderWindow &w);
#endif

private:
	const static int nbProductionMachine = 24;
	const static int nbDeliveryMachine = 6;
	const static int nbRecyclingMachine = 2;
	Objet *_production_machine[nbProductionMachine];
	Objet *_delivery_machine[nbDeliveryMachine];
	Objet *_recycling_machine[nbRecyclingMachine];

	const static int nbPointsLignes = 9;
	const static int nbPointsColonnes = 19;
	Point *_pointsPassage[nbPointsLignes][nbPointsColonnes];
};

#endif