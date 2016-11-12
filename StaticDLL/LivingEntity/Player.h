#ifndef PLAYER_H
#define PLAYER_H



#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include "../Config/Settings.h"
#include "../World/Map.h"
#include "../ImageManagement/Image.h"




#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL{


	class Player
	{
		public:
			STATICDLL_API Player(Settings *settings, Map *map);







			//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			//Sets



			STATICDLL_API void SetCharacterYAxisState(CHARACTERYAXISSTATES characterState);


			STATICDLL_API void SetHealth(int hp);




			STATICDLL_API void SetCurrentPositionX(double x);
			STATICDLL_API void SetCurrentPositionY(double y);
			STATICDLL_API void SetCurrentPosition(double x, double y);
			STATICDLL_API void SetColor(ALLEGRO_COLOR color);
			STATICDLL_API void SetWidth(double val);
			STATICDLL_API void SetHeight(double val);
			STATICDLL_API void SetGravityY(double val);
			STATICDLL_API void SetVelocityY(double val);
			STATICDLL_API void SetMaxVelocityY(double val);
			STATICDLL_API void SetAccelerationY(double val);
			STATICDLL_API void SetMoveSpeedDelta(double val);
			STATICDLL_API void SetMoveSpeed(double val);
			STATICDLL_API void SetJumpSpeed(double val);


			STATICDLL_API void SetPlayerFacingDirection(CHARACTERFACINGDIRECTION direction);
			STATICDLL_API virtual void SetObjectImageColor(Image *image);

			STATICDLL_API void SetKeyRight(bool val);
			STATICDLL_API void SetKeyLeft(bool val);



			//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			//Gets




			STATICDLL_API CHARACTERYAXISSTATES GetCharacterYAxisState();

			STATICDLL_API double GetHealth();



			STATICDLL_API CHARACTERFACINGDIRECTION GetPlayerFacingDirection();

			STATICDLL_API double GetCurrentPositionX();


			STATICDLL_API double GetCurrentPositionY();


			STATICDLL_API double GetHeight();
			STATICDLL_API double GetWidth();

			STATICDLL_API double GetMoveSpeed();
			STATICDLL_API double GetMoveSpeedDelta();

			STATICDLL_API double GetVelocityY();
			STATICDLL_API double GetMaxVelocityY();
			STATICDLL_API double GetAccelerationY();

			STATICDLL_API double GetJumpSpeed();


			STATICDLL_API bool GetKeyRight();
			STATICDLL_API bool GetKeyLeft();

			STATICDLL_API Map GetMap();
			STATICDLL_API Settings GetSettings();

			STATICDLL_API std::vector<Item*> &GetItemList();




			//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			//Misc

			STATICDLL_API void AdjustHealth(int hp);


			STATICDLL_API void AdjustPlayerRotation();




			STATICDLL_API void DrawObjectRotate();








			STATICDLL_API int Keypress(ALLEGRO_EVENT *ev);

			STATICDLL_API void KeyPressUpdateE();




			STATICDLL_API void Update();




			//this is moving in X direction
			STATICDLL_API bool CheckNextXPositionGoingLeft(float nextPosX, float nextPosY);
			STATICDLL_API bool CheckNextXPositionGoingRight(float nextPosX, float nextPosY);

			STATICDLL_API bool CheckNextPositionForObject(Cell &cellFuture);



			//this is moving in Y direction
			STATICDLL_API bool CheckNextYPositionFalling(float nextPosX, float nextPosY);

			//this is moving in Y direction
			STATICDLL_API bool CheckNextYPositionJumping(float nextPosX, float nextPosY);


			STATICDLL_API void CollisionMovingLeft();




			STATICDLL_API void CollisionMovingRight();




			STATICDLL_API void Falling();






			STATICDLL_API void Jumping();









			STATICDLL_API void AddItemToInventory(Item *item);


			STATICDLL_API void RemoveItemFromInventory(int id);








	private:
		int health_;

		CHARACTERYAXISSTATES characterYAxisState_;


		std::vector<Item*> itemList_;



		double	currentPositionX_,
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
			showInvetory_;


		CHARACTERFACINGDIRECTION faceDirection_;

		ALLEGRO_USTR *utext_;
		char *text_;


		Image *image_;

		STATES Id_, keyPressState_, keyPressReturnVal_;
		ALLEGRO_FONT *font30_;
		ALLEGRO_EVENT_QUEUE *event_queue_;
		ALLEGRO_EVENT event_;
		ALLEGRO_DISPLAY *display_;
		ALLEGRO_COLOR chosenColor_;



		ALLEGRO_EVENT *ev_;
		Map *map_;
		Settings *settings_;
		bool KeyE_;
		bool KeyLeft_;
		bool KeyRight_;
		bool KeySpace_;


	};
}
#endif