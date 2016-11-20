#ifndef IMAGEBUNDLE_H
#define IMAGEBUNDLE_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <vector>
#include "../Static/Definitions.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include <allegro5\allegro_image.h>//images
#include "ImageStateGroup.h"


#ifdef STATICDLL_EXPORTS
#define STATICDLL_API __declspec(dllexport)
#else
#define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL {

	class ImageBundle
	{
	public:






		STATICDLL_API ImageBundle(int id);



		STATICDLL_API ~ImageBundle();








		//-----------------------------------------------------------------------------------------------------

		//Gets


		STATICDLL_API std::vector<ImageStateGroup*> GetImageStateGroupDictionary();


		STATICDLL_API int GetId();


		STATICDLL_API ITEMTYPES GetItemType();
		STATICDLL_API OBJECTTYPES GetObjectType();




		//-----------------------------------------------------------------------------------------------------

		//Sets

		STATICDLL_API void SetImageStateGroupDictionary(std::vector<ImageStateGroup*> imageStateGroupDict);

		STATICDLL_API void SetId(int id);



		STATICDLL_API void SetItemType(ITEMTYPES set);
		STATICDLL_API void SetObjectType(OBJECTTYPES set);





	private:

		int id_;


		std::vector<ImageStateGroup*> imageStateGroupDictionary_;


		ITEMTYPES itemType_;
		OBJECTTYPES objectType_;



	};
}
#endif
