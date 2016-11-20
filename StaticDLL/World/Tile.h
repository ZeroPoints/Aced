#ifndef TILE_H
#define TILE_H



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



namespace StaticDLL{

	class Tile
	{
		public:
			STATICDLL_API Tile();
			STATICDLL_API ~Tile();



			//-----------------------------------------------------------------------------------------------------

			//Gets


			STATICDLL_API ImageBundle *GetImageBundle();
			STATICDLL_API bool GetHasColor();
			STATICDLL_API bool GetHasImage();
			STATICDLL_API ALLEGRO_COLOR GetColor();
			STATICDLL_API StaticDLL::IMAGESETS GetImageSet();




			//-----------------------------------------------------------------------------------------------------

			//Sets



			STATICDLL_API void SetTileBase(EditorItemBase *selectedTile);

			STATICDLL_API void SetImageBundle(ImageBundle *image);

			STATICDLL_API void SetColor(ALLEGRO_COLOR color);
			STATICDLL_API void SetColorR(float r);
			STATICDLL_API void SetColorG(float g);
			STATICDLL_API void SetColorB(float b);
			STATICDLL_API void SetColorA(float a);


			STATICDLL_API void SetImageSet(StaticDLL::IMAGESETS set);



			//-----------------------------------------------------------------------------------------------------

			//Draws


			//Draws the object...Uses the x and y offset from map to draw with displacement
			STATICDLL_API void DrawObject(double currentPositionX, double currentPositionY, int xOffset, int yOffset);




			//-----------------------------------------------------------------------------------------------------

			//MISC



			STATICDLL_API void RemoveAllProperties();
			STATICDLL_API void RemoveImage();
			STATICDLL_API void RemoveColor();
			

		private:	
			


			//Has color mmmm
			bool	
				hasImage_,
				hasColor_;

			StaticDLL::IMAGESETS imageSet_;

			ImageBundle *imageBundle_;

			ALLEGRO_COLOR chosenColor_;

	};


}
#endif