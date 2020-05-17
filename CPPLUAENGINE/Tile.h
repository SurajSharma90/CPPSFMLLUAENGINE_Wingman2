#pragma once

class Tile
{
private:
	sf::Texture& texture;
	sf::Sprite sprite;
	//int type;

public:
	Tile(sf::Texture& texture, sf::IntRect texture_rect, unsigned tile_size, unsigned grid_pos_x, unsigned grid_pos_y)
		: texture(texture)
	{
		this->sprite.setTexture(this->texture);
		this->sprite.setTextureRect(texture_rect);

		this->sprite.setPosition(static_cast<sf::Vector2f>(sf::Vector2u(tile_size * grid_pos_x, tile_size * grid_pos_y)));
	}
};

