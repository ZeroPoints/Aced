#include "StateTemplates.h"
#include "MenuTemplates.h"
#include "State.h"


namespace StaticDLL{




	/*
	State Editor Main Menu
	This is the main menu of the whole Editing mode Application
	*/
	void StateEditorMainMenu::InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap){
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

		SetMap(currentMap);

		SetMenu(new MenuEditorMain(settings));
		al_start_timer(GetTimer());
	}


	void StateEditorMainMenu::Resume(){
		SetStateDirection(EnumDLL::STATEDIRECTION::NA);
		SetNextState(NULL);
		//Resize menus
		//I dont have a resize menu type function atm
		//i could just destroy and remake
		//But then my remake doesnt have adjustments based on screen size as of yet
	}




	void StateEditorMainMenu::KeyPress(){
		//keypress here
		SetKeyPressState(GetMenu()->KeyPress(GetEvent()));
		if(GetKeyPressState() == EnumDLL::STATES::NEW)//new map
		{
			GetMap()->ResetMap();
			SetStateDirection(EnumDLL::STATEDIRECTION::PUSH);
			SetNextState(new StateEditorMode());
		}
		else if(GetKeyPressState() == EnumDLL::STATES::LOAD)//load map
		{
			GetMap()->ResetMap();
			GetMap()->LoadMapDialog();
			SetStateDirection(EnumDLL::STATEDIRECTION::PUSH);
			SetNextState(new StateEditorMode());
		}
		else if(GetKeyPressState() == EnumDLL::STATES::OPTIONS)
		{
			SetStateDirection(EnumDLL::STATEDIRECTION::PUSH);
			SetNextState(new StateOptions());
		}
		else if(GetKeyPressState() == EnumDLL::STATES::QUIT)
		{
			SetRunning(false);
		}
	}



	void StateEditorMainMenu::Update(){
		if(GetEvent()->type == ALLEGRO_EVENT_TIMER)
		{				
			GetMenu()->CalculateMenuSelectorCubePosition();
			SetRedraw(true);
		}
	}



	void StateEditorMainMenu::Draw(){
		GetMenu()->DrawMenu();
		GetMenu()->DrawMenuSelectorCube();
	}



}