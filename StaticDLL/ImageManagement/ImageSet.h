#ifndef IMAGESET_H
#define IMAGESET_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <vector>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "Image.h"
#include "../Static/Definitions.h"



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
			STATICDLL_API ~ImageSet();

			STATICDLL_API std::vector<Image*> GetImageDictionary();

			STATICDLL_API EnumDLL::IMAGESETS GetImageSetId();


			
		private:

			EnumDLL::IMAGESETS id_;

			std::vector<Image*> imageDictionary_;

	};
}
#endif
