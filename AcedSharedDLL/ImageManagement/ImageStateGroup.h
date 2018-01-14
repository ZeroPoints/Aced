#ifndef IMAGESTATEGROUP_H
#define IMAGESTATEGROUP_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <vector>
#include "../Static/Definitions.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include <allegro5\allegro_image.h>//images
#include "Image.h"
#include <memory>

#ifdef ACEDSHAREDDLL_EXPORTS
#define ACEDSHAREDDLL_API __declspec(dllexport)
#else
#define ACEDSHAREDDLL_API __declspec(dllimport)
#endif



namespace AcedSharedDLL {

	class ImageStateGroup
	{
	public:






		ACEDSHAREDDLL_API ImageStateGroup(int id);
		


		ACEDSHAREDDLL_API ~ImageStateGroup();








		//-----------------------------------------------------------------------------------------------------

		//Gets


		ACEDSHAREDDLL_API std::vector<std::shared_ptr<Image>> &GetImageDictionary();


		ACEDSHAREDDLL_API int GetId();




		//-----------------------------------------------------------------------------------------------------

		//Sets

		ACEDSHAREDDLL_API void SetImageDictionary(std::vector<std::shared_ptr<Image>> &imageDict);


		ACEDSHAREDDLL_API void SetId(int id);




	private:

		int id_;


		std::vector<std::shared_ptr<Image>> imageDictionary_;

	};
}
#endif
