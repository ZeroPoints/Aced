#include "StateTemplates.h"
#include "MenuTemplates.h"
#include "State.h"
#include "Map.h"


namespace StaticDLL{





	void StateEditorMode::InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map* currentMap){
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


		editorOverLay_ = new EditorOverLay(settings);

		SetChosenColor(al_map_rgb_f(1,1,1));
		al_start_timer(GetTimer());





	}






	void StateEditorMode::KeyPress(){
		if(GetEvent().type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(GetEvent().keyboard.keycode)
			{
				case ALLEGRO_KEY_ESCAPE:						
					SetStateDirection(EnumDLL::STATEDIRECTION::PUSH);
					SetNextState(new StateEditorMenu());
					break;
			}
		}
		editorOverLay_->KeyBoardActivity(GetEvent());
	}




	void StateEditorMode::MouseActivity(){


		if(GetEvent().type == ALLEGRO_EVENT_MOUSE_AXES)
		{			
			SetMouseCursorPos(GetEvent().mouse.x-10,GetEvent().mouse.y-10);
		}

		editorOverLay_->MouseActivity(GetEvent(), GetMouseCursorX(),GetMouseCursorY());
		EditorModeMouseActivity();

		
	}



	void StateEditorMode::EditorModeMouseActivity()
	{
		if(GetEvent().type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			switch(GetEvent().mouse.button)
			{
				case 1:
					break;
				case 2:
					SetRightMouseDown(true);
					SetRightMousePos(GetMouseCursorX(),GetMouseCursorY());
					GetMap()->SetOldMapXOffset(GetMap()->GetMapXOffset());
					GetMap()->SetOldMapYOffset(GetMap()->GetMapYOffset());
					
					break;
			}
		}
		if(GetEvent().type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			switch(GetEvent().mouse.button)
			{
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
		GetMap()->PreCalc();

		if(GetEvent().type == ALLEGRO_EVENT_TIMER)
		{			
			//Update overlay. Will return with no actions if action state of it is NONE.
			editorOverLay_->Update();
			SetRedraw(true);
		}


	}



	void StateEditorMode::Draw(){
		GetMap()->DrawMap();


		editorOverLay_->Draw();


		al_draw_rectangle(GetMouseCursorX(),GetMouseCursorY(),GetMouseCursorX()+Constants::TileSize,GetMouseCursorY()+Constants::TileSize, GetChosenColor(),2);//1
		al_draw_textf(GetFont(), GetChosenColor(), 00, 20, ALLEGRO_ALIGN_LEFT, "%f" , GetEvent().timer.timestamp);
	}



	void StateEditorMode::Resume(){
		SetStateDirection(EnumDLL::STATEDIRECTION::NA);
		SetNextState(NULL);
	}









	void StateEditorMode::DragMap()
	{
		GetMap()->SetMapXOffset(GetMap()->GetOldMapXOffset() + (GetMouseCursorX())-(GetRightMouseX()));
		GetMap()->SetMapYOffset(GetMap()->GetOldMapYOffset() + (GetMouseCursorY())-(GetRightMouseY()));
	}
}