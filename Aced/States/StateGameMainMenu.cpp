#include "StateTemplates.h"




/*
State Editor Main Menu
This is the main menu of the whole Editing mode Application
*/

StateGameMainMenu::StateGameMainMenu(ALLEGRO_DISPLAY *display, Settings *settings, AcedSharedDLL::Map *currentMap, AcedSharedDLL::AssetLibrary *assetLibrary) : State(display, settings, currentMap, assetLibrary) {
	SetMenu(new MenuGameMain(settings));


	SetId(AcedSharedDLL::STATES::EDITORMAINMENU);
	SetEventQueue(NULL);
	SetRedraw(true);
	SetDone(false);
	SetRunning(true);
	SetKeyPressReturnVal(AcedSharedDLL::STATES::DEFAULT);
	SetFont(al_load_font("arial.ttf", AcedSharedDLL::Constants::TileSize(), 0));
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
	al_start_timer(GetTimer());
}


void StateGameMainMenu::Resume() {
	SetStateDirection(AcedSharedDLL::STATEDIRECTION::NA);
	SetNextState(NULL);
	//Resize menus
	//I dont have a resize menu type function atm
	//i could just destroy and remake
	//But then my remake doesnt have adjustments based on screen size as of yet
}




void StateGameMainMenu::KeyPress() {
	//keypress here
	SetKeyPressState(GetMenu()->KeyPress(GetEvent()));
	if (GetKeyPressState() == AcedSharedDLL::STATES::NEW)//new map
	{
		GetMap()->ResetMap();
		SetStateDirection(AcedSharedDLL::STATEDIRECTION::PUSH);
		SetNextState(new StateGameMode(GetDisplay(), (Settings*)GetSettings(), GetMap(), GetAssetLibrary()));
	}
	else if (GetKeyPressState() == AcedSharedDLL::STATES::LOAD)//load map
	{
		GetMap()->ResetMap();
		GetMap()->LoadMapDialog(true);
		SetStateDirection(AcedSharedDLL::STATEDIRECTION::PUSH);
		SetNextState(new StateGameMode(GetDisplay(), (Settings*)GetSettings(), GetMap(), GetAssetLibrary()));
	}
	else if (GetKeyPressState() == AcedSharedDLL::STATES::EDITORMAINMENU)//load map
	{
		SetStateDirection(AcedSharedDLL::STATEDIRECTION::PUSH);
		SetNextState(new StateEditorMainMenu(GetDisplay(), (Settings*)GetSettings(), GetMap(), GetAssetLibrary()));
	}
	else if (GetKeyPressState() == AcedSharedDLL::STATES::OPTIONS)
	{
		SetStateDirection(AcedSharedDLL::STATEDIRECTION::PUSH);
		SetNextState(new StateOptions(GetDisplay(), (Settings*)GetSettings(), GetMap(), GetAssetLibrary()));
	}
	else if (GetKeyPressState() == AcedSharedDLL::STATES::QUIT)
	{
		SetRunning(false);
	}
}



void StateGameMainMenu::Update() {
	if (GetEvent()->type == ALLEGRO_EVENT_TIMER)
	{
		GetMenu()->CalculateMenuSelectorCubePosition();
		SetRedraw(true);
	}
}



void StateGameMainMenu::Draw() {
	GetMenu()->DrawMenu();
	GetMenu()->DrawMenuSelectorCube();
	//al_draw_bitmap(img, 5,5,0);
}



