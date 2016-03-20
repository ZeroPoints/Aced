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

	//This object is a Tile
	//This inherits from Object base like most other objects
	class Tile : public ObjectBase
	{
		public:
			STATICDLL_API Tile()
			{
				
			};
			
			STATICDLL_API ~Tile()
			{
				if(GetCurrentPositionX() != -6277438562204192500000000000000000000000000000000000000000000000000.000000)
				{
					fprintf(stderr,"A Tile[%f][%f] Destructed\n", GetCurrentPositionX(), GetCurrentPositionY());
				}
			};


			//does nothing really atm
			STATICDLL_API EnumDLL::TILETYPE GetTileType()
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
				tileType_ = selectedTile->GetTileType();
				SetObjectProperties(selectedTile);
			}


		private:	
			EnumDLL::TILETYPE tileType_;//0 = empty, 1 = solid,
			//TODO: change to enum 
	};


}
#endif