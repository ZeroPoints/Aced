#ifndef CHARACTER_H
#define CHARACTER_H





#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include "../Config/Settings.h"
#include "../ImageManagement/Image.h"
#include "../World/Cell.h"
#include <math.h>




#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL
{
	class Character
	{
		public:

			STATICDLL_API Character(Settings *settings, int mapWidth, int mapHeight, std::vector<std::vector<Cell>> *cellMap);



			STATICDLL_API ~Character();






			//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			//Sets



			STATICDLL_API void SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES characterState);


			STATICDLL_API void SetHealth(int hp);


			

			STATICDLL_API void SetCurrentPositionX(float x);
			STATICDLL_API void SetCurrentPositionY(float y);
			STATICDLL_API void SetCurrentPosition(float x, float y);
			STATICDLL_API void SetColor(ALLEGRO_COLOR color);
			STATICDLL_API void SetWidth(float val);
			STATICDLL_API void SetHeight(float val);
			STATICDLL_API void SetGravityY(float val);
			STATICDLL_API void SetVelocityY(float val);
			STATICDLL_API void SetMaxVelocityY(float val);
			STATICDLL_API void SetAccelerationY(float val);
			STATICDLL_API void SetMoveSpeedDelta(float val);
			STATICDLL_API void SetMoveSpeed(float val);
			STATICDLL_API void SetJumpSpeed(float val);


			STATICDLL_API void SetPlayerFacingDirection(EnumDLL::CHARACTERFACINGDIRECTION direction);
			STATICDLL_API virtual void SetObjectImageColor(Image *image);

			STATICDLL_API void SetKeyRight(bool val);
			STATICDLL_API void SetKeyLeft(bool val);

			STATICDLL_API void SetAIEnabled(bool val);

			STATICDLL_API void SetImageSet(EnumDLL::IMAGESETS imageSet);


			//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			//Gets




			STATICDLL_API EnumDLL::CHARACTERYAXISSTATES GetCharacterYAxisState();

			STATICDLL_API float GetHealth();



			STATICDLL_API EnumDLL::CHARACTERFACINGDIRECTION GetPlayerFacingDirection();

			STATICDLL_API float GetCurrentPositionX();


			STATICDLL_API float GetCurrentPositionY();


			STATICDLL_API float GetHeight();
			STATICDLL_API float GetWidth();

			STATICDLL_API float GetMoveSpeed();
			STATICDLL_API float GetMoveSpeedDelta();

			STATICDLL_API float GetVelocityY();
			STATICDLL_API float GetMaxVelocityY();
			STATICDLL_API float GetAccelerationY();

			STATICDLL_API float GetJumpSpeed();

			
			STATICDLL_API bool GetKeyRight();
			STATICDLL_API bool GetKeyLeft();

			STATICDLL_API Settings GetSettings();

			STATICDLL_API bool GetHasImage();
			STATICDLL_API Image *GetObjectImage();
			
			STATICDLL_API EnumDLL::IMAGESETS GetImageSet();


			//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			//Misc

			STATICDLL_API void AdjustHealth(int hp);


			STATICDLL_API void AdjustPlayerRotation();




			STATICDLL_API void DrawObjectRotate(float mapXOffset, float mapYOffset);








			STATICDLL_API int Keypress(ALLEGRO_EVENT *ev);





			STATICDLL_API void Update();




			//this is moving in X direction
			STATICDLL_API bool CheckNextXPositionGoingLeft(float nextPosX, float nextPosY);
			STATICDLL_API bool CheckNextXPositionGoingRight(float nextPosX, float nextPosY);




			//this is moving in Y direction
			STATICDLL_API bool CheckNextYPositionFalling(float nextPosX, float nextPosY);

			//this is moving in Y direction
			STATICDLL_API bool CheckNextYPositionJumping(float nextPosX, float nextPosY);


			STATICDLL_API void CollisionMovingLeft();




			STATICDLL_API void CollisionMovingRight();




			STATICDLL_API void Falling();






			STATICDLL_API void Jumping();




















		private:
			int health_;

			EnumDLL::CHARACTERYAXISSTATES characterYAxisState_;



			int mapWidth_, 
				mapHeight_;




			float	currentPositionX_,
				currentPositionY_,
				futurePositionX_,
				futurePositionY_,
				gravityX_,
				gravityY_,
				velocityX_,
				velocityY_,
				width_,
				height_,
				jumpspeed_,
				movespeed_,
				movespeedDelta_,
				accelerationX_,
				accelerationY_,
				maxAccelerationX_,
				maxAccelerationY_,
				maxVelocityY_,
				currentRotation_
				;



			bool	redraw_,
				done_,
				rightMouseDown_,
				leftMouseDown_,
				isMoving_,
				isFalling_,
				collisionBot_,
				collisionTop_,
				collisionLeft_,
				collisionRight_,
				clickable_,
				hasText_,
				hasImage_,
				hasImageReference_,
				hasColor_,
				aiEnabled_;



			std::vector<std::vector<Cell>> *cellMap_;


			EnumDLL::CHARACTERFACINGDIRECTION faceDirection_;

			EnumDLL::IMAGESETS imageSet_;

			ALLEGRO_USTR *utext_;
			char *text_;





			Image *image_;

			EnumDLL::STATES Id_, keyPressState_, keyPressReturnVal_;
			ALLEGRO_FONT *font30_;
			ALLEGRO_EVENT_QUEUE *event_queue_;
			ALLEGRO_EVENT event_;
			ALLEGRO_DISPLAY *display_;
			ALLEGRO_COLOR chosenColor_;




			ALLEGRO_EVENT *ev_;
			Settings *settings_;
			bool KeyLeft_;
			bool KeyRight_;
			bool KeySpace_;
	};
}
#endif