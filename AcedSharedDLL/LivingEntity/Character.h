#ifndef CHARACTER_H
#define CHARACTER_H





#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include "../Config/BaseSettings.h"
#include "../ImageManagement/ImageBundle.h"
#include "../World/Cell.h"
#include <math.h>

#include <memory>


#ifdef ACEDSHAREDDLL_EXPORTS
   #define ACEDSHAREDDLL_API __declspec(dllexport)
#else
   #define ACEDSHAREDDLL_API __declspec(dllimport)
#endif


namespace AcedSharedDLL
{
	class Character
	{
		public:

			ACEDSHAREDDLL_API Character(std::shared_ptr<BaseSettings> &settings, int mapWidth, int mapHeight, std::vector<std::vector<std::shared_ptr<Cell>>> &cellMap);



			ACEDSHAREDDLL_API ~Character();






			//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			//Sets



			ACEDSHAREDDLL_API void SetCharacterYAxisState(CHARACTERYAXISSTATES characterState);


			ACEDSHAREDDLL_API void SetHealth(int hp);


			

			ACEDSHAREDDLL_API void SetCurrentPositionX(float x);
			ACEDSHAREDDLL_API void SetCurrentPositionY(float y);
			ACEDSHAREDDLL_API void SetCurrentPosition(float x, float y);
			ACEDSHAREDDLL_API void SetColor(ALLEGRO_COLOR color);
			ACEDSHAREDDLL_API void SetWidth(float val);
			ACEDSHAREDDLL_API void SetHeight(float val);
			ACEDSHAREDDLL_API void SetGravityY(float val);
			ACEDSHAREDDLL_API void SetVelocityY(float val);
			ACEDSHAREDDLL_API void SetMaxVelocityY(float val);
			ACEDSHAREDDLL_API void SetAccelerationY(float val);
			ACEDSHAREDDLL_API void SetMoveSpeedDelta(float val);
			ACEDSHAREDDLL_API void SetMoveSpeed(float val);
			ACEDSHAREDDLL_API void SetJumpSpeed(float val);


			ACEDSHAREDDLL_API void SetPlayerFacingDirection(CHARACTERFACINGDIRECTION direction);

			ACEDSHAREDDLL_API void SetImageBundle(std::shared_ptr<ImageBundle> &image);


			ACEDSHAREDDLL_API void SetKeyRight(bool val);
			ACEDSHAREDDLL_API void SetKeyLeft(bool val);

			ACEDSHAREDDLL_API void SetAIEnabled(bool val);

			ACEDSHAREDDLL_API void SetImageSet(AcedSharedDLL::IMAGESETS imageSet);


			//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			//Gets




			ACEDSHAREDDLL_API CHARACTERYAXISSTATES GetCharacterYAxisState();

			ACEDSHAREDDLL_API float GetHealth();



			ACEDSHAREDDLL_API CHARACTERFACINGDIRECTION GetPlayerFacingDirection();

			ACEDSHAREDDLL_API float GetCurrentPositionX();


			ACEDSHAREDDLL_API float GetCurrentPositionY();


			ACEDSHAREDDLL_API float GetHeight();
			ACEDSHAREDDLL_API float GetWidth();

			ACEDSHAREDDLL_API float GetMoveSpeed();
			ACEDSHAREDDLL_API float GetMoveSpeedDelta();

			ACEDSHAREDDLL_API float GetVelocityY();
			ACEDSHAREDDLL_API float GetMaxVelocityY();
			ACEDSHAREDDLL_API float GetAccelerationY();

			ACEDSHAREDDLL_API float GetJumpSpeed();

			
			ACEDSHAREDDLL_API bool GetKeyRight();
			ACEDSHAREDDLL_API bool GetKeyLeft();

			ACEDSHAREDDLL_API std::shared_ptr<BaseSettings> &GetSettings();

			ACEDSHAREDDLL_API bool GetHasImage();
			ACEDSHAREDDLL_API std::shared_ptr<ImageBundle> &GetImageBundle();
			
			ACEDSHAREDDLL_API AcedSharedDLL::IMAGESETS GetImageSet();


			//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			//Misc

			ACEDSHAREDDLL_API void AdjustHealth(int hp);


			ACEDSHAREDDLL_API void AdjustPlayerRotation();




			ACEDSHAREDDLL_API void DrawObjectRotate(float mapXOffset, float mapYOffset);








			ACEDSHAREDDLL_API int Keypress(ALLEGRO_EVENT *ev);





			ACEDSHAREDDLL_API void Update();




			//this is moving in X direction
			ACEDSHAREDDLL_API bool CheckNextXPositionGoingLeft(float nextPosX, float nextPosY);
			ACEDSHAREDDLL_API bool CheckNextXPositionGoingRight(float nextPosX, float nextPosY);




			//this is moving in Y direction
			ACEDSHAREDDLL_API bool CheckNextYPositionFalling(float nextPosX, float nextPosY);

			//this is moving in Y direction
			ACEDSHAREDDLL_API bool CheckNextYPositionJumping(float nextPosX, float nextPosY);


			ACEDSHAREDDLL_API void CollisionMovingLeft();




			ACEDSHAREDDLL_API void CollisionMovingRight();




			ACEDSHAREDDLL_API void Falling();






			ACEDSHAREDDLL_API void Jumping();




















		private:
			int health_;

			CHARACTERYAXISSTATES characterYAxisState_;



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



			std::vector<std::vector<std::shared_ptr<Cell>>> cellMap_;


			CHARACTERFACINGDIRECTION faceDirection_;

			AcedSharedDLL::IMAGESETS imageSet_;

			ALLEGRO_USTR *utext_;
			char *text_;





			std::shared_ptr<ImageBundle> imageBundle_;

			STATES Id_, keyPressState_, keyPressReturnVal_;
			//ALLEGRO_FONT *font30_;
			ALLEGRO_EVENT_QUEUE *event_queue_;
			ALLEGRO_EVENT event_;
			ALLEGRO_DISPLAY *display_;
			ALLEGRO_COLOR chosenColor_;




			ALLEGRO_EVENT *ev_;
			std::shared_ptr<BaseSettings> settings_;
			bool KeyLeft_;
			bool KeyRight_;
			bool KeySpace_;
	};
}
#endif