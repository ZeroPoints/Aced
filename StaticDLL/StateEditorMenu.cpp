#include "StateTemplates.h"
#include "MenuTemplates.h"
#include "State.h"


namespace StaticDLL{



	void StateEditorMenu::InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap){
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



	void StateEditorMenu::KeyPress(){
		//keypress here
		SetKeyPressState(GetMenu()->KeyPress(GetEvent()));
		if(GetKeyPressState() == EnumDLL::STATES::NEW)//new map
		{
			SetStateDirection(EnumDLL::STATEDIRECTION::POPPUSH);
			SetPopLevel(2);
			SetNextState(new StateEditorMode());
		}
		else if(GetKeyPressState() == EnumDLL::STATES::LOAD)//load map
		{

		}
		else if(GetKeyPressState() == EnumDLL::STATES::MAPOPTIONS)//options
		{
			SetStateDirection(EnumDLL::STATEDIRECTION::PUSH);
			SetNextState(new StateMapOptions());
		}
		else if(GetKeyPressState() == EnumDLL::STATES::ABOUT)//about cinematics
		{
			
		}
		else if(GetKeyPressState() == EnumDLL::STATES::MAINMENU)
		{
			SetStateDirection(EnumDLL::STATEDIRECTION::POPTOFIRST);
		}
	}



	void StateEditorMenu::Update(){
		if(GetEvent().type == ALLEGRO_EVENT_TIMER)
		{				
			GetMenu()->CalculateMenuSelectorCubePosition();
			SetRedraw(true);
		}
	}



	void StateEditorMenu::Draw(){
		al_draw_textf(GetFont(), al_map_rgb(255,255,255), 0, 0, ALLEGRO_ALIGN_LEFT, "%f" , GetEvent().timer.timestamp);
		GetMenu()->DrawMenu();
		GetMenu()->DrawMenuSelectorCube();
	}



	void StateEditorMenu::Resume(){
		SetStateDirection(EnumDLL::STATEDIRECTION::NA);
		SetNextState(NULL);
	}



	void StateEditorMenu::CleanUp(){



	}
}