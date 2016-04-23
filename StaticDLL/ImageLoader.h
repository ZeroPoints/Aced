#ifndef IMAGELOADER_H
#define IMAGELOADER_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <vector>
#include "tile.h"
#include "Settings.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "../OpenSource/pugixml/pugixml.hpp"
#include "ImageSet.h"



#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL{

	class ImageLoader
	{
		public:
			STATICDLL_API ImageLoader();

			STATICDLL_API void LoadTiles();
			STATICDLL_API void LoadPlayers();
			STATICDLL_API void LoadInteractiveObjects();
			STATICDLL_API void LoadColors();
			STATICDLL_API void LoadSystemImages();


			STATICDLL_API std::vector<ImageSet*> GetImageSetDictionary()
			{
				return imageDictionary_;
			}



			//Make a destructor for map...???????????>>><>

			
		private:

			std::vector<ImageSet*> imageDictionary_;

	};
}
#endif
