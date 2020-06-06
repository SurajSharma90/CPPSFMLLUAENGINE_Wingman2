#pragma once

class Tile
{
private:
	sf::Sprite sprite;
	//int type;

public:
	Tile(sf::Texture& texture_sheet, sf::IntRect texture_rect, unsigned tile_size, unsigned grid_pos_x, unsigned grid_pos_y);

	void update();

	void render(sf::RenderTarget& target);
};

