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




#ifdef ACEDSHAREDDLL_EXPORTS
#define ACEDSHAREDDLL_API __declspec(dllexport)
#else
#define ACEDSHAREDDLL_API __declspec(dllimport)
#endif



namespace AcedSharedDLL {

	class Cell
	{
		public:
			ACEDSHAREDDLL_API Cell();
			ACEDSHAREDDLL_API ~Cell();





			//-----------------------------------------------------------------------------------------------------

			//Sets

			//layers setters
			ACEDSHAREDDLL_API void SetTile(Tile* tile);
			ACEDSHAREDDLL_API void SetTileType(TILETYPE tileType);
			ACEDSHAREDDLL_API void SetTileTypeProperties(EditorItemBase *selectedTile);






			ACEDSHAREDDLL_API void SetWidth(double x);
			ACEDSHAREDDLL_API void SetHeight(double y);

			
			ACEDSHAREDDLL_API void SetCurrentPosition(double x, double y);
			ACEDSHAREDDLL_API void SetCurrentPositionX(double x);
			ACEDSHAREDDLL_API void SetCurrentPositionY(double y);


			ACEDSHAREDDLL_API void SetInteractiveObject(InteractiveObject* interactiveObject);
			ACEDSHAREDDLL_API void SetInteractiveObjectReference(bool isReference);

			


			//-----------------------------------------------------------------------------------------------------

			//Gets



			ACEDSHAREDDLL_API TILETYPE GetTileType();


			ACEDSHAREDDLL_API double GetCurrentPositionY();
			ACEDSHAREDDLL_API double GetCurrentPositionX();


			ACEDSHAREDDLL_API double GetWidth();
			ACEDSHAREDDLL_API double GetHeight();



			ACEDSHAREDDLL_API Tile* GetTile();
			ACEDSHAREDDLL_API InteractiveObject* GetInteractiveObject();


			ACEDSHAREDDLL_API bool GetHasTile();
			ACEDSHAREDDLL_API bool GetHasInteractiveObject();
			ACEDSHAREDDLL_API bool GetHasInteractiveObjectReference();


			

			//-----------------------------------------------------------------------------------------------------

			//Draws


			ACEDSHAREDDLL_API void Draw(int xoffset, int yoffset, bool invertCollision = false);


			//Draws the tiles collision properties
			//Inverts them if necassery
			ACEDSHAREDDLL_API void DrawObjectType(int xOffset, int yOffset, bool invert);




			//-----------------------------------------------------------------------------------------------------

			//MISC


			//Detects If click intersects with the object selected
			ACEDSHAREDDLL_API bool ClickIntersects(int mouseX, int mouseY);
			

			
			ACEDSHAREDDLL_API void RemoveAllProperties();
			ACEDSHAREDDLL_API void RemoveColor();
			ACEDSHAREDDLL_API void RemoveImage();



			ACEDSHAREDDLL_API void DeleteTile();
			ACEDSHAREDDLL_API void DeleteInteractiveObject();





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