#ifndef _HEADER_MAP_
#define _HEADER_MAP_

#include "Point.hpp"
#include "Objet.hpp"
#include <set>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

#ifdef GRAPHIC
    //SFML
    #include <SFML/Graphics.hpp>
#endif

enum typeHeuristic{MANHATTAN,EUCLIDEAN,Chebyshev};

class Map
{
public:
	Map();
	~Map();

	// AStar
	void setAllowDiagonal(bool allowDiagonal);
	void setCrossCorner(bool crossCorner);
	void setPoidsHeuristic(signed int poids);
	signed int heuristic(Point const& pointDepart, Point const& pointDistant);
	signed int heuristicManhattan(Point const& pointDepart, Point const& pointDistant);
	signed int heuristicEuclidean(Point const& pointDepart, Point const& pointDistant);
	signed int heuristicChebyshev(Point const& pointDepart, Point const& pointDistant);
	void setHeuristicFunction(typeHeuristic heuristicFonction);
	bool isFreeAt(signed int li, signed int col);
	signed int getVoisins(std::vector<Point*> &voisins, Point *oirigin);
	signed int computeAStar(std::vector<Point*> &chemin, Point *startPoint, Point *endPoint);
	signed int getPointAt(signed int ligne, signed int colonne, Point*& point) const;

#ifdef GRAPHIC
	int drawObjects(sf::RenderWindow &w);
#endif

private:
	// Machines
	const static int nbProductionMachine = 24;
	const static int nbDeliveryMachine = 6;
	const static int nbRecyclingMachine = 2;
	Objet *_production_machine[nbProductionMachine];
	Objet *_delivery_machine[nbDeliveryMachine];
	Objet *_recycling_machine[nbRecyclingMachine];

	// Points
	const static int nbPointsLignes = 9;
	const static int nbPointsColonnes = 19;
	Point *_pointsPassage[nbPointsLignes][nbPointsColonnes];

	// AStar	
	bool _allowDiagonal;
	bool _crossCorner;
	signed int _poidsHeuristic;
	typeHeuristic _heuristicFonction;
};

class CompareF
{
public:
    bool operator()(Point* const& a, Point* const& b) const
    {
        return a->getF() < b->getF();
    }
};

#endif	// _HEADER_MAP_