#include "Path.h"
#include <cmath>
#include "Constant.h"

using namespace Pathfinding;
Path::Path(vector<TileNode> nodes)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		TileNode n = nodes[i];
		Vector2f vec(n.x * 32, n.y * 32);
		points.push_back(vec);
	}
	Build();
}

Path::Path()
{
}


Path::~Path()
{
}

void Path::Build()
{
	if (points.size() == 0)
		return;
	for (int i = 0; i < points.size() - 1; i++)
	{
		Vector2f direction = points[i + 1] - points[i];
		float length = sqrt(direction.x*direction.x +
			direction.y*direction.y);

		lengths.push_back(length);

		direction.x = direction.x / length;
		direction.y = direction.y / length;

		directions.push_back(direction);		
	}
}

const vector<Vector2f> Path::GetPoints()
{
	return points;
}
const vector<float> Path::GetLengths()
{
	return lengths;
}
const vector<Vector2f> Path::GetDirections()
{
	return directions;
}