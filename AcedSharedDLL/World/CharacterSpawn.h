#ifndef CHARACTERSPAWN_H
#define CHARACTERSPAWN_H





#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include "../Config/BaseSettings.h"
#include "../ImageManagement/Image.h"





#ifdef ACEDSHAREDDLL_EXPORTS
#define ACEDSHAREDDLL_API __declspec(dllexport)
#else
#define ACEDSHAREDDLL_API __declspec(dllimport)
#endif


namespace AcedSharedDLL
{
	class CharacterSpawn
	{
	public:

		ACEDSHAREDDLL_API CharacterSpawn(BaseSettings *settings);







		//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		//Sets






		ACEDSHAREDDLL_API void SetCurrentPositionX(double x);
		ACEDSHAREDDLL_API void SetCurrentPositionY(double y);
		ACEDSHAREDDLL_API void SetCurrentPosition(double x, double y);
		ACEDSHAREDDLL_API void SetColor(ALLEGRO_COLOR color);
		ACEDSHAREDDLL_API void SetWidth(double val);
		ACEDSHAREDDLL_API void SetHeight(double val);


		ACEDSHAREDDLL_API virtual void SetObjectImageColor(Image *image);




		//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		//Gets





		ACEDSHAREDDLL_API double GetCurrentPositionX();


		ACEDSHAREDDLL_API double GetCurrentPositionY();


		ACEDSHAREDDLL_API double GetHeight();
		ACEDSHAREDDLL_API double GetWidth();






		//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		//Misc



		ACEDSHAREDDLL_API void DrawObjectRotate(int xOffset, int yOffset);













		ACEDSHAREDDLL_API void Update();







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

		STATES Id_, keyPressState_, keyPressReturnVal_;
		ALLEGRO_COLOR chosenColor_;



		ALLEGRO_EVENT *ev_;
		BaseSettings *settings_;
	};
}
#endif