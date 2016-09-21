//Game main

#include <stdio.h>
#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>//fonts
#include <allegro5\allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include <allegro5\allegro_image.h>//shapes
#include "Engine/engine.h"
#include "Config/Settings.h"
#include "World/Map.h"
#include "Config/AssetLibrary.h"


using namespace StaticDLL;

using namespace std;
 


int main(int argc, char **argv)
{
	//ShowWindow( GetConsoleWindow(), SW_HIDE );//hide console window no body needs to see it now
	//Load options at start from txt file...res/other options that are Saved later...?
	Settings GameSettings = Settings();



	al_init();
	ALLEGRO_DISPLAY *display = NULL;
	display = al_create_display(GameSettings.GetScreenWidth(), GameSettings.GetScreenHeight());
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();//shapes and color???
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	//////////////////////init stuff above

	//load options at start from txt file...res/other options that are saved later...?


	AssetLibrary assets = AssetLibrary();

	Map CurrentMap = Map(&GameSettings, display, &assets);
	




	Engine e1 = Engine(display, &GameSettings, &CurrentMap, &assets);//titlescreen state
	e1.Run();


	
	
	al_destroy_display(display);
	
	return 0;
}


