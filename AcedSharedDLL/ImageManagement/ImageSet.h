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
#include <memory>


#ifdef ACEDSHAREDDLL_EXPORTS
   #define ACEDSHAREDDLL_API __declspec(dllexport)
#else
   #define ACEDSHAREDDLL_API __declspec(dllimport)
#endif


namespace AcedSharedDLL{

	class ImageSet
	{
		public:
			ACEDSHAREDDLL_API ImageSet(std::vector<std::shared_ptr<ImageBundle>> &imageBundle, AcedSharedDLL::IMAGESETS id);
			ACEDSHAREDDLL_API ~ImageSet();



			//-----------------------------------------------------------------------------------------------------

			//Gets

			ACEDSHAREDDLL_API std::vector<std::shared_ptr<ImageBundle>> &GetImageBundleDictionary();

			ACEDSHAREDDLL_API AcedSharedDLL::IMAGESETS GetImageSetId();



			//-----------------------------------------------------------------------------------------------------

			//Sets


			ACEDSHAREDDLL_API void SetImageBundleDictionary(std::vector<std::shared_ptr<ImageBundle>> &imageBundleDictionary);

			ACEDSHAREDDLL_API void SetImageSetId(AcedSharedDLL::IMAGESETS id);






			
		private:

			AcedSharedDLL::IMAGESETS id_;

			std::vector<std::shared_ptr<ImageBundle>> imageBundleDictionary_;

	};
}
#endif
