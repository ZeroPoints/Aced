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




#ifdef STATICDLL_EXPORTS
#define STATICDLL_API __declspec(dllexport)
#else
#define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL {

	//This object is a Tile
	//This inherits from Object base like most other objects
	class EditorItemBase
	{
	public:
		STATICDLL_API EditorItemBase();
		STATICDLL_API ~EditorItemBase();



		//-----------------------------------------------------------------------------------------------------

		//Gets

		STATICDLL_API TILETYPE GetTileType();

		STATICDLL_API double GetCurrentPositionY();
		STATICDLL_API double GetCurrentPositionX();
		STATICDLL_API double GetWidth();
		STATICDLL_API double GetHeight();
		STATICDLL_API ImageBundle *GetImageBundle();
		STATICDLL_API bool GetHasColor();
		STATICDLL_API bool GetHasImage();

		STATICDLL_API ALLEGRO_COLOR GetColor();

		STATICDLL_API StaticDLL::IMAGESETS GetImageSet();



		STATICDLL_API bool GetHasImageOrReference();
		STATICDLL_API bool GetHasImageReference();

		STATICDLL_API double GetImageReferenceX();
		STATICDLL_API double GetImageReferenceY();




		//-----------------------------------------------------------------------------------------------------

		//Sets



		/*
		This sets a tile to an OBJECT image and if its an add shaped image it adds References to the other positions and passes in the X,Y position of the parent so it knows what IMAGE it relates to
		*/
		STATICDLL_API void SetItemBase(EditorItemBase *itemBase);
		STATICDLL_API void SetImageBundle(ImageBundle *imageBundle);
		STATICDLL_API void SetHasImageReference(bool reference);






		STATICDLL_API void SetTileType(TILETYPE tileType);

		//Set Collision Type
		STATICDLL_API void SetTileTypeProperties(EditorItemBase *selectedTile);

		STATICDLL_API void SetWidth(double x);

		STATICDLL_API void SetHeight(double y);




		STATICDLL_API void SetColor(ALLEGRO_COLOR color);
		STATICDLL_API void SetColorA(float a);
		STATICDLL_API void SetColorB(float b);
		STATICDLL_API void SetColorR(float r);
		STATICDLL_API void SetColorG(float g);
		STATICDLL_API void SetCurrentPosition(double x, double y);
		STATICDLL_API void SetCurrentPositionX(double x);
		STATICDLL_API void SetCurrentPositionY(double y);

		STATICDLL_API void SetImageSet(StaticDLL::IMAGESETS set);

		STATICDLL_API void SetHasColor(bool hasColor);



		//-----------------------------------------------------------------------------------------------------

		//Draws

		//Draws the tiles collision properties
		//Inverts them if necassery
		STATICDLL_API void DrawObjectType(int xOffset, int yOffset, bool invert);


		//Draws the object...Uses the x and y offset from map to draw with displacement
		STATICDLL_API void DrawObject(int xOffset, int yOffset);




		//-----------------------------------------------------------------------------------------------------

		//MISC

		//Detects If click intersects with the object selected
		STATICDLL_API bool ClickIntersects(int mouseX, int mouseY);



		STATICDLL_API void RemoveAllProperties();


		//set flag and set image to null
		STATICDLL_API void RemoveImage();
		//set flag and set color to white
		STATICDLL_API void RemoveColor();


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

		StaticDLL::IMAGESETS imageSet_;


		ALLEGRO_COLOR tileCollisionTypeColor_;



		ImageBundle *imageBundle_;

		STATES Id_;
		ALLEGRO_COLOR chosenColor_;

	};


}
#endif