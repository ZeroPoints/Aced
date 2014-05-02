#include "tile.h"
const int tileSize = 20;

Tile::Tile()
{
}

void Tile::setColour(ALLEGRO_COLOR colour)
{
	colour_ = colour;
}

void Tile::setTileType(int tiletype)
{
	tiletype_ = tiletype;
}

void Tile::setTileX(int tileX)
{
	tileX_ = tileX;
}

void Tile::setTileY(int tileY)
{
	tileY_ = tileY;
}



void Tile::drawTile(int mapXoffset, int mapYoffset, int displaywidth, int displayheight)
{
	
		al_draw_filled_rectangle(tileX_*20 + mapXoffset*20, tileY_*20 + mapYoffset*20, tileX_*20 + tileSize + mapXoffset*20, tileY_*20 + tileSize + mapYoffset*20, colour_);
	
}