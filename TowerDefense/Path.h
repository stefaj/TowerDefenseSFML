#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "tile_node.h"
using namespace std;
using namespace sf;
namespace Pathfinding
{
	class Path
	{
	public:
		Path(vector<TileNode> nodes);
		Path();
		~Path();

		const vector<Vector2f> GetPoints();
		const vector<float> GetLengths();
		const vector<Vector2f> GetDirections();

	private:
		vector<Vector2f> points;
		vector<float> lengths;
		vector<Vector2f> directions;
		void Build();
	};

}