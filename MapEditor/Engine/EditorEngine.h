#ifndef EDITORENGINE_H
#define EDITORENGINE_H

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
#include "Config/AssetLibrary.h"




using namespace StaticDLL;


//this files for hardcoding game engine stuff.
class EditorEngine
{
    public:
        EditorEngine(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap, AssetLibrary *assetLibrary);


        ~EditorEngine()
        {
			fprintf(stderr, "A Editor Engine Destructed Start\n");

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

			fprintf(stderr,"A Editor Engine Destructed End\n");
        }
		


		bool Running() { return running_; }
		void ChangeState(State* state, ALLEGRO_DISPLAY *display);
		void CleanUp();
		void Draw();
		void KeyPress();
		void PopPushState();
		void PopState();
		void PopStateToFirst();
		void PushNewState(State* state);
		void PushState();
		void Quit() { running_ = false; }
		void Update();
        void Run();

    private:
		ALLEGRO_COLOR chosenColor_, chosenColorText_;
		ALLEGRO_DISPLAY *display_;

		AssetLibrary *assetLibrary_;
		//ImageLoader *imageLoader_;
		Map *currentMap_;
		Settings *settings_;
		State* currentState_;
		bool finished_;
		bool fullscreen_;
		bool running_;
		std::vector<State*> states_;






};
#endif
