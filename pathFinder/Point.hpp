#ifndef _HEADER_POINT_
#define _HEADER_POINT_

#include <cmath>
#include <cstddef>

#ifdef GRAPHIC
    //SFML
    #include <SFML/Graphics.hpp>
#endif

enum typePoint{LIBRE=1,OCCUPE_AMI,OCCUPE_ADVERSAIRE,INTERDIT};

class Point
{
public:
	Point(signed int x, signed int y, typePoint type = LIBRE);
	Point(signed int x, signed int y, signed int ligne, signed int colonne, typePoint type = LIBRE);
	~Point();
	int setPosition(signed int x, signed int y);
	int setType(typePoint type);
	signed int getX() const;
	signed int getY() const;
	typePoint getType() const;
	// AStar
	int setPointPrec(Point *pointPrecedent);
	int getPointPrec(Point *&pointPrecedent);
	signed int getH() const;
	signed int getG() const;
	signed int getF() const;
	void setH(signed int h);
	void setG(signed int g);
	void setF(signed int f);
	signed int getLigne() const;
	signed int getColonne() const;
	void setLigne(signed int ligne);
	void setColonne(signed int colonne);
	bool isFree();
	signed int distWith(Point const& pointDistant) const;

#ifdef GRAPHIC
	int constructShape();
	int reConstructShape();
	int draw(sf::RenderWindow &w);
#endif

private:
	// Position du point
	signed int _x;
	signed int _y;
	signed int _ligne;
	signed int _colonne;

	// Type
	typePoint _type;

	// AStar
	Point *_pointPrecedent;
	signed int _h;
	signed int _g;
	signed int _f;

	// Graphique
	#ifdef GRAPHIC
public:
		sf::CircleShape *_shape;
	#endif
};
// Surcharge d'opérateurs
	bool operator<(Point const& p1, Point const& p2);
	bool operator==(Point const& p1, Point const& p2);

#endif	// _HEADER_POINT_