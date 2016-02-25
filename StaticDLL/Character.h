#ifndef CHARACTER_H
#define CHARACTER_H





#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include "ObjectBase.h"



#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL
{
	class Character : public ObjectBase
	{
		public:
			STATICDLL_API virtual void SetHealth(int hp)
			{
				health_ = hp;
			}
			STATICDLL_API virtual double GetHealth()
			{
				return health_;
			}
			STATICDLL_API virtual void AdjustHealth(int hp){
				health_ = health_+hp;
			}
		private:
			int health_;
	};
}
#endif