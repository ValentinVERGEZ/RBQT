#include "Map.hpp"

	Map::Map()
	{		
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

		//Création des points
		for (int i = 0; i < nbPointsLignes; ++i)
		{
			for (int j = 0; j < nbPointsColonnes; ++j)
			{
				_pointsPassage[i][j] = new Point(-504+j*56,56+i*56);
			}
		}
	}

	Map::~Map()
	{
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