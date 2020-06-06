#pragma once

#include "Tile.h"

class TileMap
{
private:
	unsigned tileSize; 
	sf::Vector3<unsigned> worldSize;
	sf::Texture textureSheet;
	std::vector< std::vector< std::vector< std::vector< Tile* > > > > tiles;

	void initTileMap();
	void initTextureSheet();

public:
	TileMap(unsigned tile_size, unsigned world_size_x, unsigned world_size_y, unsigned world_size_z);
	~TileMap();

	void addTile(const unsigned grid_pos_x, const unsigned grid_pos_y, const unsigned grid_pos_z, const sf::IntRect texture_rect);

	void update();

	void render(sf::RenderTarget& target);
};

