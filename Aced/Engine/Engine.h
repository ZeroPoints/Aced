#ifndef ENGINE_H
#define ENGINE_H

#include <allegro5\allegro.h>
#include <vector>
#include "LivingEntity/Player.h"
#include "World/map.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "Static/Definitions.h"
#include "States/State.h"
#include "Config/Settings.h"
#include <States/StateTemplates.h>



using namespace StaticDLL;


//this files for hardcoding game engine stuff.
class Engine
{
    public:
        Engine(ALLEGRO_DISPLAY *display, Settings *Settings, Map *currentMap, AssetLibrary *assetLibrary);

		~Engine()
        {
			//delete all states from memory
			int popLevel = states_.size();
			int i = 0;
			//check if this pops the last one off
			while(i < popLevel){
				states_.back()->CleanUp();
				delete states_.back();
				states_.pop_back();
				popLevel--;
			}

			//fprintf(stderr,"A Editor Engine Destructed\n");
        }
		


        void Run();
		void CleanUp();
		void ChangeState(State* state, ALLEGRO_DISPLAY *display);
		void PushNewState(State* state);
		void PushState();
		void PopState();
		void PopStateToFirst();
		void PopPushState();
		void KeyPress();
		void Update();
		void Draw();

		bool Running() { return running_; }
		void Quit() { running_ = false; }

    private:
		bool finished_;

		ALLEGRO_DISPLAY *display_;
		Settings *settings_;
		Map *currentMap_;
		AssetLibrary *assetLibrary_;

		//Not sure if this needs to be emptied as it is a pointer? to the last state in the state vector.
		//so if state vector gets deleted this sshould be pointing to a null memory location
		State* currentState_;

		std::vector<State*> states_;
		bool running_;
		bool fullscreen_;

		ALLEGRO_COLOR chosenColor_, chosenColorText_;

};
#endif