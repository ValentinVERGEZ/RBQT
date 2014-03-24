#include "Objet.hpp"


	Objet::Objet(typeObjet type, signed int x, signed int y)
	{
		setType(type);
		setPosition(x, y);
		_phi = 0;
	#ifdef GRAPHIC
		constuctShape();
	#endif
	}

	Objet::Objet(typeObjet type, signed int x, signed int y, int phi)
	{
		setType(type);
		setPosition(x, y, phi);
	#ifdef GRAPHIC
		constuctShape();
	#endif
	}

	Objet::~Objet()
	{
	}

	int Objet::setPosition(signed int x, signed int y)
	{
		_x = x;
		_y = y;

		return 0;
	}

	int Objet::setPosition(signed int x, signed int y, int phi)
	{	
		setPosition(x, y);
		_phi = (phi%360);
        if (_phi > 180)
            _phi = _phi-360;
        else if(_phi <= -180)
            _phi = _phi+360;

		return 0;
	}

	int Objet::setType(typeObjet type)
	{	
		_type = type;

		return 0;
	}

	signed int Objet::getX()
	{
		return _x;
	}

	signed int Objet::getY()
	{
		return _y;
	}

	int Objet::getPhi()
	{
		return _phi;
	}


#ifdef GRAPHIC
	int Objet::constuctShape()
	{
		switch(_type)
		{
			case MACHINE:
				_shape = new sf::RectangleShape(sf::Vector2f(50, 50));
		        _shape->setFillColor(sf::Color::White);
		        _shape->setOutlineThickness(-2);
		        _shape->setOutlineColor(sf::Color::Black);
		        _shape->setPosition((int)(562.5-_x)-25, 38+_y-25);
		        _shape->setRotation(0);
			break;

			case RECYCLING:
				_shape = new sf::RectangleShape(sf::Vector2f(50, 50));
		        _shape->setFillColor(sf::Color::White);
		        _shape->setOutlineThickness(-2);
		        _shape->setOutlineColor(sf::Color::Green);
		        _shape->setPosition((int)(562.5-_x)-25, 38+_y-25);
		        _shape->setRotation(0);
			break;

			case DELIVERY:
				_shape = new sf::RectangleShape(sf::Vector2f(40, 20));
		        _shape->setFillColor(sf::Color::Green);
		        _shape->setOutlineThickness(-2);
		        _shape->setOutlineColor(sf::Color::Black);
		        _shape->setPosition((int)(562.5-_x)-25, 38+_y-25);
		        _shape->setRotation(0);
			break;

			case ROBOTINO:
				_shape = new sf::CircleShape(37.5/2);
		        _shape->setFillColor(sf::Color::Blue);
		        _shape->setOutlineThickness(-2);
		        _shape->setOutlineColor(sf::Color::Black);
			break;

			default:
				_shape = new sf::CircleShape(0);
			break;
		}

		return 0;
	}

	int Objet::draw(sf::RenderWindow &w)
	{
		w.draw(*_shape);
		return 0;
	}

#endif
