#include "StateTemplates.h"




StateEditorMode::StateEditorMode(ALLEGRO_DISPLAY *display, std::shared_ptr<Settings> &settings, std::shared_ptr<AcedSharedDLL::Map> &currentMap, std::shared_ptr<AcedSharedDLL::AssetLibrary> &assetLibrary) 
	: State(display, (std::shared_ptr<AcedSharedDLL::BaseSettings>)settings, currentMap, assetLibrary) {

	SetId(AcedSharedDLL::STATES::EDITORMODE);
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

	editorOverLayController_ = std::shared_ptr<AcedSharedDLL::EditorOverLayController>(new AcedSharedDLL::EditorOverLayController((std::shared_ptr<AcedSharedDLL::BaseSettings>)settings, GetAssetLibrary()));

	SetChosenColor(al_map_rgb_f(1, 1, 1));
	al_start_timer(GetTimer());
}





void StateEditorMode::Resume() {
	editorOverLayController_->Resize();
	SetStateDirection(AcedSharedDLL::STATEDIRECTION::NA);
	//SetNextState(NULL);

	//Resize menus
	//I dont have a resize menu type function atm
	//i could just destroy and remake
	//But then my remake doesnt have adjustments based on screen size as of yet
}



void StateEditorMode::KeyPress() {
	if (GetEvent()->type == ALLEGRO_EVENT_KEY_UP)
	{
		switch (GetEvent()->keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
			SetStateDirection(AcedSharedDLL::STATEDIRECTION::PUSH);
			SetNextState(std::shared_ptr<State>(new StateEditorMenu(GetDisplay(), std::dynamic_pointer_cast<Settings>(GetSettings()), GetMap(), GetAssetLibrary())));
			break;
		}
	}
	editorOverLayController_->KeyBoardActivity(GetEvent());
}




void StateEditorMode::MouseActivity() {


	if (GetEvent()->type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		SetMouseCursorPos(GetEvent()->mouse.x - 10, GetEvent()->mouse.y - 10);
	}


	//If the editor overlay didnt take control of mouse activity let editor mode handle it
	if (!editorOverLayController_->MouseActivity(GetEvent(), GetMouseCursorX(), GetMouseCursorY()))
	{
		EditorModeMouseActivity();
	}
	else
	{
		selectedItemBase_ = editorOverLayController_->GetSelectedObject();
	}


}



void StateEditorMode::EditorModeMouseActivity()
{
	if (GetEvent()->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		switch (GetEvent()->mouse.button)
		{
		case 1:
			SetLeftMouseDown(true);
			break;
		case 2:
			SetRightMouseDown(true);
			SetRightMousePos(GetMouseCursorX(), GetMouseCursorY());
			GetMap()->SetOldMapXOffset(GetMap()->GetMapXOffset());
			GetMap()->SetOldMapYOffset(GetMap()->GetMapYOffset());

			break;
		}
	}
	if (GetEvent()->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		switch (GetEvent()->mouse.button)
		{
		case 1:
			SetLeftMouseDown(false);
			break;
		case 2:
			SetRightMouseDown(false);
			break;
		}
	}
}



void StateEditorMode::Update() {
	if (GetRightMouseDown())
	{
		DragMap();
	}

	if (GetLeftMouseDown())
	{
		if (selectedItemBase_.second != nullptr)
		{
			int mapSizeX = GetMap()->GetCellMap().size();
			int mapSizeY = GetMap()->GetCellMap()[0].size();
			int tileXPos = (GetMouseCursorX() - GetMap()->GetMapXOffset() + AcedSharedDLL::Constants::TileSize() / 2) / AcedSharedDLL::Constants::TileSize();
			int tileYPos = (GetMouseCursorY() - GetMap()->GetMapYOffset() + AcedSharedDLL::Constants::TileSize() / 2) / AcedSharedDLL::Constants::TileSize();
			if (tileXPos >= 0 &&
				tileXPos < mapSizeX &&
				tileYPos >= 0 &&
				tileYPos < mapSizeY)
			{


				//Tile color picker is weird prototype not sure if i wanna keep yet
				if (selectedItemBase_.first == AcedSharedDLL::STATES::TILECOLORPICKER)
				{
					if (selectedItemBase_.second->GetImageBundle() != nullptr)
					{
						if (selectedItemBase_.second->GetImageBundle()->GetId() == -1)
						{
							if (GetMap()->GetCellMap()[tileXPos][tileYPos]->GetHasTile()) {
								GetMap()->GetCellMap()[tileXPos][tileYPos]->GetTile()->RemoveColor();
							}
						}
					}
					else
					{
						if (GetMap()->GetCellMap()[tileXPos][tileYPos]->GetHasTile()) {
							GetMap()->GetCellMap()[tileXPos][tileYPos]->GetTile()->SetColor(selectedItemBase_.second->GetColor());
						}
					}
				}
				//Collision Types
				else if (selectedItemBase_.first == AcedSharedDLL::STATES::TILETYPEPICKER)
				{
					int cellEmpty = true;
					if (GetMap()->EnemyAlreadyExistsAtXY(tileXPos, tileYPos)) {
						cellEmpty = false;
					}
					else if (GetMap()->ItemAlreadyExistsAtXY(tileXPos, tileYPos)) {
						cellEmpty = false;
					}

					if (cellEmpty) {
						GetMap()->GetCellMap()[tileXPos][tileYPos]->SetTileTypeProperties(selectedItemBase_.second);
					}
				}

				//Normal tile placements-
				else if (selectedItemBase_.first == AcedSharedDLL::STATES::TILEIMAGEPICKER)
				{

					//First check all fields so you dont place over a spot that already has a Solid Tile...
					int cellEmpty = true;
					if (GetMap()->GetCellMap()[tileXPos][tileYPos]->GetTileType() != AcedSharedDLL::TILETYPE::EMPTYTILE)
					{
						cellEmpty = false;
					}
					else if (GetMap()->EnemyAlreadyExistsAtXY(tileXPos, tileYPos)) {
						cellEmpty = false;
					}
					else if (GetMap()->GetCellMap()[tileXPos][tileYPos]->GetHasInteractiveObject()) {
						cellEmpty = false;
					}
					else if (GetMap()->ItemAlreadyExistsAtXY(tileXPos, tileYPos)) {
						cellEmpty = false;
					}



					//Id of 0 Means im removing object from map.
					if (selectedItemBase_.second->GetImageBundle()->GetId() == -1 &&
						GetMap()->GetCellMap()[tileXPos][tileYPos]->GetHasTile()) {
						GetMap()->GetCellMap()[tileXPos][tileYPos]->DeleteTile();
					}
					else if (selectedItemBase_.second->GetImageBundle()->GetId() == -1) {

					}
					else if (cellEmpty) {
						if (GetMap()->GetCellMap()[tileXPos][tileYPos]->GetHasTile())
						{
							GetMap()->GetCellMap()[tileXPos][tileYPos]->GetTile()->SetTileBase(selectedItemBase_.second);
						}
						else {
							std::shared_ptr<AcedSharedDLL::Tile> currentTile(new AcedSharedDLL::Tile());

							currentTile->SetTileBase(selectedItemBase_.second);

							GetMap()->GetCellMap()[tileXPos][tileYPos]->SetTile(currentTile);
						}
					}
				}



				else if (selectedItemBase_.first == AcedSharedDLL::STATES::OBJECTIMAGEPICKER) {
					//Placement Logic For Object Image Picker
					//Move To a Method and give it Details Comments as to why.

					if (tileXPos + selectedItemBase_.second->GetWidth() > GetMap()->GetMapWidth() ||
						tileYPos + selectedItemBase_.second->GetHeight() > GetMap()->GetMapHeight()) {
					}
					else {
						//First check all fields so you dont place over a spot that already has a Solid Tile...
						int cellEmpty = true;
						for (auto i = tileXPos; i < tileXPos + selectedItemBase_.second->GetWidth(); i++) {
							for (auto j = tileYPos; j < tileYPos + selectedItemBase_.second->GetHeight(); j++) {

								if (GetMap()->GetCellMap()[i][j]->GetTileType() != AcedSharedDLL::TILETYPE::EMPTYTILE)
								{
									cellEmpty = false;
									break;
								}
								else if (GetMap()->EnemyAlreadyExistsAtXY(i, j)) {
									cellEmpty = false;
									break;
								}
								else if (GetMap()->GetCellMap()[i][j]->GetHasInteractiveObject()) {
									cellEmpty = false;
									break;
								}
								else if (GetMap()->ItemAlreadyExistsAtXY(i, j)) {
									cellEmpty = false;
									break;
								}
							}
						}

						//Id of 0 Means im removing object from map.
						if (GetMap()->GetCellMap()[tileXPos][tileYPos]->GetHasInteractiveObject() &&
							selectedItemBase_.second->GetImageBundle()->GetId() == -1) {
							auto imageRefX = GetMap()->GetCellMap()[tileXPos][tileYPos]->GetInteractiveObject()->GetImageReferenceX();
							auto imageRefY = GetMap()->GetCellMap()[tileXPos][tileYPos]->GetInteractiveObject()->GetImageReferenceY();
							auto imageWidth = GetMap()->GetCellMap()[imageRefX][imageRefY]->GetInteractiveObject()->GetImageBundle()->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetWidth();
							auto imageHeight = GetMap()->GetCellMap()[imageRefX][imageRefY]->GetInteractiveObject()->GetImageBundle()->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetHeight();
							for (auto i = imageRefX; i < imageRefX + imageWidth; i++) {
								for (auto j = imageRefY; j < imageRefY + imageHeight; j++) {
									GetMap()->GetCellMap()[i][j]->DeleteInteractiveObject();
								}
							}
						}
						else if (selectedItemBase_.second->GetImageBundle()->GetId() == -1) {

						}
						else if (cellEmpty) {
							for (auto i = tileXPos; i < tileXPos + selectedItemBase_.second->GetWidth(); i++) {
								for (auto j = tileYPos; j < tileYPos + selectedItemBase_.second->GetHeight(); j++) {
									std::shared_ptr<AcedSharedDLL::InteractiveObject> currentInteractiveObject(new AcedSharedDLL::InteractiveObject());
									currentInteractiveObject->SetItemBase(selectedItemBase_.second);
									currentInteractiveObject->SetHasImageReference(!(i == tileXPos && j == tileYPos));
									currentInteractiveObject->SetImageReferenceX(tileXPos);
									currentInteractiveObject->SetImageReferenceY(tileYPos);
									GetMap()->GetCellMap()[i][j]->SetInteractiveObject(currentInteractiveObject);
									GetMap()->GetCellMap()[i][j]->SetInteractiveObjectReference(!(i == tileXPos && j == tileYPos));

								}
							}
						}
					}

				}



				else if (selectedItemBase_.first == AcedSharedDLL::STATES::ENEMYPICKER) {

					//Check that your not placing item over a tile position
					//Check not over existing char

					int tileEmpty = true;
					for (auto i = tileXPos; i < tileXPos + selectedItemBase_.second->GetWidth(); i++) {
						for (auto j = tileYPos; j < tileYPos + selectedItemBase_.second->GetHeight(); j++) {
							if (GetMap()->GetCellMap()[i][j]->GetTileType() != AcedSharedDLL::TILETYPE::EMPTYTILE)
							{
								tileEmpty = false;
								break;
							}
							else if (GetMap()->EnemyAlreadyExistsAtXY(i, j)) {
								tileEmpty = false;
								break;
							}
							else if (GetMap()->GetCellMap()[i][j]->GetHasInteractiveObject()) {
								tileEmpty = false;
								break;
							}
							else if (GetMap()->ItemAlreadyExistsAtXY(i, j)) {
								tileEmpty = false;
								break;
							}
						}
					}


					//Remover item
					if (selectedItemBase_.second->GetImageBundle()->GetId() == -1) {
						//removes enemy if it exists at point
						GetMap()->RemoveEnemyFromMap(tileXPos, tileYPos);
					}
					//Empty slot place enemy spawner
					else if (tileEmpty) {
						//should hopefully ever be 1x1 enemy sizes otherwise change add enemy to be special
						for (auto i = tileXPos; i < tileXPos + selectedItemBase_.second->GetWidth(); i++) {
							for (auto j = tileYPos; j < tileYPos + selectedItemBase_.second->GetHeight(); j++) {
								GetMap()->AddEnemyToMap(selectedItemBase_.second, tileXPos, tileYPos);
							}
						}
					}
				}

				else if (selectedItemBase_.first == AcedSharedDLL::STATES::ITEMPICKER) {

					//Check that your not placing item over a tile position
					//Check not over existing char

					int tileEmpty = true;
					for (auto i = tileXPos; i < tileXPos + selectedItemBase_.second->GetWidth(); i++) {
						for (auto j = tileYPos; j < tileYPos + selectedItemBase_.second->GetHeight(); j++) {
							if (GetMap()->GetCellMap()[i][j]->GetTileType() != AcedSharedDLL::TILETYPE::EMPTYTILE)
							{
								tileEmpty = false;
								break;
							}
							else if (GetMap()->EnemyAlreadyExistsAtXY(i, j)) {
								tileEmpty = false;
								break;
							}
							else if (GetMap()->GetCellMap()[i][j]->GetHasInteractiveObject()) {
								tileEmpty = false;
								break;
							}
							else if (GetMap()->ItemAlreadyExistsAtXY(i, j)) {
								tileEmpty = false;
								break;
							}
						}
					}


					//Remover item
					if (selectedItemBase_.second->GetImageBundle()->GetId() == -1) {
						//removes enemy if it exists at point
						GetMap()->RemoveItemFromMap(tileXPos, tileYPos);
					}
					//Empty slot place enemy spawner
					else if (tileEmpty) {
						//should hopefully ever be 1x1 enemy sizes otherwise change add enemy to be special
						for (auto i = tileXPos; i < tileXPos + selectedItemBase_.second->GetWidth(); i++) {
							for (auto j = tileYPos; j < tileYPos + selectedItemBase_.second->GetHeight(); j++) {
								GetMap()->AddItemToMap(selectedItemBase_.second, tileXPos, tileYPos);
							}
						}
					}


				}
			}
		}
	}


	if (GetEvent()->type == ALLEGRO_EVENT_TIMER)
	{
		GetMap()->Update();
		//Update overlay. Will return with no actions if action state of it is NONE.
		editorOverLayController_->Update();
		SetRedraw(true);
	}


}



void StateEditorMode::Draw() {


	GetMap()->DrawMap();


	editorOverLayController_->Draw();


	al_draw_rectangle(GetMouseCursorX(), GetMouseCursorY(), GetMouseCursorX() + AcedSharedDLL::Constants::TileSize(), GetMouseCursorY() + AcedSharedDLL::Constants::TileSize(), al_map_rgb_f(0, 0, 0), 2);//1
}











void StateEditorMode::DragMap()
{
	GetMap()->SetMapXOffset(GetMap()->GetOldMapXOffset() + (GetMouseCursorX()) - (GetRightMouseX()));
	GetMap()->SetMapYOffset(GetMap()->GetOldMapYOffset() + (GetMouseCursorY()) - (GetRightMouseY()));
}


