//editor main

#include <stdio.h>
#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>//fonts
#include <allegro5\allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "EditorEngine.h"
#include "Settings.h"
#include "Map.h"


using namespace StaticDLL;


using namespace std;
 


int main(int argc, char **argv)
{
	//ShowWindow( GetConsoleWindow(), SW_HIDE );//hide console window no body needs to see it now

	al_init();
	ALLEGRO_DISPLAY *display = NULL;
	display = al_create_display(800, 600);
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();//shapes and color???
	al_init_font_addon();
	al_init_ttf_addon();


	//////////////////////init stuff above

	//Load options at start from txt file...res/other options that are Saved later...?


	//http://gribblelab.org/CBootcamp/7_Memory_Stack_vs_Heap.html
	//Different way uses heap 
	//EditorEngine *e1 = new EditorEngine(display);//titlescreen state
	//e1->run();
	//uses stack


	//para test;
	//Herit *blah = new Herit();
	//fprintf(stderr, "test\n");
	//test.addState(blah);

	//while ( test.Running() )
	//{
	//	test.dostuff();
	//}
	

	Settings* GameSettings = new Settings;
	Map* CurrentMap = new Map(GameSettings);


	EditorEngine e1 = EditorEngine(display, GameSettings, CurrentMap);
	e1.Run();

	

	

	




	
	al_destroy_display(display);
	return 0;
}
