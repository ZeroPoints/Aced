#ifndef STATE_H
#define STATE_H

#define ALLEGRO_NO_MAGIC_MAIN


#include <allegro5\allegro.h>
#include <vector>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "../Static/Definitions.h"
#include "../Menu/Menu.h"
#include "../Config/BaseSettings.h"
#include "../Config/AssetLibrary.h"
#include "../EditorOverLay/EditorOverLayController.h"
#include "../World/Tile.h"
//#include "../Menu/MenuTemplates.h"
#include "../LivingEntity/Player.h"
#include "../World/Map.h"




#ifdef ACEDSHAREDDLL_EXPORTS
#define ACEDSHAREDDLL_API __declspec(dllexport)
#else
#define ACEDSHAREDDLL_API __declspec(dllimport)
#endif


namespace AcedSharedDLL {
	//Base class for states to inherit from
	//This is the driving structure for this projects state management system
	class State
	{
	public:

		ACEDSHAREDDLL_API State(ALLEGRO_DISPLAY *display, std::shared_ptr<BaseSettings> &settings, std::shared_ptr<Map> &currentMap, std::shared_ptr<AssetLibrary> &assetLibrary);;


		ACEDSHAREDDLL_API virtual ~State();




		//-----------------------------------------------------------------------------------------------------

		//Gets




		ACEDSHAREDDLL_API virtual STATES GetId();

		ACEDSHAREDDLL_API virtual STATES GetKeyPressState();

		ACEDSHAREDDLL_API virtual bool GetRedraw();

		ACEDSHAREDDLL_API virtual bool GetDone();



		ACEDSHAREDDLL_API virtual ALLEGRO_TIMER* GetTimer();

		ACEDSHAREDDLL_API virtual ALLEGRO_EVENT_QUEUE* GetEventQueue();

		ACEDSHAREDDLL_API virtual std::shared_ptr<Map> &GetMap();
		ACEDSHAREDDLL_API virtual ALLEGRO_DISPLAY* GetDisplay();

		ACEDSHAREDDLL_API virtual bool GetRightMouseDown();

		ACEDSHAREDDLL_API virtual bool GetLeftMouseDown();

		ACEDSHAREDDLL_API virtual int GetMouseCursorX();

		ACEDSHAREDDLL_API virtual int GetMouseCursorY();



		ACEDSHAREDDLL_API virtual int GetRightMouseX();

		ACEDSHAREDDLL_API virtual int GetRightMouseY();


		ACEDSHAREDDLL_API virtual bool GetPlayerSelected();

		ACEDSHAREDDLL_API virtual ALLEGRO_COLOR GetChosenColor();

		ACEDSHAREDDLL_API virtual ALLEGRO_EVENT *GetEvent();

		ACEDSHAREDDLL_API virtual bool GetRunning();

		ACEDSHAREDDLL_API virtual std::shared_ptr<BaseSettings> &GetSettings();
		ACEDSHAREDDLL_API virtual std::shared_ptr<Menu> &GetMenu();

		ACEDSHAREDDLL_API virtual STATEDIRECTION GetStateDirection();


		ACEDSHAREDDLL_API virtual std::shared_ptr<State> &GetNextState();

		ACEDSHAREDDLL_API virtual int GetPopLevel();






		//-----------------------------------------------------------------------------------------------------

		//Sets



		ACEDSHAREDDLL_API virtual void SetId(STATES newId);

		ACEDSHAREDDLL_API virtual void SetKeyPressState(STATES keyPress);

		ACEDSHAREDDLL_API virtual void SetKeyPressReturnVal(STATES val);

		ACEDSHAREDDLL_API virtual void SetRedraw(bool flag);

		ACEDSHAREDDLL_API virtual void SetDone(bool flag);

		ACEDSHAREDDLL_API virtual void SetRunning(bool flag);



		ACEDSHAREDDLL_API virtual void SetTimer(ALLEGRO_TIMER* currentTimer);

		ACEDSHAREDDLL_API virtual void SetEventQueue(ALLEGRO_EVENT_QUEUE* eventQueue);

		ACEDSHAREDDLL_API virtual void SetMap(std::shared_ptr<Map> &currentMap);

		ACEDSHAREDDLL_API virtual void SetAssetLibrary(std::shared_ptr<AssetLibrary> &assetLibrary);

		ACEDSHAREDDLL_API virtual std::shared_ptr<AssetLibrary> &GetAssetLibrary();

		ACEDSHAREDDLL_API virtual void SetDisplay(ALLEGRO_DISPLAY* currentDisplay);

		ACEDSHAREDDLL_API virtual void SetSettings(std::shared_ptr<BaseSettings> &settings);

		ACEDSHAREDDLL_API virtual void SetRightMouseDown(bool rightMouseDown);

		ACEDSHAREDDLL_API virtual void SetLeftMouseDown(bool leftMouseDown);

		ACEDSHAREDDLL_API virtual void SetMouseCursorPos(int x, int y);

		ACEDSHAREDDLL_API virtual void SetRightMousePos(int x, int y);

		ACEDSHAREDDLL_API virtual void SetRightMouseX(int x);

		ACEDSHAREDDLL_API virtual void SetRightMouseY(int y);

		ACEDSHAREDDLL_API virtual void SetPlayerSelected(bool selected);

		ACEDSHAREDDLL_API virtual void SetChosenColor(ALLEGRO_COLOR color);

		ACEDSHAREDDLL_API void SetMenu(std::shared_ptr<Menu> &menu);

		ACEDSHAREDDLL_API virtual void SetEvent(ALLEGRO_EVENT *event);

		ACEDSHAREDDLL_API virtual void SetStateDirection(STATEDIRECTION direction);

		ACEDSHAREDDLL_API virtual void SetNextState(std::shared_ptr<State> &state);

		ACEDSHAREDDLL_API virtual void SetPopLevel(int level);








		//-----------------------------------------------------------------------------------------------------

		//Draws


		ACEDSHAREDDLL_API virtual void Draw();






		//-----------------------------------------------------------------------------------------------------

		//Misc


		//key press probs goes in update
		ACEDSHAREDDLL_API virtual void KeyPress();
		ACEDSHAREDDLL_API virtual void MouseActivity();
		ACEDSHAREDDLL_API virtual void Update();
		ACEDSHAREDDLL_API virtual void Pause();
		//On resume maybe resize or graphics stuff? menus? overlay?
		ACEDSHAREDDLL_API virtual void Resume();
		ACEDSHAREDDLL_API virtual void CleanUp();






	private:
		ALLEGRO_COLOR chosenColor_;
		ALLEGRO_DISPLAY *display_;
		ALLEGRO_EVENT *event_;
		ALLEGRO_EVENT_QUEUE *eventQueue_;

		ALLEGRO_TIMER *timer;
		//state pair for editorengine.cpp to push pop state accordingly if need be
		STATEDIRECTION stateDirection_;
		STATES Id_, keyPressState_, keyPressReturnVal_;//keyPressReturnVal_ unused
		std::shared_ptr<AssetLibrary> assetLibrary_;
		std::shared_ptr<Map> currentMap_;
		std::shared_ptr<Menu> menu_;
		std::shared_ptr<BaseSettings> settings_;
		std::shared_ptr<State> nextState_;
		bool redraw_, done_, running_, rightMouseDown_, leftmousedown_, playerSelected_, hasMenu_;
		int mouseCursorX_, mouseCursorY_;
		int popLevel_;
		int rightMouseX_, rightMouseY_;


	};
}
#endif
