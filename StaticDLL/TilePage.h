#ifndef TILEPAGE_H
#define TILEPAGE_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <vector>
#include "tile.h"
#include "Settings.h"
#include "Definitions.h"
#include "ObjectBase.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes



#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL{
	class TilePage
	{
		public:

			STATICDLL_API TilePage(){
				fprintf(stderr,"An TilePage Created\n");
			}



			STATICDLL_API ~TilePage()
			{
				fprintf(stderr,"An TilePage Destructed\n");
			}
			


			//Draws the tiles from reference. Uses set tiles as its range indicator
			STATICDLL_API void DrawTiles(std::vector<std::vector<Tile>> &tileRef);




			//Sets some variables for drawing range of tile page selection
			STATICDLL_API void SetTiles(int yRangeMin, int yRangeMax, int x)
			{
				yRangeMin_ = yRangeMin;
				yRangeMax_ = yRangeMax;
				x_ = x;
			}




		private:


			int yRangeMin_, yRangeMax_, x_;


	};
}
#endif
