#ifndef TILE_H
#define TILE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
//
class Tile
{
    public:
        Tile();
        int getTileX()
		{
			return tileX_;
		}
		void setTileX(int tileX);

		void setTileXOffset(int tileXoffset);

        int getTileY()
		{
			return tileY_;
		}
		void setTileY(int tileY);

		void setTileYOffset(int tileYoffset);

		int getTileType()
		{
			return tiletype_;
		}
		void setTileType(int tiletype);

		ALLEGRO_COLOR getColour()
		{
			return colour_;
		}
		void setColour(ALLEGRO_COLOR colour);

		void drawTile(int mapXoffset, int mapYoffset, int displaywidth, int displayheight);

    private:	
        int tileX_, tileY_;
		int tiletype_;//0 = empty, 1 = solid,
		ALLEGRO_COLOR colour_;
};
#endif