#include "StateTemplates.h"
#include "../Menu/MenuTemplates.h"
#include "State.h"


namespace StaticDLL{



	void StateMapOptions::InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap, AssetLibrary *assetLibrary){
		SetAssetLibrary(assetLibrary);
		
		SetDisplay(display);
		SetSettings(settings);
		SetId(EnumDLL::STATES::MAPOPTIONS);
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
		SetMenu(new MenuMapOptions(settings, currentMap));
		al_start_timer(GetTimer());
	}



	void StateMapOptions::KeyPress(){
		//keypress here
		SetKeyPressState(GetMenu()->KeyPress(GetEvent()));
		if(GetKeyPressState() == EnumDLL::STATES::SAVE)//new map
		{
			//Go through each menu item. 
			for(int i = 0; i < GetMenu()->GetMenuItems().size(); i++)
			{
				if(GetMenu()->GetMenuItems()[i]->GetOptionId() == EnumDLL::OPTIONTYPES::WIDTHOPTION)
				{
					auto *u = GetMenu()->GetMenuItems()[i]->GetMenuItemProperty();
					auto *s = al_cstr_dup(u);
					auto v = atoi(s);
					if(v > 0)
					{
						GetMap()->SetMapWidth(v);
					}
				}
				else if(GetMenu()->GetMenuItems()[i]->GetOptionId() == EnumDLL::OPTIONTYPES::HEIGHTOPTION)
				{
					auto *u = GetMenu()->GetMenuItems()[i]->GetMenuItemProperty();
					auto *s = al_cstr_dup(u);
					auto v = atoi(s);
					if(v > 0)
					{
						GetMap()->SetMapHeight(v);
					}
				}
			}



			SetStateDirection(EnumDLL::STATEDIRECTION::POP);
			SetPopLevel(1);
		}
		else if(GetKeyPressState() == EnumDLL::STATES::RETURN)//load map
		{
			SetStateDirection(EnumDLL::STATEDIRECTION::POP);
			SetPopLevel(1);
		}
	}



	void StateMapOptions::Update(){
		if(GetEvent()->type == ALLEGRO_EVENT_TIMER)
		{				
			GetMenu()->CalculateMenuSelectorCubePosition();
			SetRedraw(true);
		}
	}



	void StateMapOptions::Draw(){
		GetMenu()->DrawMenu();
		GetMenu()->DrawMenuSelectorCube();
	}
}