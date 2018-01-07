#ifndef ITEM_H
#define ITEM_H



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




#ifdef ACEDSHAREDDLL_EXPORTS
#define ACEDSHAREDDLL_API __declspec(dllexport)
#else
#define ACEDSHAREDDLL_API __declspec(dllimport)
#endif



namespace AcedSharedDLL {

	class Item
	{
	public:
		ACEDSHAREDDLL_API Item();
		ACEDSHAREDDLL_API ~Item();



		//-----------------------------------------------------------------------------------------------------

		//Gets

		ACEDSHAREDDLL_API ImageBundle *GetImageBundle();

		ACEDSHAREDDLL_API ALLEGRO_COLOR GetColor();
		ACEDSHAREDDLL_API AcedSharedDLL::IMAGESETS GetImageSet();



		ACEDSHAREDDLL_API bool GetHasImage();
		ACEDSHAREDDLL_API bool GetHasImageReference();

		ACEDSHAREDDLL_API double GetImageReferenceX();
		ACEDSHAREDDLL_API double GetImageReferenceY();



		ACEDSHAREDDLL_API double GetPosX();

		ACEDSHAREDDLL_API double GetPosY();
		ACEDSHAREDDLL_API ITEMTYPES GetItemType();
		ACEDSHAREDDLL_API OBJECTTYPES GetObjectType();




		//-----------------------------------------------------------------------------------------------------

		//Sets



		ACEDSHAREDDLL_API void SetObjectProperties(EditorItemBase *selectedObject);

		ACEDSHAREDDLL_API void SetImageBundle(ImageBundle *selectedImage);


		ACEDSHAREDDLL_API void SetHasImageReference(bool reference);





		ACEDSHAREDDLL_API void SetImageSet(AcedSharedDLL::IMAGESETS set);



		ACEDSHAREDDLL_API void SetPosX(double x);

		ACEDSHAREDDLL_API void SetPosY(double y);

		ACEDSHAREDDLL_API void SetItemType(ITEMTYPES set);
		ACEDSHAREDDLL_API void SetObjectType(OBJECTTYPES set);


		//-----------------------------------------------------------------------------------------------------

		//Draws



		//Draws the object...Uses the x and y offset from map to draw with displacement
		ACEDSHAREDDLL_API void DrawObject(int xOffset, int yOffset);




		//-----------------------------------------------------------------------------------------------------

		//MISC


		ACEDSHAREDDLL_API void RemoveAllProperties();
		ACEDSHAREDDLL_API void RemoveImage();


	private:
		double
			imageReferenceX_,
			imageReferenceY_,
			currentPositionX_,
			currentPositionY_
			;



		bool
			hasImage_,
			hasImageReference_
			;



		AcedSharedDLL::IMAGESETS imageSet_;
		ITEMTYPES itemType_;
		OBJECTTYPES objectType_;


		ImageBundle *imageBundle_;
	};


}
#endif