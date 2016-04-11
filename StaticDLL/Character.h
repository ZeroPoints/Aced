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


			STATICDLL_API virtual EnumDLL::CHARACTERYAXISSTATES GetCharacterYAxisState()
			{
				return characterYAxisState_;
			}
			STATICDLL_API virtual void SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES characterState)
			{
				characterYAxisState_ = characterState;
			}






			//This was testing a smaller bounding box around player. Instead try reduce player size 
			STATICDLL_API virtual double GetCurrentPositionXLeft(){
				double temp = GetCurrentPositionX();
				temp = temp + 0.1;
				return temp;
			};

			STATICDLL_API virtual double GetCurrentPositionXRight(){
				double temp = GetCurrentPositionX() + GetWidth();
				temp = temp - 0.2;
				return temp;
			};

			STATICDLL_API virtual double GetCurrentPositionYTop(){
				double temp = GetCurrentPositionY();
				temp = temp + 0.1;
				return temp;
			};

			STATICDLL_API virtual double GetCurrentPositionYBot(){
				double temp = GetCurrentPositionY() + GetHeight();
				temp = temp - 0.2;
				return temp;
			};


		private:
			int health_;

			EnumDLL::CHARACTERYAXISSTATES characterYAxisState_;


	};
}
#endif