#ifndef EDITORENGINE_H
#define EDITORENGINE_H

#include <allegro5\allegro.h>
#include <vector>
#include "Player.h"
#include "map.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "Definitions.h"
#include "State.h"
#include "Settings.h"
#include <StateTemplates.h>



using namespace StaticDLL;


//this files for hardcoding game engine stuff.
class EditorEngine
{
    public:
        EditorEngine(ALLEGRO_DISPLAY *display, Settings *Settings, Map *CurrentMap);
		
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

		State* currentState_;

		std::vector<State*> states_;
		bool running_;
		bool fullscreen_;

		ALLEGRO_COLOR chosenColor_;

};
#endif
