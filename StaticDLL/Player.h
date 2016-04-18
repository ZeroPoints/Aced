#ifndef PLAYER_H
#define PLAYER_H



#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include "character.h"
#include "Map.h"


#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL{


	class Player : public Character
	{
		public:
			STATICDLL_API Player();

			//sets
			STATICDLL_API void AdjustLives(int num);

			STATICDLL_API int Keypress(ALLEGRO_EVENT *ev);





			STATICDLL_API void Update(Map *map);






			STATICDLL_API void CollisionMovingLeft(Map *map);





			STATICDLL_API void CollisionMovingRight(Map *map);




			STATICDLL_API void Falling(Map *map);




			STATICDLL_API void Jumping(Map *map);






			STATICDLL_API bool CheckNextXPositionGoingRight(Map *map, float nextPosX, float nextPosY);
			STATICDLL_API bool CheckNextXPositionGoingLeft(Map *map, float nextPosX, float nextPosY);
			STATICDLL_API bool CheckNextYPositionFalling(Map *map, float nextPosX, float nextPosY);
			STATICDLL_API bool CheckNextYPositionJumping(Map *map, float nextPosX, float nextPosY);






		private:


			int score_;
			int lives_;
			ALLEGRO_EVENT *ev_;
			bool KeyLeft_;
			bool KeyRight_;
			bool KeySpace_;
	};
}
#endif