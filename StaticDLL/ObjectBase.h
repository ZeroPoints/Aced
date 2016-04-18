#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#define ALLEGRO_NO_MAGIC_MAIN


#include <allegro5\allegro.h>
#include <vector>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "Definitions.h"
#include "Image.h"

#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL
{
	//Most objects will inherit there properties from this object as most objects within this game share properties from this object
	class ObjectBase
	{
		public:
			

			STATICDLL_API ObjectBase(){
				hasText_ = false;
				movespeed_ = 0;
				hasImage_ = false;
				fprintf(stderr,"An Object Created\n");
				return;
			}


			//All might destroyer of worlds
			//Will consume all knowledge of this object...Hopefully
			STATICDLL_API virtual ~ObjectBase(){
				if(hasText_ == true)
				{
					al_destroy_font(font30_);
					al_ustr_free(utext_);
					al_free(text_);
				}

				if(hasImage_)
				{
					//dont delete image as all images are shared resource pointer
					//delete image_;
				}
				fprintf(stderr,"An Object Destructed\n");
				return;
			}


			STATICDLL_API virtual void SetObjectProperties(ObjectBase *selectedObject){
				//hopefully this assigning isnt a pointer but a new object.
				//so if i recreate map and it deletes this tiles it doesnt delete the color ref from the tile picker
				chosenColor_ = selectedObject->chosenColor_;


				if(selectedObject->hasImage_)
				{
					SetObjectImage(selectedObject->GetObjectImage());
				}

				return;

			};


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


			STATICDLL_API virtual void SetMaxAccelerationY(double y){
				 maxAccelerationY_= y;
			};
			STATICDLL_API virtual void SetMaxAccelerationX(double x){
				 maxAccelerationX_= x;
			};
			STATICDLL_API virtual void SetAccelerationY(double y){
				 accelerationY_= y;
			};
			STATICDLL_API virtual void SetAccelerationX(double x){
				 accelerationX_= x;
			};
			STATICDLL_API virtual double GetAccelerationY(){
				return accelerationY_;
			};
			STATICDLL_API virtual double GetAccelerationX(){
				return accelerationX_;
			};
			STATICDLL_API virtual double GetMaxAccelerationY(){
				return maxAccelerationY_;
			};
			STATICDLL_API virtual double GetMaxAccelerationX(){
				return maxAccelerationX_;
			};


			STATICDLL_API virtual void SetMaxVelocityY(double max){
				maxVelocityY_ = max;
			};
			STATICDLL_API virtual double GetMaxVelocityY(){
				return maxVelocityY_;
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


			STATICDLL_API virtual void SetFont(ALLEGRO_FONT *font){
				font30_ = font;
			};
			STATICDLL_API virtual ALLEGRO_FONT* GetFont(){
				return font30_;
			};

			STATICDLL_API virtual void SetText(ALLEGRO_USTR *str){
				if(utext_ != NULL)
				{
					al_ustr_free(utext_);
				}
				hasText_ = true;
				utext_ = str;
				text_ = al_cstr_dup(utext_);

			};

			STATICDLL_API virtual ALLEGRO_USTR *GetText(){
				return utext_;
			};
			
			STATICDLL_API int GetFontWidth()
			{
				return al_get_text_width(font30_,text_);
			}
			


			STATICDLL_API void SetId(EnumDLL::STATES newId)
			{
				Id_ = newId;
			}
			STATICDLL_API EnumDLL::STATES GetId()
			{
				return Id_;
			}





			STATICDLL_API virtual void SetObjectImage(Image *image)
			{
				hasImage_ = true;
				image_ = image;
			}

			STATICDLL_API virtual Image *GetObjectImage()
			{
				return image_;
			}
			STATICDLL_API virtual bool GetHasImage()
			{
				return hasImage_;
			}




			STATICDLL_API virtual void UpdateObject(){

			};

			STATICDLL_API virtual void SetColorA(float a){
				chosenColor_.a = a;
			};
			STATICDLL_API virtual void SetColorB(float b){
				chosenColor_.b = b;
			};
			STATICDLL_API virtual void SetColorR(float r){
				chosenColor_.r = r;
			};
			STATICDLL_API virtual void SetColorG(float g){
				chosenColor_.g = g;
			};
			STATICDLL_API virtual void SetColor(ALLEGRO_COLOR color){
				chosenColor_ = color;
			};
			STATICDLL_API virtual ALLEGRO_COLOR GetColor(){
				return chosenColor_;
			};



			//this is how many move speed deltas it does in a frame
			STATICDLL_API virtual void SetMoveSpeed(double ms){
				movespeed_ = ms;
			};
			STATICDLL_API virtual void SetJumpSpeed(double ms){
				jumpspeed_ = ms;
			};

			//This is the fractions of movement it displaces in a frame
			STATICDLL_API virtual void SetMoveSpeedDelta(double ms){
				movespeedDelta_ = ms;
			};

			STATICDLL_API virtual double GetJumpSpeed(){
				return jumpspeed_;
			};
			STATICDLL_API virtual double GetMoveSpeed(){
				return movespeed_;
			};
			STATICDLL_API virtual double GetMoveSpeedDelta(){
				return movespeedDelta_;
			};

			STATICDLL_API virtual void SetClickable(bool clickable){
				clickable_ = clickable;
			};
			
			STATICDLL_API virtual bool GetClickable(){
				return clickable_;
			};










			//Draws the object...Uses the x and y offset from map to draw with displacement
			STATICDLL_API virtual void DrawObject(int xOffset, int yOffset){

				if(hasImage_)
				{
					al_draw_scaled_bitmap(
						image_->GetImage(),
						0, 0, image_->GetWidth(), image_->GetHeight(), 
						currentPositionX_*Constants::TileSize + xOffset, 
						currentPositionY_*Constants::TileSize + yOffset, 
						width_*Constants::TileSize, 
						height_*Constants::TileSize, 
						0
					);
				}
				else
				{
					al_draw_filled_rectangle(
						currentPositionX_*Constants::TileSize + xOffset,
						currentPositionY_*Constants::TileSize + yOffset,
						currentPositionX_*Constants::TileSize + width_*Constants::TileSize + xOffset,
						currentPositionY_*Constants::TileSize + height_*Constants::TileSize + yOffset,
						chosenColor_		
						);
				}
				//This line below was old code reminder that i need to sort the view point translation of objects
				//al_draw_filled_rectangle(tileX_*20 + mapXoffSet*20, tileY_*20 + mapYoffSet*20, tileX_*20 + tileSize + mapXoffSet*20, tileY_*20 + tileSize + mapYoffSet*20, colour_);
			};




			

			//Draw an object without need of translation
			STATICDLL_API virtual void DrawObject(){

				if(hasImage_)
				{
					al_draw_scaled_bitmap(
						image_->GetImage(),
						0, 0, image_->GetWidth(), image_->GetHeight(), 
						currentPositionX_*Constants::TileSize, 
						currentPositionY_*Constants::TileSize, 
						width_*Constants::TileSize, 
						height_*Constants::TileSize, 
						0
					);
				}
				else
				{
					al_draw_filled_rectangle(
						currentPositionX_*Constants::TileSize,
						currentPositionY_*Constants::TileSize,
						currentPositionX_*Constants::TileSize + width_*Constants::TileSize,
						currentPositionY_*Constants::TileSize + height_*Constants::TileSize,
						chosenColor_		
					);
				}
			};

			        

			STATICDLL_API virtual void DrawObjectText(){
				al_draw_textf(font30_, chosenColor_, currentPositionX_, currentPositionY_, ALLEGRO_ALIGN_LEFT, text_);
			};



			//Useing this for editor mode menubar items
			STATICDLL_API virtual void DrawObjectLeftBorder(){
				al_draw_line(
					currentPositionX_, 
					currentPositionY_, 
					currentPositionX_, 
					currentPositionY_ + Constants::TileSize,
					chosenColor_,
					1);
			};
			//Useing this for editor mode menubar items
			STATICDLL_API virtual void DrawObjectRightBorder(){
				al_draw_line(
					currentPositionX_ + GetFontWidth(), 
					currentPositionY_, 
					currentPositionX_ + GetFontWidth(), 
					currentPositionY_ + Constants::TileSize,
					chosenColor_,
					1);
			};








			//Detects If click intersects with the selected text object
			STATICDLL_API bool ClickIntersectsText(int mouseX, int mouseY)
			{
				//Offset the mouse position to the actual coord as the mouseX and mouseY i read in a moded to be offset? by half the tile size for some reason
				mouseX = mouseX + (Constants::TileSize/2);
				mouseY = mouseY + (Constants::TileSize/2);

				if(mouseX >= currentPositionX_ && 
					mouseX < (currentPositionX_ + GetFontWidth()) &&
					mouseY >= currentPositionY_ && 
					mouseY < (currentPositionY_ + height_))
				{
					return true;
				}
				return false;
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
					jumpspeed_,
					movespeed_,
					movespeedDelta_,
					accelerationX_,
					accelerationY_,
					maxAccelerationX_,
					maxAccelerationY_,
					maxVelocityY_
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
					hasImage_;	




			ALLEGRO_USTR *utext_;
			char *text_;


			Image *image_;
			
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
