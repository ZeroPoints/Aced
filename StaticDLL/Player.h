#ifndef PLAYER_H
#define PLAYER_H



#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include "character.h"


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

			STATICDLL_API int PlayerKeypress(ALLEGRO_EVENT *ev);



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