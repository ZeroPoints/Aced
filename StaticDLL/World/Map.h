#ifndef MAP_H
#define MAP_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <vector>
#include "cell.h"
#include "../Config/Settings.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "../../OpenSource/pugixml/pugixml.hpp"
#include "../Config/AssetLibrary.h"
#include "../LivingEntity/Character.h"
#include "Item.h"




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
			STATICDLL_API Map(Settings *settings, ALLEGRO_DISPLAY *display, AssetLibrary *assetLibrary);

			STATICDLL_API ~Map();

			//Make a destructor for map...???????????>>><>


			



			//-----------------------------------------------------------------------------------------------------

			//Gets

			

			STATICDLL_API bool GetPlayerPlaced();
			//This is in raw format hasnt been/Constants::TileSize()
			STATICDLL_API double GetMapYOffset();
			//This is in raw format hasnt been/Constants::TileSize()
			STATICDLL_API double GetMapXOffset();
			//Old values of the maps offset at the point the right click functionality was triggered to drag a map
			STATICDLL_API int GetOldMapXOffset();
			//Old values of the maps offset at the point the right click functionality was triggered to drag a map
			STATICDLL_API int GetOldMapYOffset();
			STATICDLL_API int GetMapWidth();
			STATICDLL_API int GetMapHeight();
			STATICDLL_API int GetPlayerStartX();
			STATICDLL_API int GetPlayerStartY();
			STATICDLL_API std::vector<std::vector<Cell>> &GetCellMap();
			//STATICDLL_API std::vector<ObjectBase> &GetObjects();
			STATICDLL_API double GetMapMoveXDelta();
			STATICDLL_API double GetMapMoveYDelta();

			STATICDLL_API std::vector<Character*> &GetEnemyList();
			STATICDLL_API std::vector<Item*> &GetItemList();




			//-----------------------------------------------------------------------------------------------------

			//Sets


			STATICDLL_API void SetMapSize(int newmapheight, int newmapwidth);
			STATICDLL_API void SetPlayerStartX(int playerStartX);
			STATICDLL_API void SetPlayerStartY(int playerStartY);
			STATICDLL_API void SetPlayerPlaced(bool playerplaced);
			STATICDLL_API void SetMapHeight(int newmapheight);
			STATICDLL_API void SetMapWidth(int newmapwidth);
			STATICDLL_API void SetMapYOffset(double mapYoffset);
			STATICDLL_API void SetMapXOffset(double mapXoffset);
			//Old values of the maps offset at the point the right click functionality was triggered to drag a map
			STATICDLL_API void SetOldMapYOffset(int mapYoffset);
			//Old values of the maps offset at the point the right click functionality was triggered to drag a map
			STATICDLL_API void SetOldMapXOffset(int mapXoffset);
			STATICDLL_API void SetMapMoveXDelta(double val);
			STATICDLL_API void SetMapMoveYDelta(double val);




			//-----------------------------------------------------------------------------------------------------

			//Draws

			STATICDLL_API void DrawMap();






			//-----------------------------------------------------------------------------------------------------

			//Misc


			//This Pre Calc function will calculate the drawing range for the maps boundaries. This should be run in update method
			STATICDLL_API void Update();
			STATICDLL_API void CreateCellMap(int newmapwidth, int newmapheight);
			//Save dialog window for saving a map
			STATICDLL_API void SaveMapDialog();
			//Save function for saving the map in xml
			STATICDLL_API bool SaveMap();
			STATICDLL_API void LoadMapDialog(bool gamestart);
			STATICDLL_API void LoadMap(bool gamestart);
			STATICDLL_API void ResetMap();

			
			STATICDLL_API void RemoveEnemyFromMap(int tileXPos, int tileYPos);
			STATICDLL_API void RemoveItemFromMap(int tileXPos, int tileYPos);

			STATICDLL_API void AddEnemyToMap(EditorItemBase *item, int tileXPos, int tileYPos);
			STATICDLL_API void AddItemToMap(EditorItemBase *item, int tileXPos, int tileYPos);

			STATICDLL_API bool EnemyAlreadyExistsAtXY(int tileXPos, int tileYPos);
			STATICDLL_API bool ItemAlreadyExistsAtXY(int tileXPos, int tileYPos);
			STATICDLL_API Item* ItemCollisionCheckAtXY(double playerX, double playerY, double width, double height);
			

			//-----------------------------------------------------------------------------------------------------

			//Testing

			
			//STATICDLL_API void AddObjectToMap(ObjectBase obj);

		


		private:


			//The border of the entire Map
			int width_;
			//The border of the entire Map
			int height_;


			//This Contains the last size of the maps borders
			int oldMapWidth_;
			//This Contains the last size of the maps borders
			int oldMapHeight_;



			double mapMoveXDelta_;
			double mapMoveYDelta_;


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


			std::vector<std::vector<Cell>> cellMap_;
			std::vector<Character*> enemyList_;
			std::vector<Item*> itemList_;


			//std::vector<ObjectBase> objects_;




			ALLEGRO_FONT *font30_;
			AssetLibrary *assetLibrary_;
			Settings *settings_;
			ALLEGRO_DISPLAY *display_;
	};
}
#endif
