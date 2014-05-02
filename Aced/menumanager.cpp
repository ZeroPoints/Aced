
#include "menumanager.h"



/////menumanager controls which actual menu should be drawn
MenuManager::MenuManager(int menutype)//menutype is for program to differentiate between game menu and editor menu code
{
	menutype_ = menutype;

	if(menutype_ == 0)
	{
		gamemenu();
	}
	else if(menutype_ == 1)
	{
		editormenu();
	}

}

void MenuManager::setCurrentSelection()
{


	currentselection_ = 0;	

	while(menu_[menunumber_].getMenuItems()[currentselection_].getMenuItemTargetable() == false)
	{
		currentselection_++;
	}



}


void MenuManager::runMenu()//this runs the menus drawing function...draws only the current menu.
{
	menu_[menunumber_].drawmenu();	
}

void MenuManager::setMenu(int menunumber)//Tells the program what menu is the menu to be drawn
{
	menunumber_ = menunumber;
}


int MenuManager::keyPress(ALLEGRO_EVENT ev)
{
	//down arrow up arrow per vector items....enter to submit or esc to leave menu/submenu so  (menutype - 1)...title = 0, options = 1 dunno yet
	ev_ = ev;
	BOOL doneflag = false;

	int val = -2;
	if(ev_.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch(ev_.keyboard.keycode)
		{

			case ALLEGRO_KEY_UP://choose later....

				currentselection_--;
				
				while(doneflag == false)
				{
					if(currentselection_ < 0)
					{
						currentselection_ = menu_[menunumber_].getMenuItems().size() - 1;
					}
					if(menu_[menunumber_].getMenuItems()[currentselection_].getMenuItemTargetable() == true)
					{
						doneflag = true;
					}
					while(menu_[menunumber_].getMenuItems()[currentselection_].getMenuItemTargetable() == false)
					{
						currentselection_--;
						if(currentselection_ < 0)
						{
							currentselection_ = menu_[menunumber_].getMenuItems().size() - 1;
						}
					}
					
				}
				
				
				break;
			case ALLEGRO_KEY_DOWN://choose later....
				
				currentselection_++;
				
				while(doneflag == false)
				{
					if(currentselection_ >= menu_[menunumber_].getMenuItems().size())
					{
						currentselection_ = 0;
					}
					if(menu_[menunumber_].getMenuItems()[currentselection_].getMenuItemTargetable() == true)
					{
						doneflag = true;
					}
					while(menu_[menunumber_].getMenuItems()[currentselection_].getMenuItemTargetable() == false)
					{
						currentselection_++;
						if(currentselection_ >= menu_[menunumber_].getMenuItems().size())
						{
							currentselection_ = 0;
						}
					}					
				}

				break;
			case ALLEGRO_KEY_ENTER://choose later....
				val = currentselection_;
				break;

			//case ALLEGRO_KEY_ESCAPE://choose later....
			//	val = -1;
			//	break;
		}
	}

	if(ev_.type == ALLEGRO_EVENT_KEY_UP)
	{
		switch(ev_.keyboard.keycode)
		{
			case ALLEGRO_KEY_ESCAPE:						
				//quit
				val = -1;
				break;
		}
	}




	return val;
}

void MenuManager::menupdate()
{
	//chuck a drawing of a cube...
	y_ = menu_[menunumber_].getMenuItems()[currentselection_].getMenuItemY();

	int test = menu_[menunumber_].getMenuX() + menu_[menunumber_].getMenuWidth() - 25;
	al_draw_filled_rectangle(test, y_ + 7, test + 20, y_ + 27, al_map_rgb(0,125,255));	
	al_draw_rectangle(test, y_ + 7, test + 20, y_ + 27, al_map_rgb(255,255,255),1);
	
}

//////////////////work in here and get current menu system in this normal game so add flags for true false for targetable 
void MenuManager::gamemenu()
{
	

	//this is a test
	std::vector<Menu> menu(3);//N is how many menus you want to create
	menu_ = menu;
	y_ = 0;
	currentselection_ = 0;	
	menunumber_ = 0;//init menunumber as 0 for title menu...1 will be options menu mmmmm...2 will ingame menu
	//

	//
	//
	//init menu to have N menu items
	menu_[0].initMenuItems(4);//main menu//start-load-options-quit
	menu_[1].initMenuItems(3);//options menu//resolution-return--save//dunno
	menu_[2].initMenuItems(4);//ingame-menu//resume-save-options-quit to main
	//menu items init done
	//set the values if yuo want	
	menu_[0].setMenuHeader("Title");
	menu_[1].setMenuHeader("Options");
	menu_[2].setMenuHeader("Menu");

	
	
	//not sure if i need these...will sort out later good to have for now though...maybe...atm looks like i dont need it...keypress() return int val sorts out who belongs to who for now.
	menu_[1].setSubMenuOf(0);
	menu_[1].setSubMenuOf(2);




	menu_[0].getMenuItems()[0].setMenuItemText("Start");
	menu_[0].getMenuItems()[1].setMenuItemText("Load");
	menu_[0].getMenuItems()[2].setMenuItemText("Options");
	menu_[0].getMenuItems()[3].setMenuItemText("Quit");

	menu_[1].getMenuItems()[0].setMenuItemText("Resolution");
	menu_[1].getMenuItems()[1].setMenuItemText("Apply");
	menu_[1].getMenuItems()[2].setMenuItemText("Return"); 

	menu_[2].getMenuItems()[0].setMenuItemText("Resume");
	menu_[2].getMenuItems()[1].setMenuItemText("Save");
	menu_[2].getMenuItems()[2].setMenuItemText("Options");
	menu_[2].getMenuItems()[3].setMenuItemText("Exit");


	

	/*menu_[0].setMenuX(300);
	menu_[0].setMenuY(100);
	menu_[0].setMenuWidth(200);
	menu_[0].setMenuHeight(400);
	
	menu_[0].setMenuHeaderX(300);
	menu_[0].setMenuHeaderY(50);
	menu_[0].setMenuHeaderWidth(200);
	menu_[0].setMenuHeaderHeight(50);*/


	for(int j = 0; j < menu_.size(); j++)
	{
		menu_[j].setMenuX(300);
		menu_[j].setMenuY(100);
		menu_[j].setMenuWidth(250);
		menu_[j].setMenuHeight(400);
	
		menu_[j].setMenuHeaderX(300);
		menu_[j].setMenuHeaderY(50);
		menu_[j].setMenuHeaderWidth(250);
		menu_[j].setMenuHeaderHeight(50);


		int i = 0;
		int xloc = 425;
		int yloc = 110;
		int yspacing = 50;
	
		for(i = 0; i < menu_[j].getMenuItems().size(); i++)
		{
			//printf("%i\n",yloc);
			menu_[j].getMenuItems()[i].setMenuItemX(xloc);
			menu_[j].getMenuItems()[i].setMenuItemY(yloc);
			menu_[j].getMenuItems()[i].setMenuItemTargetable(true);
			yloc = yloc + yspacing;
		}
		menu_[j].setMenuHeight(yloc-menu_[j].getMenuY());
		//printf("%i",yloc);


	}



}


////////////////////////////EDITOR STUFF BELOW------------------------------------------------------------------------------------------------------

void MenuManager::editormenu()
{
	std::vector<Menu> menu(3);//N is how many menus you want to create
	menu_ = menu;
	y_ = 0;
	currentselection_ = 0;	
	menunumber_ = 0;

	//init menu to have N menu items
	menu_[0].initMenuItems(6);//main menu//start-load-options-quit
	menu_[1].initMenuItems(4);//width
	menu_[2].initMenuItems(4);//height
	//menu items init done
	//set the values if yuo want	
	menu_[0].setMenuHeader("Editor");
	menu_[1].setMenuHeader("Width");
	menu_[2].setMenuHeader("Height");


	
	menu_[0].getMenuItems()[0].setMenuItemText("Save");
	menu_[0].getMenuItems()[1].setMenuItemText("Load");
	menu_[0].getMenuItems()[2].setMenuItemText("Map Width");
	menu_[0].getMenuItems()[3].setMenuItemText("Map Height");
	menu_[0].getMenuItems()[4].setMenuItemText("Return");
	menu_[0].getMenuItems()[5].setMenuItemText("Quit");


	
	menu_[1].getMenuItems()[0].setMenuItemText("Current width:");//untargetable
	menu_[1].getMenuItems()[1].setMenuItemText("New width:");
	menu_[1].getMenuItems()[2].setMenuItemText("Save");
	menu_[1].getMenuItems()[3].setMenuItemText("Return");
	
	menu_[2].getMenuItems()[0].setMenuItemText("Current height:");//untargetable
	menu_[2].getMenuItems()[1].setMenuItemText("New height:");
	menu_[2].getMenuItems()[2].setMenuItemText("Save");
	menu_[2].getMenuItems()[3].setMenuItemText("Return");





	for(int j = 0; j < menu_.size(); j++)
	{
		menu_[j].setMenuX(300);
		menu_[j].setMenuY(100);
		menu_[j].setMenuWidth(250);
		menu_[j].setMenuHeight(400);
	
		menu_[j].setMenuHeaderX(300);
		menu_[j].setMenuHeaderY(50);
		menu_[j].setMenuHeaderWidth(250);
		menu_[j].setMenuHeaderHeight(50);


		int i = 0;
		int xloc = 425;
		int yloc = 110;
		int yspacing = 50;
	
		for(i = 0; i < menu_[j].getMenuItems().size(); i++)
		{
			//printf("%i\n",yloc);
			menu_[j].getMenuItems()[i].setMenuItemX(xloc);
			menu_[j].getMenuItems()[i].setMenuItemY(yloc);
			menu_[j].getMenuItems()[i].setMenuItemTargetable(true);
			yloc = yloc + yspacing;
		}
		menu_[j].setMenuHeight(yloc-menu_[j].getMenuY());
		//printf("%i",yloc);

		menu_[1].getMenuItems()[0].setMenuItemTargetable(false);//untargetable
		menu_[2].getMenuItems()[0].setMenuItemTargetable(false);//untargetable

	}

}
