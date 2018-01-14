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


#ifdef ACEDSHAREDDLL_EXPORTS
#define ACEDSHAREDDLL_API __declspec(dllexport)
#else
#define ACEDSHAREDDLL_API __declspec(dllimport)
#endif



namespace AcedSharedDLL {

	class ImageBundle
	{
	public:






		ACEDSHAREDDLL_API ImageBundle(int id);



		ACEDSHAREDDLL_API ~ImageBundle();








		//-----------------------------------------------------------------------------------------------------

		//Gets


		ACEDSHAREDDLL_API std::vector<std::shared_ptr<ImageStateGroup>> &GetImageStateGroupDictionary();


		ACEDSHAREDDLL_API int GetId();


		ACEDSHAREDDLL_API ITEMTYPES GetItemType();
		ACEDSHAREDDLL_API OBJECTTYPES GetObjectType();




		//-----------------------------------------------------------------------------------------------------

		//Sets

		ACEDSHAREDDLL_API void SetImageStateGroupDictionary(std::vector<std::shared_ptr<ImageStateGroup>> &imageStateGroupDict);

		ACEDSHAREDDLL_API void SetId(int id);



		ACEDSHAREDDLL_API void SetItemType(ITEMTYPES set);
		ACEDSHAREDDLL_API void SetObjectType(OBJECTTYPES set);





	private:

		int id_;


		std::vector<std::shared_ptr<ImageStateGroup>> imageStateGroupDictionary_;


		ITEMTYPES itemType_;
		OBJECTTYPES objectType_;



	};
}
#endif
