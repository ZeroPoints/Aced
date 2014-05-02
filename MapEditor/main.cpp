//EDITOR main


//

//change mmm so some of the options go to subheader and are ignored...? possible rework

//

#include <stdio.h>
#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>//fonts
#include <allegro5\allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "map.h"
#include "../Aced/menumanager.h"


using namespace std;
 
enum KEYS{UP,DOWN,LEFT,RIGHT};

int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	bool done = false;
	bool redraw = true;
	bool keys[4] = {false,false,false,false};
	int mousex = 0;
	int mousey = 0;
	int value = 6;
	bool rightmousedown = false;
	bool leftmousedown = false;	
	int mapXoffset = 0;
	int oldmapXoffset = 0;
	int mapYoffset = 0;
	int oldmapYoffset = 0;
	int rightmouseX = 0;
	int rightmouseY = 0;
	int tileSize = 20;
	bool PlayerPlaced = false;
	bool PlayerSelected = false;	
	int menu = -1; //
	/*
	-1 = gameplay/nomenu
	0 = editor menu
	1 = width menu
	2 = height menu
	*/
	char width[10] = "";
	char thewidth[50] = "";
	char height[10] = "";
	char theheight[50] = "";
	char currentmapheight[50] = "10";
	char currentmapwidth[50] = "10";

	char currentdisplayheight[50] = "600";
	char currentdisplaywidth[50] = "800";

	/*fps counter
	int counter = 0;
	counter = counter + 1;
	char test[10];
	sprintf(test,"%d", counter/60);
	al_draw_text(font12, al_map_rgb(255,255,255), 100, 50, ALLEGRO_ALIGN_CENTRE, test);
	*/

	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
	//ShowWindow( GetConsoleWindow(), SW_HIDE );//hide console window no body needs to see it now

	display = al_create_display(atoi(currentdisplaywidth), atoi(currentdisplayheight));
	
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	al_install_keyboard();
	al_install_mouse();

	al_init_primitives_addon();//shapes and color???
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_FONT * font18 = al_load_font("arial.ttf", 18, 0);
	ALLEGRO_FONT * font12 = al_load_font("arial.ttf", 12, 0);
	ALLEGRO_FONT * font13 = al_load_font("arial.ttf", 13, 0);

	ALLEGRO_TIMER *timer = NULL;
	timer = al_create_timer(1.0/60);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	
	//map init
	Map *mymap = new Map();
	mymap->setMapWidth(atoi(currentmapwidth));
	mymap->setMapHeight(atoi(currentmapheight));
	mymap->setDisplayWidth(atoi(currentdisplaywidth));
	mymap->setDisplayHeight(atoi(currentdisplayheight));
	mymap->createTiles();//creates the vect of vects
	//initialize and set values
	for(int i = 0; i < mymap->getMapWidth(); i++)
	{
		for(int j = 0; j < mymap->getMapHeight(); j++)
		{
			mymap->getTiles()[i][j].setColour(al_map_rgb_f(0.5,0.5,0.5));//sets all tiles to grey
			mymap->getTiles()[i][j].setTileType(0);
			mymap->getTiles()[i][j].setTileX(i);
			mymap->getTiles()[i][j].setTileY(j);
		}
	}


	//menu creation

	MenuManager *mm = new MenuManager(1);
	int val = 0;

	ALLEGRO_COLOR chosencolor = al_map_rgb_f(0,1,0);//init chosecolor has to be after primitives line
	//so sets first color of editor to this color which is bright green (r g b)!!!



	//start loop for map editor
	al_start_timer(timer);
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue,&ev);
		
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{	
			if(menu == -1)//game hotkeys
			{
				switch(ev.keyboard.keycode)
				{
					case ALLEGRO_KEY_ESCAPE:						
						menu = 0;
						mm->setCurrentSelection();
						break;
				}
			}
			else if(menu == 0)
			{
				//keypress here
				val = mm->keyPress(ev);
				if(val == -1)//menu return
				{
					done = true;					
				}
				else if(val == 0)//save
				{
					mymap->saveMap(display);
				}
				else if(val == 1)//load
				{
					mymap->loadMap(display);
				}
				else if(val == 2)
				{
					menu = 1;
				}
				else if(val == 3)
				{
					menu = 2;	
				}
				else if(val == 4)
				{
					menu = -1;
				}
				else if(val == 5)
				{
					done = true;
				}
			}
			//----------------------------------------------------------------------------------------------------
			else if(menu == 1)//width menu hotkeys
			{
				val = mm->keyPress(ev);
				if(strlen(width) >= 0 && strlen(width) <= 8)
				{
					switch(ev.keyboard.keycode)
					{
						case ALLEGRO_KEY_0:
							strcat(width, "0");
							break;
						case ALLEGRO_KEY_1:
							strcat(width, "1");
							break;
						case ALLEGRO_KEY_2:
							strcat(width, "2");
							break;
						case ALLEGRO_KEY_3:
							strcat(width, "3"); 
							break;
						case ALLEGRO_KEY_4:
							strcat(width, "4");
							break;
						case ALLEGRO_KEY_5:
							strcat(width, "5");
							break;
						case ALLEGRO_KEY_6:
							strcat(width, "6");
							break;
						case ALLEGRO_KEY_7:
							strcat(width, "7");
							break;
						case ALLEGRO_KEY_8:
							strcat(width, "8");
							break;
						case ALLEGRO_KEY_9:
							strcat(width, "9");
							break;
					
					}
				}
				switch(ev.keyboard.keycode)
				{
					case ALLEGRO_KEY_BACKSPACE:
						if((int)(strlen(width)-1) >= 0)
						{
							width[strlen(width)-1] = '\0';
						}
						break;
				}
				if(val == -1 || val == 3)
				{
					menu = 0;
					mm->setMenu(menu);
					val = -2;
					mm->setCurrentSelection();
				}
				else if(val == 2)
				{					
					if(strcmp(width, "") == 0)
					{
						//ignore
					}	
					else if(strcmp(width, "0") == 0)
					{
						//ignore
					}
					else
					{
						strcpy(currentmapwidth, width);	
						mymap->resetMapWidth(atoi(currentmapwidth));
						menu = 0;
						mm->setMenu(menu);
						val = -2;
						mm->setCurrentSelection();
					}
				}
			}	
			//----------------------------------------------------------------------------------------------------
			else if(menu == 2)//height menu hotkeys
			{
				val = mm->keyPress(ev);
				if(strlen(height) >= 0 && strlen(height) <= 8)
				{
					switch(ev.keyboard.keycode)
					{
						case ALLEGRO_KEY_0:
							strcat(height, "0");
							break;
						case ALLEGRO_KEY_1:
							strcat(height, "1");
							break;
						case ALLEGRO_KEY_2:
							strcat(height, "2");
							break;
						case ALLEGRO_KEY_3:
							strcat(height, "3"); 
							break;
						case ALLEGRO_KEY_4:
							strcat(height, "4");
							break;
						case ALLEGRO_KEY_5:
							strcat(height, "5");
							break;
						case ALLEGRO_KEY_6:
							strcat(height, "6");
							break;
						case ALLEGRO_KEY_7:
							strcat(height, "7");
							break;
						case ALLEGRO_KEY_8:
							strcat(height, "8");
							break;
						case ALLEGRO_KEY_9:
							strcat(height, "9");
							break;						
					}
				}
				switch(ev.keyboard.keycode)
				{
					case ALLEGRO_KEY_BACKSPACE:
						if((int)(strlen(height)-1) >= 0)
						{
							height[strlen(height)-1] = '\0';
						}
						break;
				}
				if(val == -1 || val == 3)
				{
					menu = 0;
					mm->setMenu(menu);
					val = -2;
					mm->setCurrentSelection();
				}
				else if(val == 2)
				{
					if(strcmp(height, "") == 0)
					{
						//ignore//show error mssgs i guess
					}	
					else if(strcmp(height, "0") == 0)
					{
						//ignore
					}
					else
					{
						strcpy(currentmapheight, height);	
						mymap->resetMapHeight(atoi(currentmapheight));
						menu = 0;
						mm->setMenu(menu);
						val = -2;
						mm->setCurrentSelection();
					}
				}
			}	
		}
		
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			//close window if display is closed via X in top right corner
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			//every time mouse moves store its location in tile format which is why its divided by tilesize
			mousex = ev.mouse.x / tileSize;
			mousey = ev.mouse.y / tileSize;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{			
			if(ev.mouse.button & 2)
			{
				//when rightmouse no longer down store current offset so can re offset using this offset plus new offset later
				rightmousedown = false;
				oldmapXoffset = mapXoffset;
				oldmapYoffset = mapYoffset;
			}
			else if(ev.mouse.button & 1)
			{
				//when left mouse no longer down no need to keep drawing
				leftmousedown = false;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{			
			if(ev.mouse.button & 2)
			{
				//do right click stuff eg:moving map around
				rightmousedown = true;
				rightmouseX = mousex;
				rightmouseY = mousey;
			}
			else if(ev.mouse.button & 1)
			{
				if(mousey < 25)//if mouse is anywhere above color pallete flag leftmouse as down if it also without maps bounds
				{
					if(mousex >= 0 + mapXoffset && mousey >= 0 + mapYoffset && mousex < mymap->getMapWidth() + mapXoffset && mousey < mymap->getMapHeight() + mapYoffset)
					{	
						leftmousedown = true;						
					}
				}
				
				//choose paint color palette
				else if(mousex >= 0 && mousey >= 25 && mousex < 4 && mousey < 27)
				{
					PlayerSelected = false;
					if(mousex >= 0 && mousey >= 25 && mousex < 1 && mousey < 26)
					{
						chosencolor = al_map_rgb_f(1,0,0);
					}
					else if(mousex >= 1 && mousey >= 25 && mousex < 2 && mousey < 26)
					{
						chosencolor = al_map_rgb_f(0,1,0);
					}
					else if(mousex >= 2 && mousey >= 25 && mousex < 3 && mousey < 26)
					{
						chosencolor = al_map_rgb_f(0,0,1);
					}
					else if(mousex >= 0 && mousey >= 26 && mousex < 1 && mousey < 27)
					{
						chosencolor = al_map_rgb_f(1,1,0);
					}
					else if(mousex >= 1 && mousey >= 26 && mousex < 2 && mousey < 27)
					{
						chosencolor = al_map_rgb_f(0,1,1);
					}
					else if(mousex >= 2 && mousey >= 26 && mousex < 3 && mousey < 27)
					{
						chosencolor = al_map_rgb_f(1,0,1);
					}	
					else if(mousex >= 3 && mousey >= 25 && mousex < 4 && mousey < 26)
					{
						chosencolor = al_map_rgb_f(0.5,0.5,0.5);						
					}	
				}
				//detects if player is selected
				else if(mousex >= 39 && mousey >= 25 && mousex < 40 && mousey < 26)//for player
				{
					PlayerSelected = true;
				}				
			}
			
		}

		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{				
			//every 1/60th a second redraw screen
			redraw = true;
		}
		



		if(redraw && al_is_event_queue_empty(event_queue))
		{				
			redraw = false;
			
			
			
			if(menu == -1)
			{
				//move stuff around using right click
				if(rightmousedown == true)
				{
					mapXoffset = oldmapXoffset + mousex - rightmouseX;
					mapYoffset = oldmapYoffset + mousey - rightmouseY;
				}

				//when left mouse is clicked &/or held do rest of stuff
				if(leftmousedown == true)
				{
					//if mouse is clicked within map bounds continue
					if(mousex >= 0 + mapXoffset && mousey >= 0 + mapYoffset && mousex < mymap->getMapWidth() + mapXoffset && mousey < mymap->getMapHeight() + mapYoffset)
					{	
						//if player tile is selected process player stuff
						if(PlayerSelected == true)
						{
							//only if block is blank can player be placed//change this and below so blocks cant be placed upon a character
							if(mymap->getTiles()[mousex - mapXoffset][mousey - mapYoffset].getTileType() == 0)
							{
								//store players position for drawing
								mymap->setPlayerStartX(mousex - mapXoffset);
								mymap->setPlayerStartY(mousey - mapYoffset);
								PlayerPlaced = true;
							}
						}
						else //change color and change block type
						{
							mymap->getTiles()[mousex - mapXoffset][mousey - mapYoffset].setColour(chosencolor);//change color of tile
							//make grey as always 0...
							if(chosencolor.r == 0.5 && chosencolor.g == 0.5 && chosencolor.b == 0.5)
							{
								mymap->getTiles()[mousex - mapXoffset][mousey - mapYoffset].setTileType(0);//change tile to empty if grey selected
							}
							else
							{
								mymap->getTiles()[mousex - mapXoffset][mousey - mapYoffset].setTileType(1);//change tile to solid
							}
						}
					}
				}				
			}
			
			//draw all tiles with offset incase map is moved...offset init = 0 at start so its useless if map isnt moved
			
			mymap->setMapXOffset(mapXoffset);
			mymap->setMapYOffset(mapYoffset);
			mymap->drawMap();	

			//draw character if character is flaged for placed
			if(PlayerPlaced == true)
			{
				al_draw_filled_rectangle((mymap->getPlayerStartX() + mapXoffset)*20, (mymap->getPlayerStartY() + mapYoffset)*20, (mymap->getPlayerStartX() + 1 + mapXoffset)*20, (mymap->getPlayerStartY() + 1 + mapYoffset)*20, al_map_rgb_f(1,1,1));
			}

			//map border
			al_draw_rectangle((0 + mapXoffset)*20, (0 + mapYoffset)*20, (mymap->getMapWidth() + mapXoffset)*20,(mymap->getMapHeight() + mapYoffset)*20, al_map_rgb_f(0,0,0), 1);
					
			al_draw_rectangle(0,500,800,500,al_map_rgb_f(1,1,1),1);//line at bottom palette
			al_draw_filled_rectangle(0,500,800,600,al_map_rgb_f(0,0,0));//bottom box to be black to differentiate between map and palette

			//colors will change this to be easier to read or less lines
			al_draw_filled_rectangle(0,500,20,520,al_map_rgb_f(1,0,0));//1
			al_draw_filled_rectangle(20,500,40,520,al_map_rgb_f(0,1,0));//2
			al_draw_filled_rectangle(40,500,60,520,al_map_rgb_f(0,0,1));//3
			al_draw_filled_rectangle(0,520,20,540,al_map_rgb_f(1,1,0));//4
			al_draw_filled_rectangle(20,520,40,540,al_map_rgb_f(0,1,1));//5
			al_draw_filled_rectangle(40,520,60,540,al_map_rgb_f(1,0,1));//6
			al_draw_filled_rectangle(60,500,80,520,al_map_rgb_f(0.5,0.5,0.5));//7
			//colors
				
			al_draw_filled_rectangle(780,500,800,520,al_map_rgb_f(1,1,1));//draw player in bottom right for user to click on

			 
			//menus
			if(menu == 0 || menu == 1 || menu == 2)
			{
				mm->runMenu();	
				mm->menupdate();
				if(menu == 1)
				{
					sprintf(thewidth, "New width: %s", width);//this updates the screen with width as you type
					mm->getMenu()[menu].getMenuItems()[1].setMenuItemText(thewidth);
				}
				if(menu == 2)
				{
					sprintf(theheight, "New height: %s", height);//this updates the screen with height as you type
					mm->getMenu()[menu].getMenuItems()[1].setMenuItemText(theheight);
				}
			}



			//draw box around cursor location
			al_draw_rectangle(mousex * 20, mousey * 20, (mousex + 1) * 20, (mousey + 1) * 20, al_map_rgb_f(1,1,1), 1);
			
			

			//bread and butter
			al_flip_display();
			al_clear_to_color(al_map_rgb_f(0,0.5,0.25));//clears color to dark green to remove all back image
		}		
	}
	al_destroy_display(display);
	return 0;
}