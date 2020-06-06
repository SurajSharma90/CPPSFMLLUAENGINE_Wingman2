#include "pch.h"
#include "Tile.h"

Tile::Tile(sf::Texture& texture_sheet, sf::IntRect texture_rect, unsigned tile_size, unsigned grid_pos_x, unsigned grid_pos_y)
{
	this->sprite.setTexture(texture_sheet);
	this->sprite.setTextureRect(texture_rect);

	this->sprite.setPosition(static_cast<sf::Vector2f>(sf::Vector2u(tile_size * grid_pos_x, tile_size * grid_pos_y)));
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

