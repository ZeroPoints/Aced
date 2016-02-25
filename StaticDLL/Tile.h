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
			STATICDLL_API Tile();
			
			STATICDLL_API int GetTileType()
			{
				return tileType_;
			}
			STATICDLL_API void SetTileType(EnumDLL::TILETYPE tileType)
			{
				tileType_ = tileType;
			};


		private:	
			EnumDLL::TILETYPE tileType_;//0 = empty, 1 = solid,
			//TODO: change to enum 
	};


}
#endif