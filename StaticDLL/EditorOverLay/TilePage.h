#ifndef TILEPAGE_H
#define TILEPAGE_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <vector>
#include "EditorItemBase.h"
#include "../Config/Settings.h"
#include "../Static/Definitions.h"
#include "../ObjectBase.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes



#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL{
	//This Object Is a container for the tiles that are displayed in the overlay
	class TilePage
	{
		public:

			STATICDLL_API TilePage(Settings *settings){
				settings_ = settings;
				//fprintf(stderr,"An TilePage Created\n");
			}



			STATICDLL_API ~TilePage()
			{
				//fprintf(stderr,"An TilePage Destructed\n");
			}
			


			//Draws the tiles from reference. Uses set tiles as its range indicator
			STATICDLL_API void DrawItemBaseList(std::vector<std::vector<EditorItemBase>> &tileRef, bool showCollision);



			//Check This pages tiles for click intersects
			//Check each tile that is in range for click intersecting and returns the tile reference and the x and y value of that tile
			STATICDLL_API bool MouseActivity(std::vector<std::vector<EditorItemBase>> &tileRef, int mouseX, int mouseY);




			//give public access to the X
			STATICDLL_API int GetSelectedTileX()
			{
				return selectedTileX_;
			}


			//give public access to the Y
			STATICDLL_API int GetSelectedTileY()
			{
				return selectedTileY_;
			}


			//give public access to the tile reference
			STATICDLL_API EditorItemBase* GetSelectedItemBase()
			{
				return selectedItemBase_;
			}





			//Sets some variables for drawing range of tile page selection
			STATICDLL_API void SetTiles(int yRangeMin, int yRangeMax, int x)
			{
				yRangeMin_ = yRangeMin;
				yRangeMax_ = yRangeMax;
				x_ = x;
			}




		private:


			int yRangeMin_, yRangeMax_, x_;

			//Selected tile reference that the user has clicked on
			EditorItemBase* selectedItemBase_;
			//The X and Y indicator of that tile
			int selectedTileX_, selectedTileY_;

			Settings *settings_;
	};
}
#endif
