#ifndef IMAGESET_H
#define IMAGESET_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <vector>
#include "tile.h"
#include "Settings.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "../OpenSource/pugixml/pugixml.hpp"
#include "Image.h"



#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL{

	class ImageSet
	{
		public:
			STATICDLL_API ImageSet(std::vector<Image*> images, EnumDLL::IMAGESETS id);


			STATICDLL_API std::vector<Image*> GetImageDictionary()
			{
				return imageDictionary_;
			}

			STATICDLL_API EnumDLL::IMAGESETS GetImageSetId()
			{
				return id_;
			}

			//Make a destructor for map...???????????>>><>

			
		private:

			EnumDLL::IMAGESETS id_;

			std::vector<Image*> imageDictionary_;

	};
}
#endif
