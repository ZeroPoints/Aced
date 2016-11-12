#ifndef CELL_H
#define CELL_H



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
#include "Tile.h"
#include "InteractiveObject.h"
//#include "CharacterSpawn.h"
//#include "../LivingEntity/Player.h"
//#include "../LivingEntity/Character.h"




#ifdef STATICDLL_EXPORTS
#define STATICDLL_API __declspec(dllexport)
#else
#define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL {

	class Cell
	{
		public:
			STATICDLL_API Cell();
			STATICDLL_API ~Cell();





			//-----------------------------------------------------------------------------------------------------

			//Sets

			//layers setters
			STATICDLL_API void SetTile(Tile* tile);
			STATICDLL_API void SetTileType(TILETYPE tileType);
			STATICDLL_API void SetTileTypeProperties(EditorItemBase *selectedTile);






			STATICDLL_API void SetWidth(double x);
			STATICDLL_API void SetHeight(double y);

			
			STATICDLL_API void SetCurrentPosition(double x, double y);
			STATICDLL_API void SetCurrentPositionX(double x);
			STATICDLL_API void SetCurrentPositionY(double y);


			STATICDLL_API void SetInteractiveObject(InteractiveObject* interactiveObject, bool isReference);



			//-----------------------------------------------------------------------------------------------------

			//Gets



			STATICDLL_API TILETYPE GetTileType();


			STATICDLL_API double GetCurrentPositionY();
			STATICDLL_API double GetCurrentPositionX();


			STATICDLL_API double GetWidth();
			STATICDLL_API double GetHeight();



			STATICDLL_API Tile* GetTile();
			STATICDLL_API InteractiveObject* GetInteractiveObject();


			STATICDLL_API bool GetHasTile();
			STATICDLL_API bool GetHasInteractiveObject();
			STATICDLL_API bool GetHasInteractiveObjectReference();


			

			//-----------------------------------------------------------------------------------------------------

			//Draws


			STATICDLL_API void Draw(int xoffset, int yoffset, bool invertCollision = false);


			//Draws the tiles collision properties
			//Inverts them if necassery
			STATICDLL_API void DrawObjectType(int xOffset, int yOffset, bool invert);




			//-----------------------------------------------------------------------------------------------------

			//MISC


			//Detects If click intersects with the object selected
			STATICDLL_API bool ClickIntersects(int mouseX, int mouseY);
			

			
			STATICDLL_API void RemoveAllProperties();
			STATICDLL_API void RemoveColor();
			STATICDLL_API void RemoveImage();



			STATICDLL_API void DeleteTile();
			STATICDLL_API void DeleteInteractiveObject();





		private:
			Tile* tile_;

			InteractiveObject* interactiveObject_;







			double	x_,
				y_
				;


			bool 
				hasTile_,
				hasInteractiveObject_,
				hasInteractiveObjectReference_,
				clickable_
				;



			TILETYPE tileType_;



			ALLEGRO_COLOR tileCollisionTypeColor_;


	};


}
#endif