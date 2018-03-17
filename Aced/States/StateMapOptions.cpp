#include "StateTemplates.h"





StateMapOptions::StateMapOptions(ALLEGRO_DISPLAY *display, std::shared_ptr<Settings> &settings, std::shared_ptr<AcedSharedDLL::Map> &currentMap, std::shared_ptr<AcedSharedDLL::AssetLibrary> &assetLibrary) 
	: State(display, (std::shared_ptr<AcedSharedDLL::BaseSettings>)settings, currentMap, assetLibrary) {

	SetId(AcedSharedDLL::STATES::MAPOPTIONS);
	SetEventQueue(NULL);
	SetRedraw(true);
	SetDone(false);
	SetRunning(true);
	SetKeyPressReturnVal(AcedSharedDLL::STATES::DEFAULT);
	//SetFont(al_load_font("arial.ttf", AcedSharedDLL::Constants::TileSize(), 0));
	SetTimer(al_create_timer(1.0 / 60));
	SetEventQueue(al_create_event_queue());
	SetStateDirection(AcedSharedDLL::STATEDIRECTION::NA);


	al_register_event_source(GetEventQueue(), al_get_keyboard_event_source());
	al_register_event_source(GetEventQueue(), al_get_mouse_event_source());
	al_register_event_source(GetEventQueue(), al_get_display_event_source(display));
	al_register_event_source(GetEventQueue(), al_get_timer_event_source(GetTimer()));
	SetMouseCursorPos(0, 0);
	SetRightMousePos(0, 0);
	SetRightMouseDown(false);
	SetLeftMouseDown(false);
	SetPlayerSelected(false);
	SetChosenColor(al_map_rgb_f(0, 0.3, 0.5));
	SetMenu(std::shared_ptr<AcedSharedDLL::Menu>(new MenuMapOptions(settings, currentMap)));
	al_start_timer(GetTimer());
}





void StateMapOptions::KeyPress() {
	//keypress here
	SetKeyPressState(GetMenu()->KeyPress(GetEvent()));
	if (GetKeyPressState() == AcedSharedDLL::STATES::SAVE)//new map
	{
		//Go through each menu item. 
		for (int i = 0; i < GetMenu()->GetMenuItems().size(); i++)
		{
			if (GetMenu()->GetMenuItems()[i]->GetOptionId() == AcedSharedDLL::OPTIONTYPES::WIDTHOPTION)
			{
				auto *u = GetMenu()->GetMenuItems()[i]->GetMenuItemPropertyU();
				auto *s = al_cstr_dup(u);
				auto v = atoi(s);
				if (v > 0)
				{
					GetMap()->SetMapWidth(v);
				}
			}
			else if (GetMenu()->GetMenuItems()[i]->GetOptionId() == AcedSharedDLL::OPTIONTYPES::HEIGHTOPTION)
			{
				auto *u = GetMenu()->GetMenuItems()[i]->GetMenuItemPropertyU();
				auto *s = al_cstr_dup(u);
				auto v = atoi(s);
				if (v > 0)
				{
					GetMap()->SetMapHeight(v);
				}
			}
		}



		SetStateDirection(AcedSharedDLL::STATEDIRECTION::POP);
		SetPopLevel(1);
	}
	else if (GetKeyPressState() == AcedSharedDLL::STATES::RETURN)//load map
	{
		SetStateDirection(AcedSharedDLL::STATEDIRECTION::POP);
		SetPopLevel(1);
	}
}



void StateMapOptions::Update() {
	if (GetEvent()->type == ALLEGRO_EVENT_TIMER)
	{
		GetMenu()->CalculateMenuSelectorCubePosition();
		SetRedraw(true);
	}
}



void StateMapOptions::Draw() {
	GetMenu()->DrawMenu(GetSettings()->GetFont30());
	GetMenu()->DrawMenuSelectorCube();
}



