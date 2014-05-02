//Game main

#include <stdio.h>
#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>//fonts
#include <allegro5\allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "engine.h"

using namespace std;
 


int main(int argc, char **argv)
{
	ShowWindow( GetConsoleWindow(), SW_HIDE );//hide console window no body needs to see it now

	al_init();
	ALLEGRO_DISPLAY *display = NULL;
	display = al_create_display(800, 600);
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();//shapes and color???
	al_init_font_addon();
	al_init_ttf_addon();


	//////////////////////init stuff above

	//load options at start from txt file...res/other options that are saved later...?



	
	Engine *e1 = new Engine(display);//titlescreen state
	e1->run();


	

	

	




	
	al_destroy_display(display);
	return 0;
}
