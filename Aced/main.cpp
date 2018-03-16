//Game main

#include <stdio.h>
#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>//fonts
#include <allegro5\allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include <allegro5\allegro_image.h>//shapes
#include "Engine/engine.h"



#include <memory>



#include "../AcedSharedDLL/World/Map.h"
#include "../AcedSharedDLL/Config/AssetLibrary.h"

#include "Settings/Settings.h"
#include "Settings/ImageLoader.h"



int main(int argc, char **argv)
{


	//ShowWindow( GetConsoleWindow(), SW_HIDE );//hide console window no body needs to see it now



	al_init();
	ALLEGRO_DISPLAY *display = NULL;
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();//shapes and color???
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	std::shared_ptr<Settings> settings(new Settings());
	display = al_create_display(settings->GetScreenWidth(), settings->GetScreenHeight());


	//////////////////////init stuff above

	//load options at start from txt file...res/other options that are saved later...?


	std::shared_ptr<AssetLibrary> assetLibrary(new AssetLibrary());
	std::shared_ptr<ImageLoader> imageLoader(new ImageLoader());
	assetLibrary->SetImageSetDictionary(imageLoader->GetImageSetDictionary());

	std::shared_ptr<Map> CurrentMap(new Map((std::shared_ptr<AcedSharedDLL::BaseSettings>)settings, display, assetLibrary));

	std::unique_ptr<Engine> mainEngine(new Engine(display, settings, CurrentMap, assetLibrary));
	mainEngine->Run();

	
	al_destroy_display(display);
	
	return 0;
}


