#include "pch.h"
#include "TileMap.h"

void TileMap::initTileMap()
{
	if (this->worldSize.x <= 0)
		this->worldSize.x = 1;
	if (this->worldSize.y <= 0)
		this->worldSize.y = 1;
	if (this->worldSize.z <= 0)
		this->worldSize.z = 1;

	this->tiles.resize(this->worldSize.x);
	
	for (auto& arrX : this->tiles)
	{
		arrX.resize(this->worldSize.y);

		for (auto& arrY : arrX)
		{
			arrY.resize(this->worldSize.z);

			for (auto& arrZ : arrY)
			{
				arrZ.resize(1);
				arrZ[0] = nullptr;
			}
		}
	}
}

void TileMap::initTextureSheet()
{
	this->textureSheet.loadFromFile("Textures/Map/textureSheet.png");
}

TileMap::TileMap(unsigned tile_size, unsigned world_size_x, unsigned world_size_y, unsigned world_size_z)
	: tileSize(tile_size), worldSize(world_size_x, world_size_y, world_size_z)
{
	this->initTileMap();
	this->initTextureSheet();
}

TileMap::~TileMap()
{
	for (auto& arrX : this->tiles)
	{
		for (auto& arrY : arrX)
		{
			for (auto& arrZ : arrY)
			{
				for (auto* tile : arrZ)
				{
					if (tile)
						delete tile;
				}
			}
		}
	}
}

void TileMap::addTile(const unsigned grid_pos_x, const unsigned grid_pos_y, const unsigned grid_pos_z, const sf::IntRect texture_rect)
{
	if(grid_pos_x < this->worldSize.x && grid_pos_y < this->worldSize.y && grid_pos_z < this->worldSize.z
		&& grid_pos_x >= 0 && grid_pos_y >= 0 && grid_pos_z >= 0)
		this->tiles[grid_pos_x][grid_pos_y][grid_pos_z].push_back(new Tile(this->textureSheet, texture_rect, this->tileSize, grid_pos_x, grid_pos_y));
}

void TileMap::update()
{
	for (auto& arrX : this->tiles)
	{
		for (auto& arrY : arrX)
		{
			for (auto& arrZ : arrY)
			{
				for (auto* tile : arrZ)
				{
					if(tile)
						tile->update();
				}
			}
		}
	}
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& arrX : this->tiles)
	{
		for (auto& arrY : arrX)
		{
			for (auto& arrZ : arrY)
			{
				for (auto* tile : arrZ)
				{
					if(tile)
						tile->render(target);
				}
			}
		}
	}
}
