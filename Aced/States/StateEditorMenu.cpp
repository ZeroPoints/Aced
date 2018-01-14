#include "StateTemplates.h"



StateEditorMenu::StateEditorMenu(ALLEGRO_DISPLAY *display, std::shared_ptr<Settings> &settings, std::shared_ptr<AcedSharedDLL::Map> &currentMap, std::shared_ptr<AcedSharedDLL::AssetLibrary> &assetLibrary) 
	: State(display, (std::shared_ptr<AcedSharedDLL::BaseSettings>)settings, currentMap, assetLibrary) {

	SetId(AcedSharedDLL::STATES::EDITORMAINMENU);
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
	SetMenu(std::shared_ptr<AcedSharedDLL::Menu>(new MenuEditor(settings)));

	al_start_timer(GetTimer());
}






void StateEditorMenu::Resume() {
	SetStateDirection(AcedSharedDLL::STATEDIRECTION::NA);
	//SetNextState(NULL);
	//Resize menus
	//I dont have a resize menu type function atm
	//i could just destroy and remake
	//But then my remake doesnt have adjustments based on screen size as of yet
}



void StateEditorMenu::KeyPress() {
	//keypress here
	SetKeyPressState(GetMenu()->KeyPress(GetEvent()));
	if (GetKeyPressState() == AcedSharedDLL::STATES::NEW)//new map
	{
		GetMap()->ResetMap();
		SetStateDirection(AcedSharedDLL::STATEDIRECTION::POPPUSH);
		SetPopLevel(2);
		SetNextState(std::shared_ptr<State>(new StateEditorMode(GetDisplay(), std::dynamic_pointer_cast<Settings>(GetSettings()), GetMap(), GetAssetLibrary())));
		//New create new map instead of going to use what we were using before
	}
	else if (GetKeyPressState() == AcedSharedDLL::STATES::LOAD)//load map
	{
		GetMap()->ResetMap();
		GetMap()->LoadMapDialog(false);
		SetStateDirection(AcedSharedDLL::STATEDIRECTION::POPPUSH);
		SetPopLevel(2);
		SetNextState(std::shared_ptr<State>(new StateEditorMode(GetDisplay(), std::dynamic_pointer_cast<Settings>(GetSettings()), GetMap(), GetAssetLibrary())));
	}
	else if (GetKeyPressState() == AcedSharedDLL::STATES::SAVE)//save map
	{
		GetMap()->SaveMapDialog();
	}
	else if (GetKeyPressState() == AcedSharedDLL::STATES::MAPOPTIONS)//options
	{
		SetStateDirection(AcedSharedDLL::STATEDIRECTION::PUSH);
		SetNextState(std::shared_ptr<State>(new StateMapOptions(GetDisplay(), std::dynamic_pointer_cast<Settings>(GetSettings()), GetMap(), GetAssetLibrary())));
	}
	else if (GetKeyPressState() == AcedSharedDLL::STATES::OPTIONS)
	{
		SetStateDirection(AcedSharedDLL::STATEDIRECTION::PUSH);
		SetNextState(std::shared_ptr<State>(new StateOptions(GetDisplay(), std::dynamic_pointer_cast<Settings>(GetSettings()), GetMap(), GetAssetLibrary())));
	}
	else if (GetKeyPressState() == AcedSharedDLL::STATES::MAINMENU)
	{
		SetStateDirection(AcedSharedDLL::STATEDIRECTION::POPTOFIRST);
	}
	else if (GetKeyPressState() == AcedSharedDLL::STATES::RETURN)
	{
		SetStateDirection(AcedSharedDLL::STATEDIRECTION::POP);
		SetPopLevel(1);
	}
}



void StateEditorMenu::Update() {
	if (GetEvent()->type == ALLEGRO_EVENT_TIMER)
	{
		GetMenu()->CalculateMenuSelectorCubePosition();
		SetRedraw(true);
	}
}



void StateEditorMenu::Draw() {
	GetMenu()->DrawMenu();
	GetMenu()->DrawMenuSelectorCube();
}





void StateEditorMenu::CleanUp() {



}
