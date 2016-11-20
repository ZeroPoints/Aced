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


#ifdef STATICDLL_EXPORTS
#define STATICDLL_API __declspec(dllexport)
#else
#define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL {

	class ImageStateGroup
	{
	public:






		STATICDLL_API ImageStateGroup(int id);
		


		STATICDLL_API ~ImageStateGroup();








		//-----------------------------------------------------------------------------------------------------

		//Gets


		STATICDLL_API std::vector<Image*> GetImageDictionary();


		STATICDLL_API int GetId();




		//-----------------------------------------------------------------------------------------------------

		//Sets

		STATICDLL_API void SetImageDictionary(std::vector<Image*> imageDict);


		STATICDLL_API void SetId(int id);




	private:

		int id_;


		std::vector<Image*> imageDictionary_;

	};
}
#endif
