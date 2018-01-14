#ifndef TILEPAGE_H
#define TILEPAGE_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <vector>
#include "EditorItemBase.h"
#include "../Config/BaseSettings.h"
#include "../Static/Definitions.h"
#include "../Misc/ObjectBase.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes

#include <memory>

#ifdef ACEDSHAREDDLL_EXPORTS
   #define ACEDSHAREDDLL_API __declspec(dllexport)
#else
   #define ACEDSHAREDDLL_API __declspec(dllimport)
#endif


namespace AcedSharedDLL{
	//This Object Is a container for the tiles that are displayed in the overlay
	class TilePage
	{
		public:

			ACEDSHAREDDLL_API TilePage(std::shared_ptr<BaseSettings> &settings){
				settings_ = settings;
				//fprintf(stderr,"An TilePage Created\n");
			}



			ACEDSHAREDDLL_API ~TilePage()
			{
				//fprintf(stderr,"An TilePage Destructed\n");
			}
			


			//Draws the tiles from reference. Uses set tiles as its range indicator
			ACEDSHAREDDLL_API void DrawItemBaseList(std::vector<std::vector<std::shared_ptr<EditorItemBase>>> &tileRef, bool showCollision);



			//Check This pages tiles for click intersects
			//Check each tile that is in range for click intersecting and returns the tile reference and the x and y value of that tile
			ACEDSHAREDDLL_API bool MouseActivity(std::vector<std::vector<std::shared_ptr<EditorItemBase>>> &tileRef, int mouseX, int mouseY);




			//give public access to the X
			ACEDSHAREDDLL_API int GetSelectedTileX()
			{
				return selectedTileX_;
			}


			//give public access to the Y
			ACEDSHAREDDLL_API int GetSelectedTileY()
			{
				return selectedTileY_;
			}


			//give public access to the tile reference
			ACEDSHAREDDLL_API std::shared_ptr<EditorItemBase> &GetSelectedItemBase()
			{
				return selectedItemBase_;
			}





			//Sets some variables for drawing range of tile page selection
			ACEDSHAREDDLL_API void SetTiles(int yRangeMin, int yRangeMax, int x)
			{
				yRangeMin_ = yRangeMin;
				yRangeMax_ = yRangeMax;
				x_ = x;
			}




		private:


			int yRangeMin_, yRangeMax_, x_;

			//Selected tile reference that the user has clicked on
			std::shared_ptr<EditorItemBase> selectedItemBase_;
			//The X and Y indicator of that tile
			int selectedTileX_, selectedTileY_;

			std::shared_ptr<BaseSettings> settings_;
	};
}
#endif
