#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include "character.h"
#include "../MapEditor/map.h"

///////////////////make an items class
class Player
{
	public:
        Player();

		//sets
        void setLives(int num);
		void deductlives(int num);
		void deductlives();
		void addlives(int num);
		void addlives();
		void createPlayersCharacter();
		void drawPlayer();
		void passMap(Map mymap);

		int playerkeypress(ALLEGRO_EVENT ev);
		void playerupdate();


		Character getPlayersCharacter()
		{
			return *character_;
		}

    private:
		int score_;
		int lives_;
		Character *character_;
		ALLEGRO_EVENT ev_;
		bool KeyLeft_;
		bool KeyRight_;
		bool KeySpace_;
		Map maps_;
};
#endif