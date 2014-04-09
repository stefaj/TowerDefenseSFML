#include "tile_node.h"
using namespace Pathfinding;

TileNode::TileNode()
{
    x=y=g=h=0;
    parent = nullptr;
	type = 0;
}

TileNode::TileNode(int px, int py, TileNode *parentNode)
{
    x=px;
    y=py;
    parent = parentNode;
    g=h=0;
	type = TILENODE_TYPES::FREE_PATH;
}

const int TileNode::f()
{
	return h;
   return g+h;
}

