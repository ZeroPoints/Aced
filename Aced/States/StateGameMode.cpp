#include "StateTemplates.h"




StateGameMode::StateGameMode(ALLEGRO_DISPLAY *display, std::shared_ptr<Settings> &settings, std::shared_ptr<AcedSharedDLL::Map> &currentMap, std::shared_ptr<AcedSharedDLL::AssetLibrary> &assetLibrary) 
	: State(display, (std::shared_ptr<AcedSharedDLL::BaseSettings>)settings, currentMap, assetLibrary) {

	SetId(AcedSharedDLL::STATES::NEW);
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

	player1_ = std::shared_ptr<AcedSharedDLL::Player>(new AcedSharedDLL::Player(GetSettings(), GetMap()));

	player1_->SetGravityY(-9.8);

	for (int i = 0; i < GetAssetLibrary()->GetImageSetDictionary().size(); i++)
	{
		if (GetAssetLibrary()->GetImageSetDictionary()[i]->GetImageSetId() == AcedSharedDLL::IMAGESETS::PLAYERIMAGESET)
		{
			player1_->SetImageBundle(GetAssetLibrary()->GetImageSetDictionary()[i]->GetImageBundleDictionary()[0]);
		}
	}


	SetChosenColor(al_map_rgb_f(1, 1, 1));
	al_start_timer(GetTimer());

}



void StateGameMode::Resume() {
	SetStateDirection(AcedSharedDLL::STATEDIRECTION::NA);
	//SetNextState(NULL);
}



void StateGameMode::KeyPress() {
	if (GetEvent()->type == ALLEGRO_EVENT_KEY_UP)
	{
		switch (GetEvent()->keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
			//this will need to change to pushing a menu ontop instead of popping.
			//as popping cleans current states progress
			SetPopLevel(1);
			SetStateDirection(AcedSharedDLL::STATEDIRECTION::POP);
			break;
		}
	}

	if (player1_->Keypress(GetEvent()) == 1)
	{
	}



}




void StateGameMode::MouseActivity() {


	if (GetEvent()->type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		SetMouseCursorPos(GetEvent()->mouse.x - 10, GetEvent()->mouse.y - 10);
	}




}





void StateGameMode::Update() {


	if (GetEvent()->type == ALLEGRO_EVENT_TIMER)
	{
		GetMap()->Update();




		player1_->Update(GetEvent());












		//Update overlay. Will return with no actions if action state of it is NONE.
		SetRedraw(true);
	}


}



void StateGameMode::Draw() {


	GetMap()->DrawMap();

	player1_->Draw();




	al_draw_rectangle(GetMouseCursorX(), GetMouseCursorY(), GetMouseCursorX() + AcedSharedDLL::Constants::TileSize(), GetMouseCursorY() + AcedSharedDLL::Constants::TileSize(), al_map_rgb_f(0, 0, 0), 2);//1
}






