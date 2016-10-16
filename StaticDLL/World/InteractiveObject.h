#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H



#define ALLEGRO_NO_MAGIC_MAIN


#include <allegro5\allegro.h>
#include <vector>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "../Static/Definitions.h"
#include "../ImageManagement/Image.h"
#include "../EditorOverLay/EditorItemBase.h"




#ifdef STATICDLL_EXPORTS
#define STATICDLL_API __declspec(dllexport)
#else
#define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL {

	class InteractiveObject
	{
	public:
		STATICDLL_API InteractiveObject();
		STATICDLL_API ~InteractiveObject();



		//-----------------------------------------------------------------------------------------------------

		//Gets

		STATICDLL_API Image *GetObjectImage();

		STATICDLL_API ALLEGRO_COLOR GetColor();
		STATICDLL_API EnumDLL::IMAGESETS GetImageSet();



		STATICDLL_API bool GetHasImage();
		STATICDLL_API bool GetHasImageReference();

		STATICDLL_API double GetImageReferenceX();
		STATICDLL_API double GetImageReferenceY();




		//-----------------------------------------------------------------------------------------------------

		//Sets



		STATICDLL_API void SetObjectProperties(
			EditorItemBase *selectedObject,
			bool isReference = false, int x = 0, int y = 0);

		STATICDLL_API void SetImage(
			Image *selectedImage,
			bool isReference = false, int x = 0, int y = 0);







		STATICDLL_API void SetImageSet(EnumDLL::IMAGESETS set);




		//-----------------------------------------------------------------------------------------------------

		//Draws



		//Draws the object...Uses the x and y offset from map to draw with displacement
		STATICDLL_API void DrawObject(double currentPositionX, double currentPositionY, int xOffset, int yOffset);




		//-----------------------------------------------------------------------------------------------------

		//MISC


		STATICDLL_API void RemoveAllProperties();
		STATICDLL_API void RemoveImage();


	private:
		double
			imageReferenceX_,
			imageReferenceY_
			;



		bool
			hasImage_,
			hasImageReference_
			;



		EnumDLL::IMAGESETS imageSet_;

		Image *image_;
	};


}
#endif