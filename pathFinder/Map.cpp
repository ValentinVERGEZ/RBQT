#include "Map.hpp"

	Map::Map()
	{		
		std::cout << "Objet Map, instanciation" << std::endl;		
		std::cout << "Machines ..." << std::endl;
		// Création des machines 
		_production_machine[0] = new Objet(MACHINE,56,168,-90);
		_production_machine[1] = new Objet(MACHINE,56,280,90);
		_production_machine[2] = new Objet(MACHINE,168,168,180);
		_production_machine[3] = new Objet(MACHINE,168,280,0);
		_production_machine[4] = new Objet(MACHINE,168,392,0);
		_production_machine[5] = new Objet(MACHINE,280,168,90);
		_production_machine[6] = new Objet(MACHINE,280,392,-90);
		_production_machine[7] = new Objet(MACHINE,280,504,180);
		_production_machine[8] = new Objet(MACHINE,392,168,0);
		_production_machine[9] = new Objet(MACHINE,392,280,90);
		_production_machine[10] = new Objet(MACHINE,392,504,-90);
		_production_machine[11] = new Objet(MACHINE,504,504,-90);
		_production_machine[12] = new Objet(MACHINE,-56,168,-90);
		_production_machine[13] = new Objet(MACHINE,-56,280,90);
		_production_machine[14] = new Objet(MACHINE,-168,168,180);
		_production_machine[15] = new Objet(MACHINE,-168,280,0);
		_production_machine[16] = new Objet(MACHINE,-168,392,0);
		_production_machine[17] = new Objet(MACHINE,-280,168,90);
		_production_machine[18] = new Objet(MACHINE,-280,392,-90);
		_production_machine[19] = new Objet(MACHINE,-280,504,180);
		_production_machine[20] = new Objet(MACHINE,-392,168,0);
		_production_machine[21] = new Objet(MACHINE,-392,280,90);
		_production_machine[22] = new Objet(MACHINE,-392,504,-90);
		_production_machine[23] = new Objet(MACHINE,-504,504,-90);

		_delivery_machine[0] = new Objet(DELIVERY,534,245,180);
		_delivery_machine[1] = new Objet(DELIVERY,534,280,180);
		_delivery_machine[2] = new Objet(DELIVERY,534,315,180);
		_delivery_machine[3] = new Objet(DELIVERY,-534,245,0);
		_delivery_machine[4] = new Objet(DELIVERY,-534,280,0);
		_delivery_machine[5] = new Objet(DELIVERY,-534,315,0);

		_recycling_machine[0] = new Objet(RECYCLING,56,504,0);
		_recycling_machine[1] = new Objet(RECYCLING,-56,504,180);
		std::cout << "DONE" << std::endl;


		std::cout << "Point ..." << std::endl;
		//Création des points
		for (int i = 0; i < nbPointsLignes; ++i)
		{
			for (int j = 0; j < nbPointsColonnes; ++j)
			{
				std::cout << "Point x : " << i << " y : " << j << std::endl;
				_pointsPassage[i][j] = new Point(-504+j*56,56+i*56,i,j);
			}
		}				
		_pointsPassage[2][2]->setType(INTERDIT);
		_pointsPassage[2][4]->setType(INTERDIT);
		_pointsPassage[2][6]->setType(INTERDIT);
		_pointsPassage[2][8]->setType(INTERDIT);
		_pointsPassage[2][10]->setType(INTERDIT);
		_pointsPassage[2][12]->setType(INTERDIT);
		_pointsPassage[2][14]->setType(INTERDIT);
		_pointsPassage[2][16]->setType(INTERDIT);
		
		_pointsPassage[4][2]->setType(INTERDIT);
		_pointsPassage[4][6]->setType(INTERDIT);
		_pointsPassage[4][8]->setType(INTERDIT);
		_pointsPassage[4][10]->setType(INTERDIT);
		_pointsPassage[4][12]->setType(INTERDIT);
		_pointsPassage[4][16]->setType(INTERDIT);

		_pointsPassage[6][4]->setType(INTERDIT);
		_pointsPassage[6][6]->setType(INTERDIT);
		_pointsPassage[6][12]->setType(INTERDIT);
		_pointsPassage[6][14]->setType(INTERDIT);

		_pointsPassage[8][0]->setType(INTERDIT);
		_pointsPassage[8][2]->setType(INTERDIT);
		_pointsPassage[8][4]->setType(INTERDIT);
		_pointsPassage[8][8]->setType(INTERDIT);
		_pointsPassage[8][10]->setType(INTERDIT);
		_pointsPassage[8][14]->setType(INTERDIT);
		_pointsPassage[8][16]->setType(INTERDIT);
		_pointsPassage[8][18]->setType(INTERDIT);
		std::cout << "DONE" << std::endl;

		_allowDiagonal = true;
		_crossCorner = false;
		_heuristicFonction = MANHATTAN;
		_poidsHeuristic = 1;

		std::cout << "Objet Map correctement instancié" << std::endl;
	}

	Map::~Map()
	{
	}

	// AStar	
	void Map::setAllowDiagonal(bool allowDiagonal)
	{
		_allowDiagonal = allowDiagonal;
	}

	void Map::setCrossCorner(bool crossCorner)
	{
		_crossCorner = crossCorner;
	}

	void Map::setPoidsHeuristic(signed int poids)
	{
		_poidsHeuristic = poids;
	}

	signed int Map::heuristic(Point const& pointDepart, Point const& pointDistant)
	{
		switch(_heuristicFonction)
		{
			case MANHATTAN:
				return heuristicManhattan(pointDepart,pointDistant);
			break;

			case EUCLIDEAN:
				return heuristicEuclidean(pointDepart,pointDistant);
			break;

			default:
				return -1;
			break;
		}
	}

	signed int Map::heuristicManhattan(Point const& pointDepart, Point const& pointDistant)
	{
		signed int dist = 0;
		signed int distX = 0, distY = 0;

		distX = std::abs(pointDistant.getX() - pointDepart.getX());
		distY = std::abs(pointDistant.getY() - pointDepart.getY());

		dist = distX+distY;

		return dist;
	}

	signed int Map::heuristicEuclidean(Point const& pointDepart, Point const& pointDistant)
	{
		signed int dist = 0;
		signed int distX = 0, distY = 0;

		distX = std::abs(pointDistant.getX() - pointDepart.getX());
		distY = std::abs(pointDistant.getY() - pointDepart.getY());

		dist = std::sqrt(std::pow(distX,2)+std::pow(distY,2));

		return dist;
	}

	signed int Map::heuristicChebyshev(Point const& pointDepart, Point const& pointDistant)
	{
		signed int dist = 0;
		signed int distX = 0, distY = 0;

		distX = std::abs(pointDistant.getX() - pointDepart.getX());
		distY = std::abs(pointDistant.getY() - pointDepart.getY());

		dist = std::max(distX,distY);

		return dist;
	}

	void Map::setHeuristicFunction(typeHeuristic heuristicFonction)
	{
		_heuristicFonction = heuristicFonction;
	}

	bool Map::isFreeAt(signed int li, signed int col)
	{
		if(li < nbPointsLignes && li >= 0 && col < nbPointsColonnes && col>=0)
			return _pointsPassage[li][col]->isFree();
		else 
			return false;
	}

/*
 *
 * 	simpleOffsets:	diagonalOffsets:
 *  +---+---+---+    +---+---+---+
 *  |   | 0 |   |    | 0 |   | 1 |
 *  +---+---+---+    +---+---+---+
 *  | 3 |   | 1 |    |   |   |   |
 *  +---+---+---+    +---+---+---+
 *  |   | 2 |   |    | 3 |   | 2 |
 *  +---+---+---+    +---+---+---+
 *
 */
	signed int Map::getVoisins(std::vector<Point*> &voisins, Point *oirigin)
	{
		voisins.clear();
		signed int col, li;
		col = oirigin->getColonne();
		li = oirigin->getLigne();

		bool s0 = false, d0 = false,
        s1 = false, d1 = false,
        s2 = false, d2 = false,
        s3 = false, d3 = false;


	    // ↑
	    if (isFreeAt(li - 1, col)) {
	        voisins.push_back(_pointsPassage[li - 1][col]);
	        s0 = true;
	    }
	    // →
	    if (isFreeAt(li, col + 1)) {
	        voisins.push_back(_pointsPassage[li][col + 1]);
	        s1 = true;
	    }
	    // ↓
	    if (isFreeAt(li + 1, col)) {
	        voisins.push_back(_pointsPassage[li + 1][col]);
	        s2 = true;
	    }
	    // ←
	    if (isFreeAt(li, col - 1)) {
	        voisins.push_back(_pointsPassage[li][col - 1]);
	        s3 = true;
	    }

	    if (!_allowDiagonal)
	        return 0;

	    if (!_crossCorner) {
	        d0 = s3 && s0;
	        d1 = s0 && s1;
	        d2 = s1 && s2;
	        d3 = s2 && s3;
	    } else {
	        d0 = s3 || s0;
	        d1 = s0 || s1;
	        d2 = s1 || s2;
	        d3 = s2 || s3;
	    }

	    // ↖
	    if (d0 && isFreeAt(li - 1, col - 1)) {
	        voisins.push_back(_pointsPassage[li - 1][col - 1]);
	    }
	    // ↗
	    if (d1 && isFreeAt(li - 1, col + 1)) {
	        voisins.push_back(_pointsPassage[li - 1][col + 1]);
	    }
	    // ↘
	    if (d2 && isFreeAt(li + 1, col + 1)) {
	        voisins.push_back(_pointsPassage[li + 1][col + 1]);
	    }
	    // ↙
	    if (d3 && isFreeAt(li + 1, col - 1)) {
	        voisins.push_back(_pointsPassage[li + 1][col - 1]);
	    }
	    return 0;
	}

	signed int Map::computeAStar(std::vector<Point*> &chemin, Point *startPoint, Point *endPoint)
	{
		/* Just for test */
		// std::vector<Point*> cheminInv;
		// cheminInv.push_back(startPoint);
		// chemin.push_back(endPoint);
		
		// std::cout << "Computing AStar ..." << std::endl;

		// std::cout << "Test isFreeAt() ..." << std::endl;
		// _pointsPassage[4][5]->setType(INTERDIT);
		// std::cout << "2.3 : " << ((isFreeAt(2,3))?"FREE":"NOT") << " 4.5 : " << ((isFreeAt(4,5))?"FREE":"NOT") << std::endl;

		// std::cout << "Test getVoisins() ... " << std::endl;
		// std::vector<Point*> voisins;
		// unsigned int i;
		// getVoisins(voisins,_pointsPassage[4][6]);		
		// std::cout << "voisins.size() = " << voisins.size() << std::endl;
		// for (i = 0; i < voisins.size(); i++)
		// {
		// 	std::cout << "Voisins : " << voisins[i]->getLigne() << "," << voisins[i]->getColonne() << std::endl;
		// }
		// voisins.clear();


		// std::cout << "Test getVoisins() without crossing corner... " << std::endl;
		// setCrossCorner(false);
		// getVoisins(voisins,_pointsPassage[4][6]);		
		// std::cout << "voisins.size() = " << voisins.size() << std::endl;
		// for (i = 0; i < voisins.size(); i++)
		// {
		// 	std::cout << "Voisins : " << voisins[i]->getLigne() << "," << voisins[i]->getColonne() << std::endl;
		// }
		// voisins.clear();

		// std::cout << "Test getVoisins() without diagonals... " << std::endl;
		// setCrossCorner(true);
		// setAllowDiagonal(false);
		// getVoisins(voisins,_pointsPassage[4][6]);		
		// std::cout << "voisins.size() = " << voisins.size() << std::endl;
		// for (i = 0; i < voisins.size(); i++)
		// {
		// 	std::cout << "Voisins : " << voisins[i]->getLigne() << "," << voisins[i]->getColonne() << std::endl;
		// }
		// voisins.clear();


//Création des points
		#ifdef GRAPHIC
		for (int i = 0; i < nbPointsLignes; ++i)
		{
			for (int j = 0; j < nbPointsColonnes; ++j)
			{
				_pointsPassage[i][j]->reConstructShape();
			}
		}				
		#endif

		chemin.clear();
		std::multiset<Point*,CompareF> aEvaluer;
		std::multiset<Point*> dejaEvalue;
		std::vector<Point*> voisins;
		unsigned int i;

		aEvaluer.insert(startPoint);
		while(!aEvaluer.empty())
		{
			//std::multiset<Point*>::iterator p;
			Point *p;
			// p = *(--(aEvaluer.end()));
			p = *(aEvaluer.begin());
			#ifdef GRAPHIC
			p->_shape->setFillColor(sf::Color::Blue);
			#endif

			std::cout << "A Evaluer Contains:";
			for (std::multiset<Point*>::iterator it=aEvaluer.begin(); it!=aEvaluer.end(); ++it )
			  	std::cout << ' ' << (*it)->getF();

			std::cout << '\n';


        	std::cout << "Point evalue: " << p->getLigne() << "," << p->getColonne() << " f :" << p->getF()  << " g :" << p->getG()  << " h :" << p->getH() << std::endl;

			if(p == endPoint)
			{
				std::cout << "Arrive au point terminal !" << std::endl;
				Point* prec;
				do
				{
					#ifdef GRAPHIC
					p->_shape->setFillColor(sf::Color::Green);
					#endif
					chemin.push_back(p);
					p->getPointPrec(prec);
					p = prec;
				}
				while(prec != NULL);

				std::reverse(chemin.begin(),chemin.end());

				return 0;
			}

			dejaEvalue.insert(p);
			aEvaluer.erase(p);
			getVoisins(voisins,p);
			std::cout << "Size voisins : " << voisins.size() << std::endl;
			for (i = 0; i < voisins.size(); i++)
			{
				if(dejaEvalue.count(voisins[i]) > 0 && voisins[i])
					continue;

				std::cout << "Voisin " << i << std::endl;

				signed int newG = p->getG() + voisins[i]->distWith(*p);

				if(aEvaluer.count(voisins[i]) == 0 || newG < voisins[i]->getG())
				{
					voisins[i]->setPointPrec(p);
					voisins[i]->setG(newG);
					voisins[i]->setH((voisins[i]->getH())?voisins[i]->getH():heuristic(*voisins[i], *endPoint));
					voisins[i]->setF(voisins[i]->getG()+_poidsHeuristic*voisins[i]->getH());
					aEvaluer.insert(voisins[i]);

        			std::cout << "\tNouveau Voisin : " << voisins[i]->getLigne() << "," << voisins[i]->getColonne() << " f :" << voisins[i]->getF()  << " g :" << voisins[i]->getG()  << " h :" << voisins[i]->getH() << std::endl;
				}
			}
		}

		return 0;		
	}


	signed int Map::getPointAt(signed int ligne, signed int colonne, Point*& point) const
	{
		if(ligne < nbPointsLignes && ligne >= 0 && colonne < nbPointsColonnes && colonne>=0)
		{
			point = _pointsPassage[ligne][colonne];
			return 0;
		}
		else 
			return -1;
	}



#ifdef GRAPHIC
	int Map::drawObjects(sf::RenderWindow &w)
	{		
		for(int i=0; i < nbProductionMachine; i++)
        	w.draw(*(_production_machine[i]->_shape));

		for(int i=0; i < nbDeliveryMachine; i++)
        	w.draw(*(_delivery_machine[i]->_shape));

		for(int i=0; i < nbRecyclingMachine; i++)
        	w.draw(*(_recycling_machine[i]->_shape));

		for(int i=0; i < nbPointsLignes; i++)
			for (int j = 0; j < nbPointsColonnes; ++j)
	        	w.draw(*(_pointsPassage[i][j]->_shape));

		return 0;
	}
#endif

// Grid.prototype.getNodeAt = function(x, y) {
//     return this.nodes[y][x];
// };


// /**
//  * Determine whether the node at the given position is walkable.
//  * (Also returns false if the position is outside the grid.)
//  * @param {number} x - The x coordinate of the node.
//  * @param {number} y - The y coordinate of the node.
//  * @return {boolean} - The walkability of the node.
//  */
// Grid.prototype.isWalkableAt = function(x, y) {
//     return this.isInside(x, y) && this.nodes[y][x].walkable;
// };


// /**
//  * Determine whether the position is inside the grid.
//  * XXX: `grid.isInside(x, y)` is wierd to read.
//  * It should be `(x, y) is inside grid`, but I failed to find a better
//  * name for this method.
//  * @param {number} x
//  * @param {number} y
//  * @return {boolean}
//  */
// Grid.prototype.isInside = function(x, y) {
//     return (x >= 0 && x < this.width) && (y >= 0 && y < this.height);
// };


// /**
//  * Set whether the node on the given position is walkable.
//  * NOTE: throws exception if the coordinate is not inside the grid.
//  * @param {number} x - The x coordinate of the node.
//  * @param {number} y - The y coordinate of the node.
//  * @param {boolean} walkable - Whether the position is walkable.
//  */
// Grid.prototype.setWalkableAt = function(x, y, walkable) {
//     this.nodes[y][x].walkable = walkable;
// };


// *
//  * Get the neighbors of the given node.
//  *
//  *     offsets      diagonalOffsets:
//  *  +---+---+---+    +---+---+---+
//  *  |   | 0 |   |    | 0 |   | 1 |
//  *  +---+---+---+    +---+---+---+
//  *  | 3 |   | 1 |    |   |   |   |
//  *  +---+---+---+    +---+---+---+
//  *  |   | 2 |   |    | 3 |   | 2 |
//  *  +---+---+---+    +---+---+---+
//  *
//  *  When allowDiagonal is true, if offsets[i] is valid, then
//  *  diagonalOffsets[i] and
//  *  diagonalOffsets[(i + 1) % 4] is valid.
//  * @param {Node} node
//  * @param {boolean} allowDiagonal
//  * @param {boolean} dontCrossCorners
 
// Grid.prototype.getNeighbors = function(node, allowDiagonal, dontCrossCorners) {
//     var x = node.x,
//         y = node.y,
//         neighbors = [],
//         s0 = false, d0 = false,
//         s1 = false, d1 = false,
//         s2 = false, d2 = false,
//         s3 = false, d3 = false,
//         nodes = this.nodes;

//     // ↑
//     if (this.isWalkableAt(x, y - 1)) {
//         neighbors.push(nodes[y - 1][x]);
//         s0 = true;
//     }
//     // →
//     if (this.isWalkableAt(x + 1, y)) {
//         neighbors.push(nodes[y][x + 1]);
//         s1 = true;
//     }
//     // ↓
//     if (this.isWalkableAt(x, y + 1)) {
//         neighbors.push(nodes[y + 1][x]);
//         s2 = true;
//     }
//     // ←
//     if (this.isWalkableAt(x - 1, y)) {
//         neighbors.push(nodes[y][x - 1]);
//         s3 = true;
//     }

//     if (!allowDiagonal) {
//         return neighbors;
//     }

//     if (dontCrossCorners) {
//         d0 = s3 && s0;
//         d1 = s0 && s1;
//         d2 = s1 && s2;
//         d3 = s2 && s3;
//     } else {
//         d0 = s3 || s0;
//         d1 = s0 || s1;
//         d2 = s1 || s2;
//         d3 = s2 || s3;
//     }

//     // ↖
//     if (d0 && this.isWalkableAt(x - 1, y - 1)) {
//         neighbors.push(nodes[y - 1][x - 1]);
//     }
//     // ↗
//     if (d1 && this.isWalkableAt(x + 1, y - 1)) {
//         neighbors.push(nodes[y - 1][x + 1]);
//     }
//     // ↘
//     if (d2 && this.isWalkableAt(x + 1, y + 1)) {
//         neighbors.push(nodes[y + 1][x + 1]);
//     }
//     // ↙
//     if (d3 && this.isWalkableAt(x - 1, y + 1)) {
//         neighbors.push(nodes[y + 1][x - 1]);
//     }

//     return neighbors;
// };

// 





  // /**
  //  * Manhattan distance.
  //  * @param {number} dx - Difference in x.
  //  * @param {number} dy - Difference in y.
  //  * @return {number} dx + dy
  //  */
  // manhattan: function(dx, dy) {
  //     return dx + dy;
  // },

  // *
  //  * Euclidean distance.
  //  * @param {number} dx - Difference in x.
  //  * @param {number} dy - Difference in y.
  //  * @return {number} sqrt(dx * dx + dy * dy)
   
  // euclidean: function(dx, dy) {
  //     return Math.sqrt(dx * dx + dy * dy);
  // },

  // /**
  //  * Chebyshev distance.
  //  * @param {number} dx - Difference in x.
  //  * @param {number} dy - Difference in y.
  //  * @return {number} max(dx, dy)
  //  */
  // chebyshev: function(dx, dy) {
  //     return Math.max(dx, dy);
  // }
