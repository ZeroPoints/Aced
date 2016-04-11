#ifndef MAP_H
#define MAP_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <vector>
#include "tile.h"
#include "Settings.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "../OpenSource/pugixml/pugixml.hpp"



#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL{

	//This class Contains the maps dimensions are properties. 
	//Contains the main list of tiles object that most things will reference
	class Map
	{
		public:
			//Definitions. 
			//Map is the border of a MAP
			//Window Size/View point is dictated by the displayHeight_,displayWidth_ variables that are in the Settings for display resolution
			//Offset dictates how displaced the map is from the view point.
			STATICDLL_API Map(Settings *settings, ALLEGRO_DISPLAY *display);


			//Make a destructor for map...???????????>>><>

			STATICDLL_API void ResetMap();

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

			
			//This is in raw format hasnt been/Constants::TileSize
			STATICDLL_API double GetMapYOffset()
			{
				return mapYoffset_;
			}
			//This is in raw format hasnt been/Constants::TileSize
			STATICDLL_API double GetMapXOffset()
			{
				return mapXoffset_;
			}

			STATICDLL_API void SetMapYOffset(double mapYoffset);
			STATICDLL_API void SetMapXOffset(double mapXoffset);


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


			//Save dialog window for saving a map
			STATICDLL_API void SaveMapDialog();
			//Save function for saving the map in xml
			STATICDLL_API bool SaveMap();
			STATICDLL_API void LoadMapDialog();
			STATICDLL_API void LoadMap();
			


			//Old style call
			STATICDLL_API void SaveMap(ALLEGRO_DISPLAY *display);
			//Old style call
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


			//The border of the entire Map
			int width_;
			//The border of the entire Map
			int height_;


			//This Contains the last size of the maps borders
			int oldMapWidth_;
			//This Contains the last size of the maps borders
			int oldMapHeight_;




			//This may or may not be used for displacing the mapps view point...maybe
			double mapXoffset_;
			//This may or may not be used for displacing the mapps view point...maybe
			double mapYoffset_;



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


			ALLEGRO_PATH *mapPath_;



			bool playerplaced_;
			int playerStartX_;//players starting position
			int playerStartY_;
			std::vector<std::vector<Tile>> tiles_;

			ALLEGRO_FONT *font30_;
			Settings *settings_;
			ALLEGRO_DISPLAY *display_;
	};
}
#endif
