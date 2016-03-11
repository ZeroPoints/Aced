#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#define ALLEGRO_NO_MAGIC_MAIN


#include <allegro5\allegro.h>
#include <vector>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "Definitions.h"
//#include "Map.h"


#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL
{
	class ObjectBase
	{
		public:
			

			STATICDLL_API ObjectBase(){
				fprintf(stderr,"An Object Created\n");
				return;
			}



			STATICDLL_API virtual ~ObjectBase(){
				//al_destroy_font(font30_);

				fprintf(stderr,"An Object Destructed\n");
				return;
			}

			STATICDLL_API virtual void InitState(ALLEGRO_DISPLAY *display){
				return;
			};



			STATICDLL_API virtual void SetCurrentPosition(double x, double y){
				currentPositionX_ = x;
				currentPositionY_ = y;
			};
			STATICDLL_API virtual void SetCurrentPositionX(double x){
				currentPositionX_ = x;
			};
			STATICDLL_API virtual void SetCurrentPositionY(double y){
				currentPositionY_ = y;
			};


			STATICDLL_API virtual void SetFuturePosition(double x, double y){
				futurePositionX_ = x;
				futurePositionY_ = y;
			};
			STATICDLL_API virtual void SetFuturePositionX(double x){
				futurePositionX_ = x;
			};
			STATICDLL_API virtual void SetFuturePositionY(double y){
				futurePositionY_ = y;
			};


			STATICDLL_API virtual void CalculateFuturePosition(double x, double y){
				futurePositionX_ = x;
				futurePositionY_ = y;
			};


			STATICDLL_API virtual void SetGravityX(double x){
				gravityX_ = x;
			};
			STATICDLL_API virtual void SetGravityY(double y){
				gravityY_ = y;
			};

			STATICDLL_API virtual void SetVelocityX(double x){
				velocityX_ = x;
			};
			STATICDLL_API virtual void SetVelocityY(double y){
				velocityY_ = y;
			};




			STATICDLL_API virtual double GetVelocityY(){
				return velocityY_;
			};
			STATICDLL_API virtual double GetVelocityX(){
				return velocityX_;
			};
			STATICDLL_API virtual double GetGravityY(){
				return gravityY_;
			};
			STATICDLL_API virtual double GetGravityX(){
				return gravityX_;
			};

			STATICDLL_API virtual double GetFuturePositionY(){
				return futurePositionY_;
			};
			STATICDLL_API virtual double GetFuturePositionX(){
				return futurePositionX_;
			};
			STATICDLL_API virtual double GetCurrentPositionY(){
				return currentPositionY_;
			};
			STATICDLL_API virtual double GetCurrentPositionX(){
				return currentPositionX_;
			};






			STATICDLL_API virtual void SetRightMouseDown(bool flag){
				rightMouseDown_ = flag;
			};
			STATICDLL_API virtual void SetLeftMouseDown(bool flag){
				leftMouseDown_ = flag;
			};
			STATICDLL_API virtual void SetIsMoving(bool flag){
				isMoving_ = flag;
			};
			STATICDLL_API virtual void SetIsFalling(bool flag){
				isFalling_ = flag;
			};


			STATICDLL_API virtual void SetWidth(double x){
				width_ = x;
			};
			STATICDLL_API virtual double GetWidth(){
				return width_;
			};
			STATICDLL_API virtual void SetHeight(double y){
				height_ = y;
			};
			STATICDLL_API virtual double GetHeight(){
				return height_;
			};

			STATICDLL_API virtual void SetCollisionBot(bool flag){
				collisionBot_ = flag;
			};
			STATICDLL_API virtual void SetCollisionTop(bool flag){
				collisionTop_ = flag;
			};
			STATICDLL_API virtual void SetCollisionLeft(bool flag){
				collisionLeft_ = flag;
			};
			STATICDLL_API virtual void SetCollisionRight(bool flag){
				collisionRight_ = flag;
			};


			STATICDLL_API virtual void SetKeyPressState(EnumDLL::STATES state){
				keyPressState_ = state;
			};


			/*STATICDLL_API virtual void SetMap(Map *map){
				map_ = map;
			};*/




			STATICDLL_API virtual void UpdateObject(){

			};

			STATICDLL_API virtual void SetColor(ALLEGRO_COLOR color){
				chosenColor_ = color;
			};
			STATICDLL_API virtual ALLEGRO_COLOR GetColor(){
				return chosenColor_;
			};


			STATICDLL_API virtual void SetMoveSpeed(double ms){
				movespeed_ = ms;
			};

			STATICDLL_API virtual double GetMoveSpeed(){
				return movespeed_;
			};


			STATICDLL_API virtual void SetClickable(bool clickable){
				clickable_ = clickable;
			};
			
			STATICDLL_API virtual bool GetClickable(){
				return clickable_;
			};



			STATICDLL_API virtual void DrawObject(int xOffset, int yOffset){
				al_draw_filled_rectangle(
					currentPositionX_*Constants::TileSize + xOffset,
					currentPositionY_*Constants::TileSize + yOffset,
					currentPositionX_*Constants::TileSize + width_*Constants::TileSize + xOffset,
					currentPositionY_*Constants::TileSize + height_*Constants::TileSize + yOffset,
					chosenColor_		
					);
				//This line below was old code reminder that i need to sort the view point translation of objects
				//al_draw_filled_rectangle(tileX_*20 + mapXoffSet*20, tileY_*20 + mapYoffSet*20, tileX_*20 + tileSize + mapXoffSet*20, tileY_*20 + tileSize + mapYoffSet*20, colour_);
			};
			STATICDLL_API virtual void DrawRectangleMapObject(int xOffset, int yOffset){
				al_draw_rectangle(
					currentPositionX_*Constants::TileSize + xOffset,
					currentPositionY_*Constants::TileSize + yOffset,
					currentPositionX_*Constants::TileSize + width_*Constants::TileSize + xOffset,
					currentPositionY_*Constants::TileSize + height_*Constants::TileSize + yOffset,
					al_map_rgb_f(1,1,1),1	
					);
				//This line below was old code reminder that i need to sort the view point translation of objects
				//al_draw_filled_rectangle(tileX_*20 + mapXoffSet*20, tileY_*20 + mapYoffSet*20, tileX_*20 + tileSize + mapXoffSet*20, tileY_*20 + tileSize + mapYoffSet*20, colour_);
			};

			STATICDLL_API virtual void DrawObject(){
				al_draw_filled_rectangle(
					currentPositionX_*Constants::TileSize,
					currentPositionY_*Constants::TileSize,
					currentPositionX_*Constants::TileSize + width_*Constants::TileSize,
					currentPositionY_*Constants::TileSize + height_*Constants::TileSize,
					chosenColor_		
					);
				//This line below was old code reminder that i need to sort the view point translation of objects
				//al_draw_filled_rectangle(tileX_*20 + mapXoffSet*20, tileY_*20 + mapYoffSet*20, tileX_*20 + tileSize + mapXoffSet*20, tileY_*20 + tileSize + mapYoffSet*20, colour_);
			};

			           



			//Detects If click intersects with the object selected
			STATICDLL_API bool ClickIntersects(int mouseX, int mouseY)
			{
				//Offset the mouse position to the actual coord as the mouseX and mouseY i read in a moded to be offset? by half the tile size for some reason
				mouseX = mouseX + (Constants::TileSize/2);
				mouseY = mouseY + (Constants::TileSize/2);

				if(mouseX >= (currentPositionX_*Constants::TileSize) && 
					mouseX < ((currentPositionX_ + width_)*Constants::TileSize) &&
					mouseY >= (currentPositionY_*Constants::TileSize) && 
					mouseY < ((currentPositionY_ + height_)*Constants::TileSize))
				{
					return true;
				}
				return false;

			};


		private:


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
					movespeed_
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
					clickable_
					;	

			
			EnumDLL::STATES Id_, keyPressState_, keyPressReturnVal_;
			ALLEGRO_FONT *font30_;
			ALLEGRO_EVENT_QUEUE *event_queue_;
			ALLEGRO_EVENT event_;
			//Map *map_;
			ALLEGRO_DISPLAY *display_;
			ALLEGRO_COLOR chosenColor_;
	};
}
#endif
