#include "StateTemplates.h"
#include "MenuTemplates.h"
#include "State.h"
#include "Map.h"


namespace StaticDLL{





	void StateEditorMode::InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap, ImageLoader *imageLoader){
		
		SetImageLoader(imageLoader);
		SetDisplay(display);
		SetSettings(settings);
		SetId(EnumDLL::STATES::EDITORMODE);
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
		SetMap(currentMap);



		editorOverLayController_ = new EditorOverLayController(settings, imageLoader);



		SetChosenColor(al_map_rgb_f(1,1,1));
		al_start_timer(GetTimer());
	}


	void StateEditorMode::Resume(){
		editorOverLayController_->Resize();
		SetStateDirection(EnumDLL::STATEDIRECTION::NA);
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
					SetStateDirection(EnumDLL::STATEDIRECTION::PUSH);
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
			selectedTile_  = editorOverLayController_->GetSelectedObject();
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
			if(selectedTile_.second != nullptr)
			{
				int mapSizeX = GetMap()->GetTiles().size();
				int mapSizeY = GetMap()->GetTiles()[0].size();
				int tileXPos = (GetMouseCursorX() - GetMap()->GetMapXOffset() + Constants::TileSize/2)/Constants::TileSize;
				int tileYPos = (GetMouseCursorY() - GetMap()->GetMapYOffset() + Constants::TileSize/2)/Constants::TileSize;
				if(tileXPos >= 0 && 
					tileXPos < mapSizeX &&
					tileYPos >= 0 && 
					tileYPos < mapSizeY)
				{
					if(selectedTile_.first == EnumDLL::STATES::TILEIMAGEPICKER)
					{
						if(selectedTile_.second->GetObjectImage()->GetId() == 0)
						{
							GetMap()->GetTiles()[tileXPos][tileYPos].RemoveImage();
						}
						else
						{
							GetMap()->GetTiles()[tileXPos][tileYPos].SetTileProperties(selectedTile_.second);
						}
					}
					else if(selectedTile_.first == EnumDLL::STATES::TILECOLORPICKER)
					{
						if(selectedTile_.second->GetObjectImage() != nullptr)
						{
							if(selectedTile_.second->GetObjectImage()->GetId() == 0)
							{
								GetMap()->GetTiles()[tileXPos][tileYPos].RemoveColor();
							}
						}
						else
						{
							GetMap()->GetTiles()[tileXPos][tileYPos].SetTileProperties(selectedTile_.second);
						}
					}
					else if(selectedTile_.first == EnumDLL::STATES::TILETYPEPICKER)
					{
						GetMap()->GetTiles()[tileXPos][tileYPos].SetTileTypeProperties(selectedTile_.second);
					}



				}
			}
		}


		if(GetEvent()->type == ALLEGRO_EVENT_TIMER)
		{			
			GetMap()->PreCalc();
			//Update overlay. Will return with no actions if action state of it is NONE.
			editorOverLayController_->Update();
			SetRedraw(true);
		}


	}



	void StateEditorMode::Draw(){


		GetMap()->DrawMap();


		editorOverLayController_->Draw();


		al_draw_rectangle(GetMouseCursorX(),GetMouseCursorY(),GetMouseCursorX()+Constants::TileSize,GetMouseCursorY()+Constants::TileSize, al_map_rgb_f(0,0,0),2);//1
	}



	







	void StateEditorMode::DragMap()
	{
		GetMap()->SetMapXOffset(GetMap()->GetOldMapXOffset() + (GetMouseCursorX())-(GetRightMouseX()));
		GetMap()->SetMapYOffset(GetMap()->GetOldMapYOffset() + (GetMouseCursorY())-(GetRightMouseY()));
	}
}