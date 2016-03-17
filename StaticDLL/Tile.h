#ifndef TILE_H
#define TILE_H



#define ALLEGRO_NO_MAGIC_MAIN


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "ObjectBase.h"
#include "Definitions.h"


#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL{

	//
	class Tile : public ObjectBase
	{
		public:
			STATICDLL_API Tile()
			{
				
			};
			

			//does nothing really atm
			STATICDLL_API int GetTileType()
			{
				return tileType_;
			}
			//does nothing really atm
			STATICDLL_API void SetTileType(EnumDLL::TILETYPE tileType)
			{
				tileType_ = tileType;
			};



			//Sets equivalent properties for the tile from another tile object
			//Will probably make a SetObjectProperties one aswell later that this one can call within it.
			//So it sets it own properties then its object properties that are inherited
			STATICDLL_API void SetTileProperties(Tile *selectedTile)
			{
				SetObjectProperties(selectedTile);
			}


		private:	
			EnumDLL::TILETYPE tileType_;//0 = empty, 1 = solid,
			//TODO: change to enum 
	};


}
#endif