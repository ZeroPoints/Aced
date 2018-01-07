#ifndef IMAGELOADER_H
#define IMAGELOADER_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <vector>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "../../OpenSource/pugixml/pugixml.hpp"
#include "ImageSet.h"



#ifdef ACEDSHAREDDLL_EXPORTS
   #define ACEDSHAREDDLL_API __declspec(dllexport)
#else
   #define ACEDSHAREDDLL_API __declspec(dllimport)
#endif


namespace AcedSharedDLL{

	class ImageLoader
	{
		public:
			ACEDSHAREDDLL_API ImageLoader();

			




			//-----------------------------------------------------------------------------------------------------

			//Gets


			ACEDSHAREDDLL_API std::vector<ImageSet*> GetImageSetDictionary();





			//-----------------------------------------------------------------------------------------------------

			//Misc

			ACEDSHAREDDLL_API void LoadTiles();
			ACEDSHAREDDLL_API void LoadPlayers();
			ACEDSHAREDDLL_API void LoadInteractiveObjects();
			ACEDSHAREDDLL_API void LoadColors();
			ACEDSHAREDDLL_API void LoadSystemImages();
			ACEDSHAREDDLL_API void LoadObjectImages();
			ACEDSHAREDDLL_API void LoadEnemyImages();
			ACEDSHAREDDLL_API void LoadItemImages();

			


			
		private:

			std::vector<ImageSet*> imageDictionary_;

	};
}
#endif
