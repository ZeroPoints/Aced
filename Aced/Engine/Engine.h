#ifndef ENGINE_H
#define ENGINE_H




#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include <allegro5\allegro.h>
#include <vector>

#include <sstream>

#include "../AcedSharedDLL/LivingEntity/Player.h"
#include "../AcedSharedDLL/World/map.h"
#include "../AcedSharedDLL/Static/Definitions.h"

#include "../Aced/States/StateTemplates.h"
#include "../Aced/Settings/Settings.h"




using namespace AcedSharedDLL;


//this files for hardcoding game engine stuff.
class Engine
{
    public:
        Engine(ALLEGRO_DISPLAY *display, std::shared_ptr<Settings> &Settings, std::shared_ptr<Map> &currentMap, std::shared_ptr<AssetLibrary> &assetLibrary);

		~Engine()
        {
			//delete all states from memory
			int popLevel = states_.size();
			int i = 0;
			//check if this pops the last one off
			while(i < popLevel){
				states_.back()->CleanUp();
				//delete states_.back();
				states_.pop_back();
				popLevel--;
			}

			//fprintf(stderr,"A Editor Engine Destructed\n");
        }
		


        void Run();
		void CleanUp();
		void ChangeState(std::shared_ptr<State> &state, ALLEGRO_DISPLAY *display);
		void PushNewState(std::shared_ptr<State> &state);
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
		std::shared_ptr<Settings> settings_;
		std::shared_ptr<Map> currentMap_;
		std::shared_ptr<AssetLibrary> assetLibrary_;

		//Not sure if this needs to be emptied as it is a pointer? to the last state in the state vector.
		//so if state vector gets deleted this sshould be pointing to a null memory location
		std::shared_ptr<State> currentState_;

		std::vector<std::shared_ptr<State>> states_;
		bool running_;
		bool fullscreen_;

		std::stringstream timeOverlay_ ;


		ALLEGRO_COLOR chosenColor_, chosenColorText_;

};
#endif
