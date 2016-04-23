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
				tileCollisionTypeColor_ = al_map_rgb_f(0,0,0);
			};
			
			STATICDLL_API ~Tile()
			{
				//i should really set the position to something mmm or have a bool. Shouldnt really need this soon later anyway its just a debug msg
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
				//So if the tile is not already empty force new tile SOLID properties over it.
				if(GetTileType() == EnumDLL::TILETYPE::EMPTYTILE)
				{
					SetTileTypeProperties(selectedTile);
				}
				SetObjectProperties(selectedTile);
			}





			STATICDLL_API void SetTileTypeProperties(Tile *selectedTile)
			{
				tileType_ = selectedTile->GetTileType();
			}


			//Draw an object without need of translation
			STATICDLL_API virtual void DrawObjectType(bool invert){
				DrawObjectType(0,0, invert);
			};

			
			STATICDLL_API void DrawObjectType(int xOffset, int yOffset, bool invert){
				ALLEGRO_COLOR newColor;
				newColor.a = 1;
				newColor.r = invert ? !tileCollisionTypeColor_.r : tileCollisionTypeColor_.r;
				newColor.g = invert ? !tileCollisionTypeColor_.g : tileCollisionTypeColor_.g;
				newColor.b = invert ? !tileCollisionTypeColor_.b : tileCollisionTypeColor_.b;

				if(tileType_ == EnumDLL::TILETYPE::SOLIDTILE)
				{
					al_draw_rectangle(
						GetCurrentPositionX()*Constants::TileSize + xOffset + (Constants::TileSize/5),
						GetCurrentPositionY()*Constants::TileSize + yOffset + (Constants::TileSize/5),
						GetCurrentPositionX()*Constants::TileSize + GetWidth()*Constants::TileSize + xOffset - (Constants::TileSize/5),
						GetCurrentPositionY()*Constants::TileSize + GetHeight()*Constants::TileSize + yOffset - (Constants::TileSize/5),
						newColor,2
					);
				}
				else if(tileType_ == EnumDLL::TILETYPE::COLLISIONTOPTILE)
				{
					al_draw_line(
						GetCurrentPositionX()*Constants::TileSize + xOffset														 + (Constants::TileSize/5),
						GetCurrentPositionY()*Constants::TileSize + yOffset														 + (Constants::TileSize/5),
						GetCurrentPositionX()*Constants::TileSize + GetWidth()*Constants::TileSize + xOffset					 - (Constants::TileSize/5),
						GetCurrentPositionY()*Constants::TileSize + yOffset														 + (Constants::TileSize/5),
						newColor,2
					);
				}
				else if(tileType_ == EnumDLL::TILETYPE::COLLISIONLEFTTILE)
				{
					al_draw_line(
						GetCurrentPositionX()*Constants::TileSize + xOffset														 + (Constants::TileSize/5),
						GetCurrentPositionY()*Constants::TileSize + yOffset														 + (Constants::TileSize/5),
						GetCurrentPositionX()*Constants::TileSize + xOffset														 + (Constants::TileSize/5),
						GetCurrentPositionY()*Constants::TileSize + GetHeight()*Constants::TileSize + yOffset					 - (Constants::TileSize/5),
						newColor,2
					);
				}
				else if(tileType_ == EnumDLL::TILETYPE::COLLISIONRIGHTTILE)
				{
					al_draw_line(
						GetCurrentPositionX()*Constants::TileSize + GetWidth()*Constants::TileSize + xOffset					 - (Constants::TileSize/5),
						GetCurrentPositionY()*Constants::TileSize + yOffset														 + (Constants::TileSize/5),
						GetCurrentPositionX()*Constants::TileSize + GetWidth()*Constants::TileSize + xOffset					 - (Constants::TileSize/5),
						GetCurrentPositionY()*Constants::TileSize + GetHeight()*Constants::TileSize + yOffset					 - (Constants::TileSize/5),
						newColor,2
					);
				}
				else if(tileType_ == EnumDLL::TILETYPE::INVERTCOLLISIONCOLOR)
				{
					//reverse inversion tile 
					newColor.r = invert ? tileCollisionTypeColor_.r : !tileCollisionTypeColor_.r;
					newColor.g = invert ? tileCollisionTypeColor_.g : !tileCollisionTypeColor_.g;
					newColor.b = invert ? tileCollisionTypeColor_.b : !tileCollisionTypeColor_.b;
					al_draw_rectangle(
						GetCurrentPositionX()*Constants::TileSize + xOffset + (Constants::TileSize/5),
						GetCurrentPositionY()*Constants::TileSize + yOffset + (Constants::TileSize/5),
						GetCurrentPositionX()*Constants::TileSize + GetWidth()*Constants::TileSize + xOffset - (Constants::TileSize/5),
						GetCurrentPositionY()*Constants::TileSize + GetHeight()*Constants::TileSize + yOffset - (Constants::TileSize/5),
						newColor,2
					);
				}
			};


			STATICDLL_API void SetTileCollisionTypeColor(ALLEGRO_COLOR color){
				tileCollisionTypeColor_ = color;
			}



		private:	
			EnumDLL::TILETYPE tileType_;

			ALLEGRO_COLOR tileCollisionTypeColor_;

	};


}
#endif