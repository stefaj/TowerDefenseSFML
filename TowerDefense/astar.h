#pragma once
#include "tile_node.h"
#include <vector>
#include <cmath>
namespace Pathfinding
{

	class AStar
	{
	public:
		AStar(int x_size, int y_size, TileNode**);
		std::vector<TileNode> Search(TileNode &start, TileNode &end);
		std::vector<TileNode*> GetNeighbours(TileNode &node);
		static bool FindGraphNode(std::vector<TileNode*> node_list, TileNode &node);
		static float ManhattanHeuristic(TileNode a, TileNode b);
		static float EuclidianHeuristic(TileNode a, TileNode b);

	private:
		int grid_nx;
		int grid_ny;
		TileNode **grid;

	};
}
