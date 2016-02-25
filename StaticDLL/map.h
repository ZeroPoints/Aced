#ifndef MAP_H
#define MAP_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <vector>
#include "tile.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes



#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL{
	class Map
	{
		public:
			//Definitions. 
			//Map is the border of a MAP
			//Window Size/View point is dictated by the displayHeight_,displayWidth_ variables
			//Offset dictates how displaced the map is from the view point.

			STATICDLL_API Map();

			STATICDLL_API int GetMapWidth()
			{
				return width_;
			}
			STATICDLL_API int GetMapHeight()
			{
				return height_;
			}
			STATICDLL_API int GetPlayerStartX()
			{
				return playerStartX_;
			}
			STATICDLL_API int GetPlayerStartY()
			{
				return playerStartY_;
			}
			STATICDLL_API std::vector<std::vector<Tile>> &GetTiles()
			{
				return tiles_;
			}

			
			STATICDLL_API int GetMapYOffset()
			{
				return mapYoffset_;
			}
			STATICDLL_API int GetMapXOffset()
			{
				return mapXoffset_;
			}

			STATICDLL_API void SetMapYOffset(int mapYoffset);
			STATICDLL_API void SetMapXOffset(int mapXoffset);


			//Old values of the maps offset at the point the right click functionality was triggered to drag a map
			STATICDLL_API void SetOldMapYOffset(int mapYoffset){
				offSetBeforeRightClickDragY_ = mapYoffset;
			}
			//Old values of the maps offset at the point the right click functionality was triggered to drag a map
			STATICDLL_API void SetOldMapXOffset(int mapXoffset){
				offSetBeforeRightClickDragX_ = mapXoffset;
			}
			//Old values of the maps offset at the point the right click functionality was triggered to drag a map
			STATICDLL_API int GetOldMapXOffset()
			{
				return offSetBeforeRightClickDragX_;
			}
			//Old values of the maps offset at the point the right click functionality was triggered to drag a map
			STATICDLL_API int GetOldMapYOffset()
			{
				return offSetBeforeRightClickDragY_;
			}

			STATICDLL_API void SaveMap(ALLEGRO_DISPLAY *display);
			STATICDLL_API void LoadMap(ALLEGRO_DISPLAY *display);

			//This will Resize the map to the new size.
			STATICDLL_API void SetMapSize(int newmapheight,int newmapwidth);

			STATICDLL_API void DrawMap();

			//This Pre Calc function will calculate the drawing range for the maps boundaries. This should be run in update method
			STATICDLL_API void PreCalc();

			STATICDLL_API void SetDisplayHeight(int displayheight);
			STATICDLL_API void SetDisplayWidth(int displaywidth);


			STATICDLL_API void SetMapHeight(int newmapheight);
			STATICDLL_API void SetMapWidth(int newmapwidth);
			STATICDLL_API void SetPlayerStartX(int playerStartX);
			STATICDLL_API void SetPlayerStartY(int playerStartY);
			STATICDLL_API void CreateTiles(int newmapwidth, int newmapheight);

			STATICDLL_API void SetPlayerPlaced(bool playerplaced);
			STATICDLL_API bool GetPlayerPlaced()
			{
				return playerplaced_;
			}


		private:

			//Not used at the moment kinda. I want to use this to cap my drawing view to a box around screen size area. or so.
			int displayHeight_;
			//Not used at the moment kinda. I want to use this to cap my drawing view to a box around screen size area. or so.
			int displayWidth_;




			//The border of the entire Map
			int width_;
			//The border of the entire Map
			int height_;


			//This Contains the last size of the maps borders
			int oldMapWidth_;
			//This Contains the last size of the maps borders
			int oldMapHeight_;




			//This may or may not be used for displacing the mapps view point...maybe
			int mapXoffset_;
			//This may or may not be used for displacing the mapps view point...maybe
			int mapYoffset_;



			//Old values of the maps offset at the point the right click functionality was triggered to drag a map
			int offSetBeforeRightClickDragX_;
			//Old values of the maps offset at the point the right click functionality was triggered to drag a map
			int offSetBeforeRightClickDragY_;


			//These contain the view points of the maps printing range.
			int leftViewPoint_,
			//These contain the view points of the maps printing range.
			 rightViewPoint_,
			//These contain the view points of the maps printing range.
			 topViewPoint_,
			//These contain the view points of the maps printing range.
			 botViewPoint_;






			bool playerplaced_;
			int playerStartX_;//players starting position
			int playerStartY_;
			std::vector<std::vector<Tile>> tiles_;

			ALLEGRO_FONT *font30_;

	};
}
#endif
