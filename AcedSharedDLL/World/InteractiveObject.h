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
#include "../ImageManagement/ImageBundle.h"
#include "../EditorOverLay/EditorItemBase.h"
#include "../World/Item.h"




#ifdef ACEDSHAREDDLL_EXPORTS
#define ACEDSHAREDDLL_API __declspec(dllexport)
#else
#define ACEDSHAREDDLL_API __declspec(dllimport)
#endif



namespace AcedSharedDLL {

	class InteractiveObject
	{
	public:
		ACEDSHAREDDLL_API InteractiveObject();
		ACEDSHAREDDLL_API ~InteractiveObject();



		//-----------------------------------------------------------------------------------------------------

		//Gets

		ACEDSHAREDDLL_API ImageBundle *GetImageBundle();

		ACEDSHAREDDLL_API ALLEGRO_COLOR GetColor();
		ACEDSHAREDDLL_API AcedSharedDLL::IMAGESETS GetImageSet();



		ACEDSHAREDDLL_API bool GetHasImage();
		ACEDSHAREDDLL_API bool GetHasImageReference();

		ACEDSHAREDDLL_API double GetImageReferenceX();
		ACEDSHAREDDLL_API double GetImageReferenceY();

		ACEDSHAREDDLL_API OBJECTTYPES GetObjectType();
		ACEDSHAREDDLL_API ITEMTYPES GetItemType();






		//-----------------------------------------------------------------------------------------------------

		//Sets



		ACEDSHAREDDLL_API void SetItemBase(EditorItemBase *selectedObject);



		ACEDSHAREDDLL_API void SetImageBundle(ImageBundle *selectedImage);



		ACEDSHAREDDLL_API void SetImageReferenceX(double x);
		ACEDSHAREDDLL_API void SetImageReferenceY(double y);

		ACEDSHAREDDLL_API void SetHasImageReference(bool reference);



		ACEDSHAREDDLL_API void SetImageSet(AcedSharedDLL::IMAGESETS set);

		ACEDSHAREDDLL_API void SetObjectType(OBJECTTYPES set);
		ACEDSHAREDDLL_API void SetItemType(ITEMTYPES set);




		//-----------------------------------------------------------------------------------------------------

		//Draws



		//Draws the object...Uses the x and y offset from map to draw with displacement
		ACEDSHAREDDLL_API void DrawObject(double currentPositionX, double currentPositionY, int xOffset, int yOffset);




		//-----------------------------------------------------------------------------------------------------

		//MISC


		ACEDSHAREDDLL_API void RemoveAllProperties();
		ACEDSHAREDDLL_API void RemoveImage();
		//returns false  if interaction user can walk over object
		ACEDSHAREDDLL_API bool CollisionInteraction(std::vector<Item*> &itemList);


	private:
		double
			imageReferenceX_,
			imageReferenceY_
			;



		bool
			hasImage_,
			hasImageReference_
			;



		AcedSharedDLL::IMAGESETS imageSet_;
		OBJECTTYPES objectType_;
		ITEMTYPES itemType_;


		ImageBundle *imageBundle_;
	};


}
#endif