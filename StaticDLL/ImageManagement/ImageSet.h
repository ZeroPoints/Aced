#ifndef IMAGESET_H
#define IMAGESET_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <vector>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "ImageBundle.h"
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
			STATICDLL_API ImageSet(std::vector<ImageBundle*> imageBundle, StaticDLL::IMAGESETS id);
			STATICDLL_API ~ImageSet();



			//-----------------------------------------------------------------------------------------------------

			//Gets

			STATICDLL_API std::vector<ImageBundle*> GetImageBundleDictionary();

			STATICDLL_API StaticDLL::IMAGESETS GetImageSetId();



			//-----------------------------------------------------------------------------------------------------

			//Sets


			STATICDLL_API void SetImageBundleDictionary(std::vector<ImageBundle*> imageBundleDictionary);

			STATICDLL_API void SetImageSetId(StaticDLL::IMAGESETS id);






			
		private:

			StaticDLL::IMAGESETS id_;

			std::vector<ImageBundle*> imageBundleDictionary_;

	};
}
#endif
