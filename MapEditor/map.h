#ifndef MAP_H
#define MAP_H

#include "tile.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <vector>

class Map
{
    public:
        Map();

        int getMapWidth()
		{
			return mapwidth_;
		}
        int getMapHeight()
		{
			return mapheight_;
		}
		int getPlayerStartX()
		{
			return playerStartX_;
		}
		int getPlayerStartY()
		{
			return playerStartY_;
		}
		std::vector<std::vector<Tile>> &getTiles()
		{
			return tiles_;
		}

		void setMapYOffset(int mapYoffset);
		void setMapXOffset(int mapXoffset);

		void saveMap(ALLEGRO_DISPLAY *display);
		void loadMap(ALLEGRO_DISPLAY *display);
		void drawMap();

		void setDisplayHeight(int displayheight);
		void setDisplayWidth(int displaywidth);


		void setMapHeight(int mapheight);
		void setMapWidth(int mapwidth);
		void resetMapHeight(int newmapheight);
		void resetMapWidth(int newmapwidth);
		void setPlayerStartX(int playerStartX);
		void setPlayerStartY(int playerStartY);
		void createTiles();

    private:
		int displayheight_;
		int displaywidth_;
        int mapwidth_;//of map
        int mapheight_;//of map
		int oldmapwidth_;//for resize
        int oldmapheight_;//for resize
		int mapYoffset_;//for when you moved the player past screenthingytypestuff
		int mapXoffset_;


		int playerStartX_;//players starting position
		int playerStartY_;
		std::vector<std::vector<Tile>> tiles_;
};
#endif
