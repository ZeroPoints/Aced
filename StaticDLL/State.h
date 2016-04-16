#ifndef STATE_H
#define STATE_H

#define ALLEGRO_NO_MAGIC_MAIN


#include <allegro5\allegro.h>
#include <vector>
#include "Player.h"
#include "Map.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "Definitions.h"
#include "Menu.h"
#include "Settings.h"
#include "ImageLoader.h"


#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL{
	//Base class for states to inherit from
	//This is the driving structure for this projects state management system
	class State
	{
		public:
		
			STATICDLL_API State(){
				fprintf(stderr,"A State Created\n");
			}


			STATICDLL_API virtual ~State(){
				al_destroy_event_queue(eventQueue_);
				al_destroy_font(font30_);
				al_destroy_timer(timer);
				delete menu_;

				fprintf(stderr,"A State Destructed\n");
				return;
			}


			STATICDLL_API virtual void InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap, ImageLoader *imageLoader){
				return;
			};

			//key press probs goes in update
			STATICDLL_API virtual void KeyPress(){
				return;
			};
			STATICDLL_API virtual void MouseActivity(){
				return;
			};
			STATICDLL_API virtual void Update(){
				return;
			};



			STATICDLL_API virtual void Draw(){
				return;
			};
			STATICDLL_API virtual void Pause(){
				return;
			};

			//On resume maybe resize or graphics stuff? menus? overlay?
			STATICDLL_API virtual void Resume(){
				return;
			};
			STATICDLL_API virtual void CleanUp(){
				return;
			};

			STATICDLL_API virtual EnumDLL::STATES GetId()
			{
				return Id_;
			}
			STATICDLL_API virtual EnumDLL::STATES GetKeyPressState()
			{
				return keyPressState_;
			}
			STATICDLL_API virtual bool GetRedraw()
			{
				return redraw_;
			}
			STATICDLL_API virtual bool GetDone()
			{
				return done_;
			}
			STATICDLL_API virtual ALLEGRO_FONT* GetFont()
			{
				return font30_;
			}
			STATICDLL_API virtual ALLEGRO_TIMER* GetTimer()
			{
				return timer;
			}
			STATICDLL_API virtual ALLEGRO_EVENT_QUEUE* GetEventQueue()
			{
				return eventQueue_;
			}
		
			STATICDLL_API virtual Map* GetMap()
			{
				return currentMap_;
			}
			STATICDLL_API virtual ALLEGRO_DISPLAY* GetDisplay()
			{
				return display_;
			}

			STATICDLL_API virtual bool GetRightMouseDown(){
				return rightMouseDown_;
			}

			STATICDLL_API virtual bool GetLeftMouseDown(){
				return leftmousedown_;
			}

			STATICDLL_API virtual int GetMouseCursorX(){
				return mouseCursorX_;
			}
		
			STATICDLL_API virtual int GetMouseCursorY(){
				return mouseCursorY_;
			}

			
		
			STATICDLL_API virtual int GetRightMouseX(){
				return rightMouseX_;
			}

			STATICDLL_API virtual int GetRightMouseY(){
				return rightMouseY_;
			}

		
			STATICDLL_API virtual bool GetPlayerSelected(){
				return playerSelected_;
			}

			STATICDLL_API virtual ALLEGRO_COLOR GetChosenColor(){
				return chosenColor_;
			}

			STATICDLL_API virtual ALLEGRO_EVENT *GetEvent(){
				return event_;
			}

			STATICDLL_API virtual bool GetRunning(){
				return running_;
			}



			STATICDLL_API virtual void SetId(EnumDLL::STATES newId)
			{
				Id_ = newId;
			}

			STATICDLL_API virtual void SetKeyPressState(EnumDLL::STATES keyPress){
				keyPressState_ = keyPress;
			}


			////keyPressReturnVal_ unused
			STATICDLL_API virtual void SetKeyPressReturnVal(EnumDLL::STATES val){
				keyPressReturnVal_ = val;
			}

			STATICDLL_API virtual void SetRedraw(bool flag){
				redraw_ = flag;
			}

			STATICDLL_API virtual void SetDone(bool flag){
				done_ = flag;
			}

			STATICDLL_API virtual void SetRunning(bool flag){
				running_ = flag;
			}

			STATICDLL_API virtual void SetFont(ALLEGRO_FONT* currentFont){
				font30_ = currentFont;
			}

			STATICDLL_API virtual void SetTimer(ALLEGRO_TIMER* currentTimer){
				timer = currentTimer;
			}

			STATICDLL_API virtual void SetEventQueue(ALLEGRO_EVENT_QUEUE* eventQueue){
				eventQueue_ = eventQueue;
			}


			STATICDLL_API virtual void SetMap(Map* currentMap){
				currentMap_ = currentMap;
			}

			STATICDLL_API virtual void SetImageLoader(ImageLoader* imageLoader){
				imageLoader_ = imageLoader;
			}
			STATICDLL_API virtual ImageLoader* GetImageLoader(){
				return imageLoader_;
			}
			STATICDLL_API virtual void SetDisplay(ALLEGRO_DISPLAY* currentDisplay){
				display_ = currentDisplay;
			}
			STATICDLL_API virtual void SetSettings(Settings* settings){
				settings_ = settings;
			}
			STATICDLL_API virtual Settings* GetSettings(){
				return settings_;
			}



			STATICDLL_API virtual void SetRightMouseDown(bool rightMouseDown){
				rightMouseDown_ = rightMouseDown;
			}

			STATICDLL_API virtual void SetLeftMouseDown(bool leftMouseDown){
				leftmousedown_ = leftMouseDown;
			}

		
			STATICDLL_API virtual void SetMouseCursorPos(int x, int y){
				mouseCursorX_ = x;
				mouseCursorY_ = y;
			}




			STATICDLL_API virtual void SetRightMousePos(int x, int y){
				rightMouseX_ = x;
				rightMouseY_ = y;
			}

		
			STATICDLL_API virtual void SetRightMouseX(int x){
				rightMouseX_ = x;
			}

			STATICDLL_API virtual void SetRightMouseY(int y){
				rightMouseY_ = y;
			}

			STATICDLL_API virtual void SetPlayerSelected(bool selected){
				playerSelected_ = selected;
			}

			STATICDLL_API virtual void SetChosenColor(ALLEGRO_COLOR color){
				chosenColor_ = color;
			}

			STATICDLL_API virtual Menu *GetMenu(){
				return menu_;
			}

			STATICDLL_API void SetMenu(Menu *menu){
				menu_ = menu;
			}


			STATICDLL_API virtual void SetEvent(ALLEGRO_EVENT *event){
				event_ = event;
			}

			STATICDLL_API virtual void SetStateDirection(EnumDLL::STATEDIRECTION direction){
				stateDirection_ = direction;
			}

			STATICDLL_API virtual EnumDLL::STATEDIRECTION GetStateDirection(){
				return stateDirection_;
			}

			STATICDLL_API virtual void SetNextState(State* state){
				nextState_ = state;
			}

			STATICDLL_API virtual State* GetNextState(){
				return nextState_;
			}

			STATICDLL_API virtual int GetPopLevel(){
				return popLevel_;
			}

			STATICDLL_API virtual void SetPopLevel(int level = 1){
				popLevel_ = level;
			}

		private:

			//state pair for editorengine.cpp to push pop state accordingly if need be
			EnumDLL::STATEDIRECTION stateDirection_;
			State* nextState_;
			int popLevel_;

			int mouseCursorX_, mouseCursorY_;
			int rightMouseX_, rightMouseY_;
			EnumDLL::STATES Id_, keyPressState_, keyPressReturnVal_;//keyPressReturnVal_ unused
			bool redraw_, done_, running_, rightMouseDown_, leftmousedown_,playerSelected_;	
			ALLEGRO_FONT *font30_;
			ALLEGRO_TIMER *timer;
			ALLEGRO_EVENT_QUEUE *eventQueue_;
			ALLEGRO_EVENT *event_;
			Menu *menu_;
			Settings *settings_;
			Map *currentMap_;
			ImageLoader *imageLoader_;
			ALLEGRO_DISPLAY *display_;
			ALLEGRO_COLOR chosenColor_;
	};
}
#endif
