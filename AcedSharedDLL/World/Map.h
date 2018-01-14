#ifndef MAP_H
#define MAP_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <vector>
#include "cell.h"
#include "../Config/BaseSettings.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "../../OpenSource/pugixml/pugixml.hpp"
#include "../Config/AssetLibrary.h"
#include "../LivingEntity/Character.h"
#include "Item.h"

#include <memory>


#ifdef ACEDSHAREDDLL_EXPORTS
   #define ACEDSHAREDDLL_API __declspec(dllexport)
#else
   #define ACEDSHAREDDLL_API __declspec(dllimport)
#endif




namespace AcedSharedDLL{

	class Map
	{
		public:

			ACEDSHAREDDLL_API Map(std::shared_ptr<BaseSettings> &settings, ALLEGRO_DISPLAY *display, std::shared_ptr<AssetLibrary> &assetLibrary);

			ACEDSHAREDDLL_API ~Map();

			//Make a destructor for map...???????????>>><>


			



			//-----------------------------------------------------------------------------------------------------

			//Gets

			

			ACEDSHAREDDLL_API bool GetPlayerPlaced();
			//This is in raw format hasnt been/Constants::TileSize()
			ACEDSHAREDDLL_API double GetMapYOffset();
			//This is in raw format hasnt been/Constants::TileSize()
			ACEDSHAREDDLL_API double GetMapXOffset();
			//Old values of the maps offset at the point the right click functionality was triggered to drag a map
			ACEDSHAREDDLL_API int GetOldMapXOffset();
			//Old values of the maps offset at the point the right click functionality was triggered to drag a map
			ACEDSHAREDDLL_API int GetOldMapYOffset();
			ACEDSHAREDDLL_API int GetMapWidth();
			ACEDSHAREDDLL_API int GetMapHeight();
			ACEDSHAREDDLL_API int GetPlayerStartX();
			ACEDSHAREDDLL_API int GetPlayerStartY();
			ACEDSHAREDDLL_API std::vector<std::vector<std::shared_ptr<Cell>>> &GetCellMap();
			//ACEDSHAREDDLL_API std::vector<ObjectBase> &GetObjects();
			ACEDSHAREDDLL_API double GetMapMoveXDelta();
			ACEDSHAREDDLL_API double GetMapMoveYDelta();

			ACEDSHAREDDLL_API std::vector<std::shared_ptr<Character>> &GetEnemyList();
			ACEDSHAREDDLL_API std::vector<std::shared_ptr<Item>> &GetItemList();




			//-----------------------------------------------------------------------------------------------------

			//Sets


			ACEDSHAREDDLL_API void SetMapSize(int newmapheight, int newmapwidth);
			ACEDSHAREDDLL_API void SetPlayerStartX(int playerStartX);
			ACEDSHAREDDLL_API void SetPlayerStartY(int playerStartY);
			ACEDSHAREDDLL_API void SetPlayerPlaced(bool playerplaced);
			ACEDSHAREDDLL_API void SetMapHeight(int newmapheight);
			ACEDSHAREDDLL_API void SetMapWidth(int newmapwidth);
			ACEDSHAREDDLL_API void SetMapYOffset(double mapYoffset);
			ACEDSHAREDDLL_API void SetMapXOffset(double mapXoffset);
			//Old values of the maps offset at the point the right click functionality was triggered to drag a map
			ACEDSHAREDDLL_API void SetOldMapYOffset(int mapYoffset);
			//Old values of the maps offset at the point the right click functionality was triggered to drag a map
			ACEDSHAREDDLL_API void SetOldMapXOffset(int mapXoffset);
			ACEDSHAREDDLL_API void SetMapMoveXDelta(double val);
			ACEDSHAREDDLL_API void SetMapMoveYDelta(double val);




			//-----------------------------------------------------------------------------------------------------

			//Draws

			ACEDSHAREDDLL_API void DrawMap();






			//-----------------------------------------------------------------------------------------------------

			//Misc


			//This Pre Calc function will calculate the drawing range for the maps boundaries. This should be run in update method
			ACEDSHAREDDLL_API void Update();
			ACEDSHAREDDLL_API void CreateCellMap(int newmapwidth, int newmapheight);
			//Save dialog window for saving a map
			ACEDSHAREDDLL_API void SaveMapDialog();
			//Save function for saving the map in xml
			ACEDSHAREDDLL_API bool SaveMap();
			ACEDSHAREDDLL_API void LoadMapDialog(bool gamestart);
			ACEDSHAREDDLL_API void LoadMap(bool gamestart);
			ACEDSHAREDDLL_API void ResetMap();

			
			ACEDSHAREDDLL_API void RemoveEnemyFromMap(int tileXPos, int tileYPos);
			ACEDSHAREDDLL_API void RemoveItemFromMap(int tileXPos, int tileYPos);

			ACEDSHAREDDLL_API void AddEnemyToMap(std::shared_ptr<EditorItemBase> &item, int tileXPos, int tileYPos);
			ACEDSHAREDDLL_API void AddItemToMap(std::shared_ptr<EditorItemBase> &item, int tileXPos, int tileYPos);

			ACEDSHAREDDLL_API bool EnemyAlreadyExistsAtXY(int tileXPos, int tileYPos);
			ACEDSHAREDDLL_API bool ItemAlreadyExistsAtXY(int tileXPos, int tileYPos);
			ACEDSHAREDDLL_API bool ItemCollisionCheckAtXYExists(double playerX, double playerY, double width, double height);
			ACEDSHAREDDLL_API std::shared_ptr<Item> ItemCollisionCheckAtXY(double playerX, double playerY, double width, double height);


			//-----------------------------------------------------------------------------------------------------

			//Testing

			
			//ACEDSHAREDDLL_API void AddObjectToMap(ObjectBase obj);

		


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


			std::vector<std::vector<std::shared_ptr<Cell>>> cellMap_;
			std::vector<std::shared_ptr<Character>> enemyList_;
			std::vector<std::shared_ptr<Item>> itemList_;


			//std::vector<ObjectBase> objects_;



			std::shared_ptr<AssetLibrary> assetLibrary_;
			std::shared_ptr<BaseSettings> settings_;
			ALLEGRO_DISPLAY *display_;
	};
}
#endif
