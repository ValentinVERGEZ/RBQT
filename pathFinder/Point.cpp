#include "Point.hpp"

	Point::Point(signed int x, signed int y, typePoint type)
	{
		setPosition(x,y);
		setType(type);
	#ifdef GRAPHIC
		constuctShape();
	#endif
	}

	Point::~Point()
	{
	}

	int Point::setPosition(signed int x, signed int y)
	{
		_x = x;
		_y = y;

		return 0;
	}

	int Point::setType(typePoint type)
	{
		_type = type;

		return 0;
	}

	signed int Point::getX()
	{
		return _x;
	}

	signed int Point::getY()
	{
		return _y;
	}

	typePoint Point::getType()
	{
		return _type;
	}


#ifdef GRAPHIC
	int Point::constuctShape()
	{
		switch(_type)
		{
			case LIBRE:
				_shape = new sf::CircleShape(4);
		        _shape->setFillColor(sf::Color::Blue);
		        _shape->setPosition((int)(562.5-_x)-2, 38+_y-2);
			break;

			case OCCUPE_AMI:
				_shape = new sf::CircleShape(4);
		        _shape->setFillColor(sf::Color::Green);
		        _shape->setPosition((int)(562.5-_x)-2, 38+_y-2);
			break;

			case OCCUPE_ADVERSAIRE:
				_shape = new sf::CircleShape(4);
		        _shape->setFillColor(sf::Color::Red);
		        _shape->setPosition((int)(562.5-_x)-2, 38+_y-2);
			break;

			case INTERDIT:
				_shape = new sf::CircleShape(4,4);
		        _shape->setFillColor(sf::Color::Black);
		        _shape->setPosition((int)(562.5-_x)-2, 38+_y-2);
			break;

			default:
				_shape = new sf::CircleShape(0);
			break;
		}


		return 0;
	}

	int Point::draw(sf::RenderWindow &w)
	{
		w.draw(*_shape);
		return 0;
	}

#endif
