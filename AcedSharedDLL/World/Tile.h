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

#include <memory>


#ifdef ACEDSHAREDDLL_EXPORTS
   #define ACEDSHAREDDLL_API __declspec(dllexport)
#else
   #define ACEDSHAREDDLL_API __declspec(dllimport)
#endif



namespace AcedSharedDLL{

	class Tile
	{
		public:
			ACEDSHAREDDLL_API Tile();
			ACEDSHAREDDLL_API ~Tile();



			//-----------------------------------------------------------------------------------------------------

			//Gets


			ACEDSHAREDDLL_API std::shared_ptr<ImageBundle> &GetImageBundle();
			ACEDSHAREDDLL_API bool GetHasColor();
			ACEDSHAREDDLL_API bool GetHasImage();
			ACEDSHAREDDLL_API ALLEGRO_COLOR GetColor();
			ACEDSHAREDDLL_API AcedSharedDLL::IMAGESETS GetImageSet();




			//-----------------------------------------------------------------------------------------------------

			//Sets



			ACEDSHAREDDLL_API void SetTileBase(std::shared_ptr<EditorItemBase> &selectedTile);

			ACEDSHAREDDLL_API void SetImageBundle(std::shared_ptr<ImageBundle> &image);

			ACEDSHAREDDLL_API void SetColor(ALLEGRO_COLOR color);
			ACEDSHAREDDLL_API void SetColorR(float r);
			ACEDSHAREDDLL_API void SetColorG(float g);
			ACEDSHAREDDLL_API void SetColorB(float b);
			ACEDSHAREDDLL_API void SetColorA(float a);


			ACEDSHAREDDLL_API void SetImageSet(AcedSharedDLL::IMAGESETS set);



			//-----------------------------------------------------------------------------------------------------

			//Draws


			//Draws the object...Uses the x and y offset from map to draw with displacement
			ACEDSHAREDDLL_API void DrawObject(double currentPositionX, double currentPositionY, int xOffset, int yOffset);




			//-----------------------------------------------------------------------------------------------------

			//MISC



			ACEDSHAREDDLL_API void RemoveAllProperties();
			ACEDSHAREDDLL_API void RemoveImage();
			ACEDSHAREDDLL_API void RemoveColor();
			

		private:	
			


			//Has color mmmm
			bool	
				hasImage_,
				hasColor_;

			AcedSharedDLL::IMAGESETS imageSet_;

			std::shared_ptr<ImageBundle> imageBundle_;

			ALLEGRO_COLOR chosenColor_;

	};


}
#endif