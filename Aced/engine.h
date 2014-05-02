#ifndef ENGINE_H
#define ENGINE_H

#include <allegro5\allegro.h>
#include <vector>
#include "menumanager.h"
#include "player.h"
#include "../MapEditor/map.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes



//this files for hardcoding game engine stuff.
class Engine
{
    public:
        Engine(ALLEGRO_DISPLAY *display);

		void inGameKeyPress();
		void inGameUpdate();
		void inMenuKeyPress(ALLEGRO_EVENT ev);
		void inMenuUpdate();
        void run();
		void game();
		void menu();
		void options();
		int ingamemenu();
		void setState(int state);

    private:
		MenuManager *mm_;
		bool finished_;
		int currentstate_;
		int oldstate_;
		ALLEGRO_DISPLAY *display_;
		Map *map_;

};
#endif
