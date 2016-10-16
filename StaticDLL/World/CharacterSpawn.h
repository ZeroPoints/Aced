#ifndef CHARACTERSPAWN_H
#define CHARACTERSPAWN_H





#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include "../Config/Settings.h"
#include "../ImageManagement/Image.h"





#ifdef STATICDLL_EXPORTS
#define STATICDLL_API __declspec(dllexport)
#else
#define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL
{
	class CharacterSpawn
	{
	public:

		STATICDLL_API CharacterSpawn(Settings *settings);







		//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		//Sets






		STATICDLL_API void SetCurrentPositionX(double x);
		STATICDLL_API void SetCurrentPositionY(double y);
		STATICDLL_API void SetCurrentPosition(double x, double y);
		STATICDLL_API void SetColor(ALLEGRO_COLOR color);
		STATICDLL_API void SetWidth(double val);
		STATICDLL_API void SetHeight(double val);


		STATICDLL_API virtual void SetObjectImageColor(Image *image);




		//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		//Gets





		STATICDLL_API double GetCurrentPositionX();


		STATICDLL_API double GetCurrentPositionY();


		STATICDLL_API double GetHeight();
		STATICDLL_API double GetWidth();






		//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		//Misc



		STATICDLL_API void DrawObjectRotate(int xOffset, int yOffset);













		STATICDLL_API void Update();







	private:

		double	currentPositionX_,
			currentPositionY_,
			width_,
			height_,
			currentRotation_
			;



		bool	
			collisionBot_,
			collisionTop_,
			collisionLeft_,
			collisionRight_,
			hasImage_,
			hasImageReference_,
			hasColor_;


		Image *image_;

		EnumDLL::STATES Id_, keyPressState_, keyPressReturnVal_;
		ALLEGRO_COLOR chosenColor_;



		ALLEGRO_EVENT *ev_;
		Settings *settings_;
	};
}
#endif