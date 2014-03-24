#ifndef _HEADER_POINT_
#define _HEADER_POINT_

#ifdef GRAPHIC
    //SFML
    #include <SFML/Graphics.hpp>
#endif

enum typePoint{LIBRE=1,OCCUPE_AMI,OCCUPE_ADVERSAIRE,INTERDIT};

class Point
{
public:
	Point(signed int x, signed int y, typePoint type = LIBRE);
	~Point();
	int setPosition(signed int x, signed int y);
	int setType(typePoint type);
	signed int getX();
	signed int getY();
	typePoint getType();
#ifdef GRAPHIC
	int constuctShape();
	int draw(sf::RenderWindow &w);
#endif

private:
	// Position du point
	signed int _x;
	signed int _y;

	// Type
	typePoint _type;

	// Graphique
	#ifdef GRAPHIC
public:
		sf::CircleShape *_shape;
	#endif
};

#endif	// _HEADER_POINT_