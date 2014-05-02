#include "engine.h"







Engine::Engine(ALLEGRO_DISPLAY *display)
{
	//init
	display_ = display;
	finished_ = false;
	mm_ = new MenuManager(0);//0 for game menu not editor menu
	currentstate_ = -5;
	oldstate_ = 0;
	//crate states one for each thing???do i even need this i will keep it...
	//setstate push state pop state use this to try get ingame to ingame menu and back???
}




void Engine::run()//hmmm
{
	while(!finished_)
	{
		if(currentstate_ == 0)
		{
			game();
		}
		else if(currentstate_ == -5)
		{
			menu();
		}
		else if(currentstate_ == 2)//draw options crap
		{
			finished_ = true;
		}
		else if(currentstate_ == 3)//quit
		{
			finished_ = true;
		}
		else if(currentstate_ == 1)//load
		{
			finished_ = true;
		}
			
	}
}


void Engine::game()
{
	//INIT-------------------------------------------
	//load map
	//
	map_ = new Map();
	map_->loadMap(display_);
	//
	//
	Player *p1 = new Player();
	//
	int val = -2;

	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	bool redraw = true;
	bool done = false;


	ALLEGRO_TIMER *timer = NULL;
	timer = al_create_timer(1.0/60);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display_));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));



	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	ALLEGRO_FONT * font30_;
	font30_ = al_load_font("arial.ttf", 20, 0);
	int framesps = 0;
	int counter = 0;

	al_start_timer(timer);
	//-----------------------------------------
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue,&ev);
		
		
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			//close window if display is closed via X in top right corner
			done = true;
			finished_ = true;
		}
		

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{				
			//every 1/60th a second redraw screen
			redraw = true;
		}
		
		
		//keypress here for game stuff so left right space esc
		//keypress routine from player class
		//ifs to say what happens if esc pushed...
		//if val == -1 then currentstate is 3 done = true//dont know if i want to set done = true yet as i might want to come back to same state within game...will going to menu then back in return state or clean state//since i load map it looks like clean state atm
		val = p1->playerkeypress(ev);
		if(val == -1)
		{			
			al_stop_timer(timer);			
			//need to finish keypresses registering?ASDFNKGAFDSGNSDFFgmn i dunno ye may aswell fuck humans
			val = ingamemenu();//stick in here till need
			if(val == 3)//quits game if x was pushed within the menu
			{
				done = true;
				finished_ = true;
			}
			if(val == -5)
			{
				done = true;
				setState(val);
			}
			al_flush_event_queue(event_queue);
			al_start_timer(timer);

			//load ingamemenu();
			//done = true;
			//setState(val);//this exits val needs to be something else
		}



		//drawing routine
		if(redraw && al_is_event_queue_empty(event_queue))
		{				
			redraw = false;

			//passmap in to player for offsets and collision
			p1->passMap(*map_);
			//update here
			p1->playerupdate();
			

			//draw here
			map_->drawMap();
			p1->drawPlayer();


			al_draw_textf(font30_, al_map_rgb(255,255,255), 300, 100, ALLEGRO_ALIGN_CENTRE, "%d" , ev.timer.count/60);


			//bread and butter
			al_flip_display();
			al_clear_to_color(al_map_rgb_f(0,0.5,0.25));//clears color to dark green to remove all back image
			counter++;
		}		
	}


	//clear memory

}



void Engine::menu()
{
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	bool redraw = true;
	bool done = false;
	int val = -2;

	ALLEGRO_TIMER *timer = NULL;
	timer = al_create_timer(1.0/60);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display_));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	mm_->setMenu(0);
	mm_->setCurrentSelection();

	al_start_timer(timer);
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue,&ev);
		
		
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			//close window if display is closed via X in top right corner
			done = true;
			finished_ = true;
		}
		

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{				
			//every 1/60th a second redraw screen
			redraw = true;
		}
		
		
		//keypress here
		val = mm_->keyPress(ev);
		if(val == -1 || val == 3)//program quit
		{
			done = true;
			setState(3);
		}
		else if(val == 0)//game start
		{
			done = true;
			setState(0);
		}
		else if(val == 1)
		{
			//load map
			//sort later...probs load map...then start map after load for now...
		}
		else if(val == 2)
		{
			//load options menu stuff//not wokring atm
			done = true;
			setState(2);
		}




		//drawing routine
		if(redraw && al_is_event_queue_empty(event_queue))
		{				
			redraw = false;


			
			

			//draw here
			mm_->runMenu();
			//update here
			mm_->menupdate();

			//bread and butter
			al_flip_display();
			al_clear_to_color(al_map_rgb_f(0,0.5,0.25));//clears color to dark green to remove all back image
		}		
	}

	//clear memory of this stuff

}



int Engine::ingamemenu()
{
	mm_->setMenu(2);
	mm_->setCurrentSelection();

	ALLEGRO_EVENT_QUEUE *event_queue2 = NULL;
	bool redraw = true;
	bool done = false;
	int val = -2;

	ALLEGRO_FONT * font30_;
	font30_ = al_load_font("arial.ttf", 20, 0);

	ALLEGRO_TIMER *timer2 = NULL;
	timer2 = al_create_timer(1.0/60);
	event_queue2 = al_create_event_queue();
	al_register_event_source(event_queue2, al_get_keyboard_event_source());
	al_register_event_source(event_queue2, al_get_mouse_event_source());
	al_register_event_source(event_queue2, al_get_display_event_source(display_));
	al_register_event_source(event_queue2, al_get_timer_event_source(timer2));



	al_start_timer(timer2);
	while(!done)
	{
		ALLEGRO_EVENT ev2;
		al_wait_for_event(event_queue2,&ev2);


		//keypress here
		val = mm_->keyPress(ev2);
		if(val == -1 || val == 0)//return to game if esc or option 1 chosen
		{
			val = 0;
			done = true;
			al_destroy_event_queue(event_queue2);//destroy whatever was created i guess
		}
		else if(val == 1)//save maybe a laod aswell
		{
			done = true;//do something 
		}
		else if(val == 2)//ingame options
		{
			
		}
		else if(val == 3)
		{
			done = true;		
			val = -5;
		}

		if(ev2.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			//close window if display is closed via X in top right corner
			done = true;		
			val = 3;
		}



		if(ev2.type == ALLEGRO_EVENT_TIMER)
		{				
			//every 1/60th a second redraw screen
			redraw = true;
		}


		//drawing routine
		if(redraw && al_is_event_queue_empty(event_queue2))
		{				
			redraw = false;


			
			al_draw_textf(font30_, al_map_rgb(255,255,255), 500, 200, ALLEGRO_ALIGN_CENTRE, "%d" , ev2.timer.count/60);

			//draw here
			mm_->runMenu();
			//update here
			mm_->menupdate();

			//bread and butter
			al_flip_display();
			al_clear_to_color(al_map_rgb_f(0,0.5,0.25));//clears color to dark green to remove all back image
		}	
	}

	//
	//ima need to clear the memory
	return val;
}

void Engine::options()
{

}

void Engine::setState(int state)
{
	oldstate_ = currentstate_;
	currentstate_ = state;
}