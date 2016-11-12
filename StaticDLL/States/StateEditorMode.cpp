#include "StateTemplates.h"
#include "../Menu/MenuTemplates.h"
#include "State.h"
#include "../World/Map.h"


namespace StaticDLL{





	void StateEditorMode::InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap, AssetLibrary *assetLibrary){
		
		SetAssetLibrary(assetLibrary);
		SetDisplay(display);
		SetSettings(settings);
		SetId(STATES::EDITORMODE);
		SetEventQueue(NULL);
		SetRedraw(true);
		SetDone(false);
		SetRunning(true);
		SetKeyPressReturnVal(STATES::DEFAULT);
		SetFont(al_load_font("arial.ttf", Constants::TileSize(), 0));
		SetTimer(al_create_timer(1.0/60));
		SetEventQueue(al_create_event_queue());
		SetStateDirection(STATEDIRECTION::NA);


		al_register_event_source(GetEventQueue(), al_get_keyboard_event_source());
		al_register_event_source(GetEventQueue(), al_get_mouse_event_source());
		al_register_event_source(GetEventQueue(), al_get_display_event_source(GetDisplay()));
		al_register_event_source(GetEventQueue(), al_get_timer_event_source(GetTimer()));
		SetMouseCursorPos(0,0);
		SetRightMousePos(0,0);
		SetRightMouseDown(false);
		SetLeftMouseDown(false);
		SetPlayerSelected(false);
		SetMap(currentMap);



		editorOverLayController_ = new EditorOverLayController(settings, GetAssetLibrary());



		SetChosenColor(al_map_rgb_f(1,1,1));
		al_start_timer(GetTimer());
	}


	void StateEditorMode::Resume(){
		editorOverLayController_->Resize();
		SetStateDirection(STATEDIRECTION::NA);
		SetNextState(NULL);

		//Resize menus
		//I dont have a resize menu type function atm
		//i could just destroy and remake
		//But then my remake doesnt have adjustments based on screen size as of yet
	}



	void StateEditorMode::KeyPress(){
		if(GetEvent()->type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(GetEvent()->keyboard.keycode)
			{
				case ALLEGRO_KEY_ESCAPE:						
					SetStateDirection(STATEDIRECTION::PUSH);
					SetNextState(new StateEditorMenu());
					break;
			}
		}
		editorOverLayController_->KeyBoardActivity(GetEvent());
	}




	void StateEditorMode::MouseActivity(){


		if(GetEvent()->type == ALLEGRO_EVENT_MOUSE_AXES)
		{			
			SetMouseCursorPos(GetEvent()->mouse.x-10,GetEvent()->mouse.y-10);
		}


		//If the editor overlay didnt take control of mouse activity let editor mode handle it
		if(!editorOverLayController_->MouseActivity(GetEvent(), GetMouseCursorX(),GetMouseCursorY()))
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
		if(GetEvent()->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			switch(GetEvent()->mouse.button)
			{
				case 1:
					SetLeftMouseDown(true);
					break;
				case 2:
					SetRightMouseDown(true);
					SetRightMousePos(GetMouseCursorX(),GetMouseCursorY());
					GetMap()->SetOldMapXOffset(GetMap()->GetMapXOffset());
					GetMap()->SetOldMapYOffset(GetMap()->GetMapYOffset());
					
					break;
			}
		}
		if(GetEvent()->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			switch(GetEvent()->mouse.button)
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



	void StateEditorMode::Update(){
		if(GetRightMouseDown())
		{
			DragMap();
		}

		if(GetLeftMouseDown())
		{
			if(selectedItemBase_.second != nullptr)
			{
				int mapSizeX = GetMap()->GetCellMap().size();
				int mapSizeY = GetMap()->GetCellMap()[0].size();
				int tileXPos = (GetMouseCursorX() - GetMap()->GetMapXOffset() + Constants::TileSize()/2)/Constants::TileSize();
				int tileYPos = (GetMouseCursorY() - GetMap()->GetMapYOffset() + Constants::TileSize()/2)/Constants::TileSize();
				if(tileXPos >= 0 && 
					tileXPos < mapSizeX &&
					tileYPos >= 0 && 
					tileYPos < mapSizeY)
				{
					

					//Tile color picker is weird prototype not sure if i wanna keep yet
					if(selectedItemBase_.first == STATES::TILECOLORPICKER)
					{
						if(selectedItemBase_.second->GetObjectImage() != nullptr)
						{
							if(selectedItemBase_.second->GetObjectImage()->GetId() == 0)
							{
								if (GetMap()->GetCellMap()[tileXPos][tileYPos].GetHasTile()) {
									GetMap()->GetCellMap()[tileXPos][tileYPos].GetTile()->RemoveColor();
								}
							}
						}
						else
						{
							if (GetMap()->GetCellMap()[tileXPos][tileYPos].GetHasTile()) {
								GetMap()->GetCellMap()[tileXPos][tileYPos].GetTile()->SetColor(selectedItemBase_.second->GetColor());
							}
						}
					}
					//Collision Types
					else if(selectedItemBase_.first == STATES::TILETYPEPICKER)
					{
						int cellEmpty = true;
						if (GetMap()->EnemyAlreadyExistsAtXY(tileXPos, tileYPos)) {
							cellEmpty = false;
						}
						else if (GetMap()->ItemAlreadyExistsAtXY(tileXPos, tileYPos)) {
							cellEmpty = false;
						}

						if (cellEmpty) {
							GetMap()->GetCellMap()[tileXPos][tileYPos].SetTileTypeProperties(selectedItemBase_.second);
						}
					}

					//Normal tile placements-
					else if (selectedItemBase_.first == STATES::TILEIMAGEPICKER)
					{
						
						//First check all fields so you dont place over a spot that already has a Solid Tile...
						int cellEmpty = true;
						if (GetMap()->GetCellMap()[tileXPos][tileYPos].GetTileType() != TILETYPE::EMPTYTILE)
						{
							cellEmpty = false;
						}
						else if (GetMap()->EnemyAlreadyExistsAtXY(tileXPos,tileYPos)) {
							cellEmpty = false;
						}
						else if (GetMap()->GetCellMap()[tileXPos][tileYPos].GetHasInteractiveObject()) {
							cellEmpty = false;
						}
						else if (GetMap()->ItemAlreadyExistsAtXY(tileXPos, tileYPos)) {
							cellEmpty = false;
						}



						//Id of 0 Means im removing object from map.
						if (selectedItemBase_.second->GetObjectImage()->GetId() == 0 &&
							GetMap()->GetCellMap()[tileXPos][tileYPos].GetHasTile()) {
							GetMap()->GetCellMap()[tileXPos][tileYPos].DeleteTile();
						}
						else if (selectedItemBase_.second->GetObjectImage()->GetId() == 0) {

						}
						else if (cellEmpty) {
							if (GetMap()->GetCellMap()[tileXPos][tileYPos].GetHasTile())
							{
								GetMap()->GetCellMap()[tileXPos][tileYPos].GetTile()->SetTileObjectImageFromTile(
									selectedItemBase_.second, tileXPos, tileYPos);
							}
							else {
								auto currentTile = new Tile();
								currentTile->SetTileObjectImageFromTile(
									selectedItemBase_.second, tileXPos, tileYPos);
								GetMap()->GetCellMap()[tileXPos][tileYPos].SetTile(currentTile);
							}
						}
					}



					else if (selectedItemBase_.first == STATES::OBJECTIMAGEPICKER) {
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

									if (GetMap()->GetCellMap()[i][j].GetTileType() != TILETYPE::EMPTYTILE)
									{
										cellEmpty = false;
										break;
									}
									else if (GetMap()->EnemyAlreadyExistsAtXY(i, j)) {
										cellEmpty = false;
										break;
									}
									else if (GetMap()->GetCellMap()[i][j].GetHasInteractiveObject()) {
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
							if (GetMap()->GetCellMap()[tileXPos][tileYPos].GetHasInteractiveObject() && 
								selectedItemBase_.second->GetObjectImage()->GetId() == 0) {
								auto imageRefX = GetMap()->GetCellMap()[tileXPos][tileYPos].GetInteractiveObject()->GetImageReferenceX();
								auto imageRefY = GetMap()->GetCellMap()[tileXPos][tileYPos].GetInteractiveObject()->GetImageReferenceY();
								auto imageWidth = GetMap()->GetCellMap()[imageRefX][imageRefY].GetInteractiveObject()->GetObjectImage()->GetWidth();
								auto imageHeight = GetMap()->GetCellMap()[imageRefX][imageRefY].GetInteractiveObject()->GetObjectImage()->GetHeight();
								for (auto i = imageRefX; i < imageRefX + imageWidth; i++) {
									for (auto j = imageRefY; j < imageRefY + imageHeight; j++) {
										GetMap()->GetCellMap()[i][j].DeleteInteractiveObject();
									}
								}
							}
							else if (selectedItemBase_.second->GetObjectImage()->GetId() == 0) {

							}
							else if (cellEmpty) {
								for (auto i = tileXPos; i < tileXPos + selectedItemBase_.second->GetWidth(); i++) {
									for (auto j = tileYPos; j < tileYPos + selectedItemBase_.second->GetHeight(); j++) {
										auto currentInteractiveObject = new InteractiveObject();
										currentInteractiveObject->SetObjectProperties(selectedItemBase_.second, !(i == tileXPos && j == tileYPos), tileXPos, tileYPos);
										GetMap()->GetCellMap()[i][j].SetInteractiveObject(currentInteractiveObject, !(i == tileXPos && j == tileYPos));
									}
								}
							}
						}

					}



					else if (selectedItemBase_.first == STATES::ENEMYPICKER) {

						//Check that your not placing item over a tile position
						//Check not over existing char

						int tileEmpty = true;
						for (auto i = tileXPos; i < tileXPos + selectedItemBase_.second->GetWidth(); i++) {
							for (auto j = tileYPos; j < tileYPos + selectedItemBase_.second->GetHeight(); j++) {
								if (GetMap()->GetCellMap()[i][j].GetTileType() != TILETYPE::EMPTYTILE)
								{
									tileEmpty = false;
									break;
								}
								else if (GetMap()->EnemyAlreadyExistsAtXY(i, j)) {
									tileEmpty = false;
									break;
								}
								else if (GetMap()->GetCellMap()[i][j].GetHasInteractiveObject()) {
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
						if (selectedItemBase_.second->GetObjectImage()->GetId() == 0) {
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

					else if (selectedItemBase_.first == STATES::ITEMPICKER) {

						//Check that your not placing item over a tile position
						//Check not over existing char

						int tileEmpty = true;
						for (auto i = tileXPos; i < tileXPos + selectedItemBase_.second->GetWidth(); i++) {
							for (auto j = tileYPos; j < tileYPos + selectedItemBase_.second->GetHeight(); j++) {
								if (GetMap()->GetCellMap()[i][j].GetTileType() != TILETYPE::EMPTYTILE)
								{
									tileEmpty = false;
									break;
								}
								else if (GetMap()->EnemyAlreadyExistsAtXY(i, j)) {
									tileEmpty = false;
									break;
								}
								else if (GetMap()->GetCellMap()[i][j].GetHasInteractiveObject()) {
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
						if (selectedItemBase_.second->GetObjectImage()->GetId() == 0) {
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


		if(GetEvent()->type == ALLEGRO_EVENT_TIMER)
		{			
			GetMap()->Update();
			//Update overlay. Will return with no actions if action state of it is NONE.
			editorOverLayController_->Update();
			SetRedraw(true);
		}


	}



	void StateEditorMode::Draw(){


		GetMap()->DrawMap();


		editorOverLayController_->Draw();


		al_draw_rectangle(GetMouseCursorX(),GetMouseCursorY(),GetMouseCursorX()+Constants::TileSize(),GetMouseCursorY()+Constants::TileSize(), al_map_rgb_f(0,0,0),2);//1
	}



	







	void StateEditorMode::DragMap()
	{
		GetMap()->SetMapXOffset(GetMap()->GetOldMapXOffset() + (GetMouseCursorX())-(GetRightMouseX()));
		GetMap()->SetMapYOffset(GetMap()->GetOldMapYOffset() + (GetMouseCursorY())-(GetRightMouseY()));
	}
}