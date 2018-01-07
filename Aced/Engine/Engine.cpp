#include "Engine.h"



Engine::Engine(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap, AssetLibrary *assetLibrary)
{
	//init
	display_ = display;
	settings_ = settings;
	currentMap_ = currentMap;
	assetLibrary_ = assetLibrary;
	finished_ = false;
	running_ = true;
	chosenColor_ = al_map_rgb_f(1,1,1);
	chosenColorText_ = al_map_rgb_f(0,0,0);


	//new used to keep it in memory the state. This needs to be freed when Engine is finished.

	PushNewState(new StateGameMainMenu(display_, settings_, currentMap_, assetLibrary_));
}



/*
Main Loop running the project engine. Cycles through an infinite loop while States are still running.
Pushes in the first state of main menu of the editor application and it will cycle through the States registered events
Then it will perform that States keypress method and mouse activity method.
If a states resulting processing will decide that the state is no longer needed. EG: closing current map or option menu it will push or pop the State stack and destroy/dispose/clean those objects from memory.
If those State directions have not been triggered. The game will run the current states Update(game logic) method and then run the Draw method
*/
void Engine::Run()
{


	ALLEGRO_EVENT ev;
	while(currentState_->GetRunning()){
		al_wait_for_event(currentState_->GetEventQueue(),&ev);


		currentState_->SetEvent(&ev);
		currentState_->KeyPress();
		currentState_->MouseActivity();

		if(currentState_->GetStateDirection() == STATEDIRECTION::PUSH){
			PushState();
			continue;
		}
		else if(currentState_->GetStateDirection() == STATEDIRECTION::POP){
			PopState();
			continue;
		}
		else if(currentState_->GetStateDirection() == STATEDIRECTION::POPPUSH){
			PopPushState();
			continue;
		}
		else if(currentState_->GetStateDirection() == STATEDIRECTION::POPTOFIRST){
			PopStateToFirst();
			continue;
		}
		if(currentState_->GetEvent()->type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			//close window if display is closed via X in top right corner
			currentState_->SetRunning(false);
		}
		currentState_->Update();
		if(currentState_->GetRedraw() && al_is_event_queue_empty(currentState_->GetEventQueue()))
		{
			currentState_->SetRedraw(false);
			currentState_->Draw();
			//bread and butter

			char text[20];
			sprintf(text, "Time:%f", ev.timer.timestamp);
			al_draw_text(currentState_->GetFont(), chosenColorText_,
				0,
				settings_->GetScreenHeight() - Constants::TileSize(), ALLEGRO_ALIGN_LEFT, text);


			al_flip_display();
			al_clear_to_color(chosenColor_);//clears color to dark green to remove all back image
		}




		/*
		Get state done or not
		if done == true delete current state and Set new state
		if not done and state change push new state to stack
		if neither do normal again (-2 default)
		*/
		//Get keypress state
		//mmm change state
	}
}










/*
This will append the State stack with the lasts states direction towards the new state. EG: main menu click new map -> will push the editing mode state onto the stack.
*/
void Engine::PushState()
{
	// pause current state
	if ( !states_.empty() ) {
		states_.back()->Pause();
	}

	// store and init the new state
	states_.push_back(states_.back()->GetNextState());
	//states_.back()->InitState();
	//change init state to reset state
	currentState_ = states_.back();
}


/*
This will push a forced state onto the stack ontop of current state. This may or may not ever be used. 
Might be useful if a state has no specific direction it can take and only the engine can decide 
eg some fatal error in state let the engine decide that it should cancel out and go to main menu.
Also used to push the first state onto the stack as part of engine init
*/
void Engine::PushNewState(State* state)
{
	// pause current state
	if ( !states_.empty() ) {
		states_.back()->Pause();
	}

	// store and init the new state
	states_.push_back(state);
	//states_.back()->InitState();
	//change init state to reset state
	currentState_ = states_.back();
}





/*

*/
void Engine::PopState()
{
	int popLevel = states_.back()->GetPopLevel();
	//store something mmmm so pop back x levels then push something aswell

	int i = 0;
	while(i < popLevel){
		// cleanup the current state
		if ( !states_.empty() ) {
			if(states_.size() > 1){
				states_.back()->CleanUp();
				delete states_.back();
				states_.pop_back();
			}
		}
		i++;
	}
	//fprintf(stderr,"States Popped\n\n\n");

	// resume previous state..This will control where in the last state it should appear and what variables need to be reSet
	if ( !states_.empty() ) {
		states_.back()->Resume();
		//clears all events in queue so the other menus keystate is cleared
		al_flush_event_queue(states_.back()->GetEventQueue());
	}
	currentState_ = states_.back();
}


/*
Takes current state of stack and pushes a new one onto the stack in its place
*/
void Engine::PopPushState()
{
	int popLevel = states_.back()->GetPopLevel();
	State* pushState = states_.back()->GetNextState();
	int i = 0;
	while(i < popLevel){
		if ( !states_.empty() ) {
			if(states_.size() > 1){
				states_.back()->CleanUp();
				delete states_.back();
				states_.pop_back();
			}
		}
		i++;
	}
	//fprintf(stderr,"States Popped\n\n\n");

	PushNewState(pushState);
}



/*
Takes all states off and goes back to first state eg: main menu most often
*/
void Engine::PopStateToFirst()
{
	int popLevel = states_.size();
	int i = 1;
	while(i < popLevel){
		states_.back()->CleanUp();
		delete states_.back();
		states_.pop_back();
		popLevel--;
	}
	states_.back()->Resume();
	al_flush_event_queue(states_.back()->GetEventQueue());
	currentState_ = states_.back();
}






