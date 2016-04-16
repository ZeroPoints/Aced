#include "StateTemplates.h"
#include "MenuTemplates.h"
#include "State.h"
#include "Map.h"


namespace StaticDLL{





	void StateGameMode::InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap, ImageLoader *imageLoader){
		
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

		
		player1_ = new Player();
		player1_->SetCurrentPositionX(5);
		player1_->SetGravityY(-9.8);


		for(int i = 0; i < 20; i++)
		{
			Player* newPlayer = new Player();
			newPlayer->SetCurrentPositionX(i+5);
			newPlayer->SetGravityY(-9.8);
			players_.push_back(newPlayer);
		}




		SetChosenColor(al_map_rgb_f(1,1,1));
		al_start_timer(GetTimer());
	}


	void StateGameMode::Resume(){
		SetStateDirection(EnumDLL::STATEDIRECTION::NA);
		SetNextState(NULL);
	}



	void StateGameMode::KeyPress(){
		if(GetEvent()->type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(GetEvent()->keyboard.keycode)
			{
				case ALLEGRO_KEY_ESCAPE:
					//this will need to change to pushing a menu ontop instead of popping.
					//as popping cleans current states progress
					SetPopLevel(1);
					SetStateDirection(EnumDLL::STATEDIRECTION::POP);
					break;
			}
		}

		if(player1_->Keypress(GetEvent())==1)
		{
		}

			
		for(int i = 0; i < 20; i++)
		{
			if(players_[i]->Keypress(GetEvent())==1)
			{
				players_[i]->SetVelocityY(i);
			}
		}

	}




	void StateGameMode::MouseActivity(){


		if(GetEvent()->type == ALLEGRO_EVENT_MOUSE_AXES)
		{			
			SetMouseCursorPos(GetEvent()->mouse.x-10,GetEvent()->mouse.y-10);
		}


		

	}





	void StateGameMode::Update(){
		

		if(GetEvent()->type == ALLEGRO_EVENT_TIMER)
		{			
			GetMap()->PreCalc();

				player1_->Update(GetMap());
			/*for(int i = 0; i < 20; i++)
			{
				players_[i]->Update(GetMap());
			}*/


			//Update overlay. Will return with no actions if action state of it is NONE.
			SetRedraw(true);
		}


	}



	void StateGameMode::Draw(){


		GetMap()->DrawMap();

		player1_->DrawObject();
		/*for(int i = 0; i < 20; i++)
		{
			players_[i]->DrawObject();
		}
*/
		al_draw_rectangle(GetMouseCursorX(),GetMouseCursorY(),GetMouseCursorX()+Constants::TileSize,GetMouseCursorY()+Constants::TileSize, GetChosenColor(),2);//1
	}






}