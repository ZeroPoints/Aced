#include "StateTemplates.h"
#include "../Menu/MenuTemplates.h"
#include "State.h"


namespace StaticDLL{



	void StateEditorMenu::InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap, AssetLibrary *assetLibrary){
		SetAssetLibrary(assetLibrary);
		
		SetDisplay(display);
		SetSettings(settings);
		SetId(EnumDLL::STATES::EDITORMAINMENU);
		SetEventQueue(NULL);
		SetRedraw(true);
		SetDone(false);
		SetRunning(true);
		SetKeyPressReturnVal(EnumDLL::STATES::DEFAULT);
		SetFont(al_load_font("arial.ttf", 20, 0));
		SetTimer(al_create_timer(1.0/60));
		SetEventQueue(al_create_event_queue());
		SetStateDirection(EnumDLL::STATEDIRECTION::NA);


		al_register_event_source(GetEventQueue(), al_get_keyboard_event_source());
		al_register_event_source(GetEventQueue(), al_get_mouse_event_source());
		al_register_event_source(GetEventQueue(), al_get_display_event_source(GetDisplay()));
		al_register_event_source(GetEventQueue(), al_get_timer_event_source(GetTimer()));
		SetMouseCursorPos(0,0);
		SetRightMousePos(0,0);
		SetRightMouseDown(false);
		SetLeftMouseDown(false);
		SetPlayerSelected(false);
		SetChosenColor(al_map_rgb_f(0,0.3,0.5));
		SetMenu(new MenuEditor(settings));
		SetMap(currentMap);

		al_start_timer(GetTimer());
	}

	void StateEditorMenu::Resume(){
		SetStateDirection(EnumDLL::STATEDIRECTION::NA);
		SetNextState(NULL);
		//Resize menus
		//I dont have a resize menu type function atm
		//i could just destroy and remake
		//But then my remake doesnt have adjustments based on screen size as of yet
	}



	void StateEditorMenu::KeyPress(){
		//keypress here
		SetKeyPressState(GetMenu()->KeyPress(GetEvent()));
		if(GetKeyPressState() == EnumDLL::STATES::NEW)//new map
		{
			GetMap()->ResetMap();
			SetStateDirection(EnumDLL::STATEDIRECTION::POPPUSH);
			SetPopLevel(2);
			SetNextState(new StateEditorMode());
			//New create new map instead of going to use what we were using before
		}
		else if(GetKeyPressState() == EnumDLL::STATES::LOAD)//load map
		{
			GetMap()->ResetMap();
			GetMap()->LoadMapDialog();
			SetStateDirection(EnumDLL::STATEDIRECTION::POPPUSH);
			SetPopLevel(2);
			SetNextState(new StateEditorMode());
		}
		else if(GetKeyPressState() == EnumDLL::STATES::SAVE)//save map
		{
			GetMap()->SaveMapDialog();
		}
		else if(GetKeyPressState() == EnumDLL::STATES::MAPOPTIONS)//options
		{
			SetStateDirection(EnumDLL::STATEDIRECTION::PUSH);
			SetNextState(new StateMapOptions());
		}
		else if(GetKeyPressState() == EnumDLL::STATES::OPTIONS)
		{
			SetStateDirection(EnumDLL::STATEDIRECTION::PUSH);
			SetNextState(new StateOptions());
		}
		else if(GetKeyPressState() == EnumDLL::STATES::MAINMENU)
		{
			SetStateDirection(EnumDLL::STATEDIRECTION::POPTOFIRST);
		}
		else if(GetKeyPressState() == EnumDLL::STATES::RETURN)
		{
			SetStateDirection(EnumDLL::STATEDIRECTION::POP);
			SetPopLevel(1);
		}
	}



	void StateEditorMenu::Update(){
		if(GetEvent()->type == ALLEGRO_EVENT_TIMER)
		{				
			GetMenu()->CalculateMenuSelectorCubePosition();
			SetRedraw(true);
		}
	}



	void StateEditorMenu::Draw(){
		GetMenu()->DrawMenu();
		GetMenu()->DrawMenuSelectorCube();
	}





	void StateEditorMenu::CleanUp(){



	}
}