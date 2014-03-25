#include "Point.hpp"


	Point::Point(signed int x, signed int y, typePoint type)
	{
		setPosition(x,y);
		setType(type);
	#ifdef GRAPHIC
		constructShape();
	#endif
		setH(0);
		setG(0);
		setF(0);
		setPointPrec(NULL);
		setLigne(-1);
		setColonne(-1);
	}

	Point::Point(signed int x, signed int y, signed int ligne, signed int colonne, typePoint type)
	{
		//Point(x,y,ligne,colonne,type);
		setPosition(x,y);
		setType(type);
	#ifdef GRAPHIC
		constructShape();
	#endif
		setH(0);
		setG(0);
		setF(0);
		setPointPrec(NULL);
		setLigne(ligne);
		setColonne(colonne);
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

	signed int Point::getX() const
	{
		return _x;
	}

	signed int Point::getY() const
	{
		return _y;
	}

	typePoint Point::getType() const
	{
		return _type;
	}

	// A Star	
	int Point::setPointPrec(Point *pointPrecedent)
	{
		_pointPrecedent = pointPrecedent;
		return 0;
	}

	int Point::getPointPrec(Point *&pointPrecedent)
	{
		pointPrecedent = _pointPrecedent;
		return 0;
	}

	signed int Point::getH() const
	{
		return _h;
	}

	signed int Point::getG() const
	{
		return _g;
	}

	signed int Point::getF() const
	{
		return _f;
	}

	void Point::setH(signed int h)
	{
		_h = h;
	}

	void Point::setG(signed int g)
	{
 		_g = g;
	}

	void Point::setF(signed int f)
	{
		_f = f;
	}

	signed int Point::getLigne() const
	{
		return _ligne;
	}

	signed int Point::getColonne() const
	{
		return _colonne;
	}

	void Point::setLigne(signed int ligne)
	{
		_ligne = ligne;
	}

	void Point::setColonne(signed int colonne)
	{
		_colonne = colonne;
	}

	bool Point::isFree()
	{
		return (_type == LIBRE);
	}

	signed int Point::distWith(Point const& pointDistant) const
	{
		signed int dist = 0;
		signed int distX = 0, distY = 0;

		distX = std::abs(pointDistant.getX() - getX());
		distY = std::abs(pointDistant.getY() - getY());

		dist = std::sqrt(std::pow(distX,2)+std::pow(distY,2));

		return dist;
	}


#ifdef GRAPHIC
	int Point::constructShape()
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


	int Point::reConstructShape()
	{
		switch(_type)
		{
			case LIBRE:
		        _shape->setFillColor(sf::Color::Blue);
		        _shape->setPosition((int)(562.5-_x)-2, 38+_y-2);
			break;

			case OCCUPE_AMI:
		        _shape->setFillColor(sf::Color::Green);
		        _shape->setPosition((int)(562.5-_x)-2, 38+_y-2);
			break;

			case OCCUPE_ADVERSAIRE:
		        _shape->setFillColor(sf::Color::Red);
		        _shape->setPosition((int)(562.5-_x)-2, 38+_y-2);
			break;

			case INTERDIT:
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


	bool operator<(Point const& p1, Point const& p2)
	{
		return p1.getF()<p2.getF();
	}
	bool operator<=(Point const& p1, Point const& p2)
	{
		return p1.getF()<=p2.getF();
	}
	bool operator>(Point const& p1, Point const& p2)
	{
		return p1.getF()>p2.getF();
	}
	bool operator>=(Point const& p1, Point const& p2)
	{
		return p1.getF()>=p2.getF();
	}
	bool operator==(Point const& p1, Point const& p2)
	{
		return (p1.getLigne() == p2.getLigne() && p1.getColonne() == p2.getColonne());
	}
