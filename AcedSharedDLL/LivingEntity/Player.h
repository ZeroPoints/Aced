#ifndef PLAYER_H
#define PLAYER_H



#define ALLEGRO_NO_MAGIC_MAIN


#include <sstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include "../Config/BaseSettings.h"
#include "../World/Map.h"
#include "../ImageManagement/ImageBundle.h"




#ifdef ACEDSHAREDDLL_EXPORTS
   #define ACEDSHAREDDLL_API __declspec(dllexport)
#else
   #define ACEDSHAREDDLL_API __declspec(dllimport)
#endif



namespace AcedSharedDLL{


	class Player
	{
		public:
			ACEDSHAREDDLL_API Player(std::shared_ptr<BaseSettings> &settings, std::shared_ptr<Map> &map);

			ACEDSHAREDDLL_API ~Player();






			//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			//Sets



			ACEDSHAREDDLL_API void SetCharacterYAxisState(CHARACTERYAXISSTATES characterState);


			ACEDSHAREDDLL_API void SetHealth(int hp);




			ACEDSHAREDDLL_API void SetCurrentPositionX(double x);
			ACEDSHAREDDLL_API void SetCurrentPositionY(double y);
			ACEDSHAREDDLL_API void SetCurrentPosition(double x, double y);
			ACEDSHAREDDLL_API void SetColor(ALLEGRO_COLOR color);
			ACEDSHAREDDLL_API void SetWidth(double val);
			ACEDSHAREDDLL_API void SetHeight(double val);
			ACEDSHAREDDLL_API void SetGravityY(double val);
			ACEDSHAREDDLL_API void SetVelocityY(double val);
			ACEDSHAREDDLL_API void SetMaxVelocityY(double val);
			ACEDSHAREDDLL_API void SetAccelerationY(double val);
			ACEDSHAREDDLL_API void SetMoveSpeedDelta(double val);
			ACEDSHAREDDLL_API void SetMoveSpeed(double val);
			ACEDSHAREDDLL_API void SetJumpSpeed(double val);


			ACEDSHAREDDLL_API void SetPlayerFacingDirection(CHARACTERFACINGDIRECTION direction);
			ACEDSHAREDDLL_API virtual void SetImageBundle(std::shared_ptr<ImageBundle> &imageBundle);

			ACEDSHAREDDLL_API void SetKeyRight(bool val);
			ACEDSHAREDDLL_API void SetKeyLeft(bool val);



			//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			//Gets




			ACEDSHAREDDLL_API CHARACTERYAXISSTATES GetCharacterYAxisState();

			ACEDSHAREDDLL_API double GetHealth();



			ACEDSHAREDDLL_API CHARACTERFACINGDIRECTION GetPlayerFacingDirection();

			ACEDSHAREDDLL_API double GetCurrentPositionX();


			ACEDSHAREDDLL_API double GetCurrentPositionY();


			ACEDSHAREDDLL_API double GetHeight();
			ACEDSHAREDDLL_API double GetWidth();

			ACEDSHAREDDLL_API double GetMoveSpeed();
			ACEDSHAREDDLL_API double GetMoveSpeedDelta();

			ACEDSHAREDDLL_API double GetVelocityY();
			ACEDSHAREDDLL_API double GetMaxVelocityY();
			ACEDSHAREDDLL_API double GetAccelerationY();

			ACEDSHAREDDLL_API double GetJumpSpeed();


			ACEDSHAREDDLL_API bool GetKeyRight();
			ACEDSHAREDDLL_API bool GetKeyLeft();

			ACEDSHAREDDLL_API std::shared_ptr<Map> &GetMap();
			ACEDSHAREDDLL_API std::shared_ptr<BaseSettings> &GetSettings();

			ACEDSHAREDDLL_API std::vector<std::shared_ptr<Item>> &GetItemList();




			//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			//Misc

			ACEDSHAREDDLL_API void AdjustHealth(int hp);


			ACEDSHAREDDLL_API void AdjustPlayerRotation();

			ACEDSHAREDDLL_API void IncrementAnimationTick();



			ACEDSHAREDDLL_API void Draw(ALLEGRO_FONT* font);








			ACEDSHAREDDLL_API int Keypress(ALLEGRO_EVENT *ev);

			ACEDSHAREDDLL_API void KeyPressUpdateE();




			ACEDSHAREDDLL_API void Update(ALLEGRO_EVENT *ev);




			//this is moving in X direction
			ACEDSHAREDDLL_API bool CheckNextXPositionGoingLeft(float nextPosX, float nextPosY);
			ACEDSHAREDDLL_API bool CheckNextXPositionGoingRight(float nextPosX, float nextPosY);

			ACEDSHAREDDLL_API bool CheckNextPositionForObject(std::shared_ptr<Cell> &cellFuture);



			//this is moving in Y direction
			ACEDSHAREDDLL_API bool CheckNextYPositionFalling(float nextPosX, float nextPosY);

			//this is moving in Y direction
			ACEDSHAREDDLL_API bool CheckNextYPositionJumping(float nextPosX, float nextPosY);


			ACEDSHAREDDLL_API void CollisionMovingLeft();




			ACEDSHAREDDLL_API void CollisionMovingRight();




			ACEDSHAREDDLL_API void Falling();






			ACEDSHAREDDLL_API void Jumping();









			ACEDSHAREDDLL_API void AddItemToInventory(std::shared_ptr<Item> &item);


			ACEDSHAREDDLL_API void RemoveItemFromInventory(int id);








	private:
		int health_;

		CHARACTERYAXISSTATES characterYAxisState_;


		std::vector<std::shared_ptr<Item>> itemList_;



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
			lastImageUpdate_
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





		ALLEGRO_USTR *utext_;


		std::shared_ptr<ImageBundle> imageBundle_;

		CHARACTERFACINGDIRECTION faceDirection_;
		CHARACTERIMAGESTATES imageState_;
		int animationTick_;



		STATES Id_, keyPressState_, keyPressReturnVal_;

		ALLEGRO_EVENT_QUEUE *event_queue_;
		ALLEGRO_EVENT event_;
		ALLEGRO_DISPLAY *display_;
		ALLEGRO_COLOR chosenColor_;








		ALLEGRO_EVENT *ev_;
		std::shared_ptr<Map> map_;
		std::shared_ptr<BaseSettings> settings_;
		bool KeyE_;
		bool KeyLeft_;
		bool OldKeyLeft_;
		bool KeyRight_;
		bool OldKeyRight_;
		bool KeySpace_;

		bool KeyUp_;
		bool KeyDown_;


	};
}
#endif