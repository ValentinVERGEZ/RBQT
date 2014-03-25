#ifndef _HEADER_OBJET_
#define _HEADER_OBJET_

#ifdef GRAPHIC
    //SFML
    #include <SFML/Graphics.hpp>
#endif

enum typeObjet{MACHINE,ROBOTINO,DELIVERY,RECYCLING};

class Objet
{
public:
	Objet(typeObjet type, signed int x, signed int y);
	Objet(typeObjet type, signed int x, signed int y,int phi);
	~Objet();
	int setPosition(signed int x, signed int y);
	int setPosition(signed int x, signed int y, int phi);
	int setType(typeObjet type);
	signed int getX() const;
	signed int getY() const;
	int getPhi() const;
#ifdef GRAPHIC
	int constuctShape();
	int draw(sf::RenderWindow &w);
#endif

private:
	// Position de l'objet
	signed int _x;
	signed int _y;
	int _phi;	

	// Type
	typeObjet _type;

	// Graphique
	#ifdef GRAPHIC
public:
		sf::Shape *_shape;
	#endif
};

#endif	// _HEADER_OBJET_