#ifndef EDITORITEMBASE_H
#define EDITORITEMBASE_H



#define ALLEGRO_NO_MAGIC_MAIN


#include <allegro5\allegro.h>
#include <vector>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "../Static/Definitions.h"
#include "../ImageManagement/ImageBundle.h"

#include <memory>


#ifdef ACEDSHAREDDLL_EXPORTS
#define ACEDSHAREDDLL_API __declspec(dllexport)
#else
#define ACEDSHAREDDLL_API __declspec(dllimport)
#endif



namespace AcedSharedDLL {

	//This object is a Tile
	//This inherits from Object base like most other objects
	class EditorItemBase
	{
	public:
		ACEDSHAREDDLL_API EditorItemBase();
		ACEDSHAREDDLL_API ~EditorItemBase();



		//-----------------------------------------------------------------------------------------------------

		//Gets

		ACEDSHAREDDLL_API TILETYPE GetTileType();

		ACEDSHAREDDLL_API double GetCurrentPositionY();
		ACEDSHAREDDLL_API double GetCurrentPositionX();
		ACEDSHAREDDLL_API double GetWidth();
		ACEDSHAREDDLL_API double GetHeight();
		ACEDSHAREDDLL_API std::shared_ptr<ImageBundle> &GetImageBundle();
		ACEDSHAREDDLL_API bool GetHasColor();
		ACEDSHAREDDLL_API bool GetHasImage();

		ACEDSHAREDDLL_API ALLEGRO_COLOR GetColor();

		ACEDSHAREDDLL_API AcedSharedDLL::IMAGESETS GetImageSet();



		ACEDSHAREDDLL_API bool GetHasImageOrReference();
		ACEDSHAREDDLL_API bool GetHasImageReference();

		ACEDSHAREDDLL_API double GetImageReferenceX();
		ACEDSHAREDDLL_API double GetImageReferenceY();




		//-----------------------------------------------------------------------------------------------------

		//Sets



		/*
		This sets a tile to an OBJECT image and if its an add shaped image it adds References to the other positions and passes in the X,Y position of the parent so it knows what IMAGE it relates to
		*/
		ACEDSHAREDDLL_API void SetItemBase(std::shared_ptr<EditorItemBase> &itemBase);
		ACEDSHAREDDLL_API void SetImageBundle(std::shared_ptr<ImageBundle> &imageBundle);
		ACEDSHAREDDLL_API void SetHasImageReference(bool reference);






		ACEDSHAREDDLL_API void SetTileType(TILETYPE tileType);

		//Set Collision Type
		ACEDSHAREDDLL_API void SetTileTypeProperties(std::shared_ptr<EditorItemBase> &selectedTile);

		ACEDSHAREDDLL_API void SetWidth(double x);

		ACEDSHAREDDLL_API void SetHeight(double y);




		ACEDSHAREDDLL_API void SetColor(ALLEGRO_COLOR color);
		ACEDSHAREDDLL_API void SetColorA(float a);
		ACEDSHAREDDLL_API void SetColorB(float b);
		ACEDSHAREDDLL_API void SetColorR(float r);
		ACEDSHAREDDLL_API void SetColorG(float g);
		ACEDSHAREDDLL_API void SetCurrentPosition(double x, double y);
		ACEDSHAREDDLL_API void SetCurrentPositionX(double x);
		ACEDSHAREDDLL_API void SetCurrentPositionY(double y);

		ACEDSHAREDDLL_API void SetImageSet(AcedSharedDLL::IMAGESETS set);

		ACEDSHAREDDLL_API void SetHasColor(bool hasColor);



		//-----------------------------------------------------------------------------------------------------

		//Draws

		//Draws the tiles collision properties
		//Inverts them if necassery
		ACEDSHAREDDLL_API void DrawObjectType(int xOffset, int yOffset, bool invert);


		//Draws the object...Uses the x and y offset from map to draw with displacement
		ACEDSHAREDDLL_API void DrawObject(int xOffset, int yOffset);




		//-----------------------------------------------------------------------------------------------------

		//MISC

		//Detects If click intersects with the object selected
		ACEDSHAREDDLL_API bool ClickIntersects(int mouseX, int mouseY);



		ACEDSHAREDDLL_API void RemoveAllProperties();


		//set flag and set image to null
		ACEDSHAREDDLL_API void RemoveImage();
		//set flag and set color to white
		ACEDSHAREDDLL_API void RemoveColor();


	private:
		double	currentPositionX_,
			currentPositionY_,
			width_,
			height_,
			imageReferenceX_,
			imageReferenceY_
			;



		bool	
			hasImage_,
			hasImageReference_,
			hasColor_;



		TILETYPE tileType_;

		AcedSharedDLL::IMAGESETS imageSet_;


		ALLEGRO_COLOR tileCollisionTypeColor_;



		std::shared_ptr<ImageBundle> imageBundle_;

		STATES Id_;
		ALLEGRO_COLOR chosenColor_;

	};


}
#endif