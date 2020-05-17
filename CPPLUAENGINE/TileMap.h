#pragma once

#include "Tile.h"

class TileMap
{
private:
	std::vector< std::vector< std::vector< Tile* > > > map;

public:
	TileMap(unsigned world_size_x, unsigned world_size_y);

};

