#include "Menu.h"
#include "menuitem.h"



namespace StaticDLL{

	



	#pragma region menusettings
	//this is menu stuff
	void Menu::SetMenuHeight(int menuHeight)
	{
		menuHeight_ = menuHeight;
	}

	void Menu::SetMenuWidth(int menuWidth)
	{
		menuWidth_ = menuWidth;
	}

	void Menu::SetMenuY(int menuY)
	{
		menuY_ = menuY;
	}

	void Menu::SetMenuX(int menuX)
	{
		menuX_ = menuX;
	}
	#pragma endregion menusettings


	#pragma region menuheader 
	//menu header stuff
	void Menu::SetMenuHeaderHeight(int menuHeaderHeight)
	{
		menuHeaderHeight_ = menuHeaderHeight;
	}

	void Menu::SetMenuHeaderWidth(int menuHeaderWidth)
	{
		menuHeaderWidth_ = menuHeaderWidth;
	}

	void Menu::SetMenuHeaderY(int menuHeaderY)
	{
		menuHeaderY_ = menuHeaderY;
	}

	void Menu::SetMenuHeaderX(int menuHeaderX)
	{
		menuHeaderX_ = menuHeaderX;
	}

	void Menu::SetMenuHeader(char *menuHeader)
	{
		menuHeader_ = menuHeader;
		//strcpy_s(menuHeader_, menuHeader);
	}
	#pragma endregion menuheader


	#pragma region submenuheader //menu sub header stuff

	void Menu::SetSubMenuHeaderHeight(int menuSubHeaderHeight)
	{
		menuSubHeaderHeight_ = menuSubHeaderHeight;
	}

	void Menu::SetSubMenuHeaderWidth(int menuSubHeaderWidth)
	{
		menuSubHeaderWidth_ = menuSubHeaderWidth;
	}

	void Menu::SetSubMenuHeaderY(int menuSubHeaderY)
	{
		menuSubHeaderY_ = menuSubHeaderY;
	}

	void Menu::SetSubMenuHeaderX(int menuSubHeaderX)
	{
		menuSubHeaderX_ = menuSubHeaderX;
	}

	void Menu::SetSubMenuHeader(char menuSubHeader[])
	{
		strcpy_s(menuSubHeader_, menuSubHeader);
	}
	#pragma endregion submenuheader


	void Menu::SetSettings(Settings *settings)
	{
		settings_ = settings;
	}


	void Menu::SetMap(Map *currentMap)
	{
		currentMap_ = currentMap;
	}
	////this function is for menumanager
	//void Menu::InitMenuItems()
	//{
	//	std::vector<MenuItem> menuItems(10);
	//	menuItems_ = menuItems;
	//}



	void Menu::SetId(EnumDLL::STATES newId)
	{
		Id_ = newId;
	}




	void Menu::AddMenuItem(MenuItem* newMenuItem)
	{
		menuItems_.push_back(newMenuItem);
	}



	void Menu::SetCurrentSelection()
	{
		auto i = 0;

		currentSelection_ = i;
		while(GetMenuItems()[i]->GetMenuItemTargetable() == false)
		{
			i++;
			currentSelection_ = i;	
		}
	}

	void Menu::CalculateMenuSelectorCubePosition()
	{
		SetSelectItemY(GetMenuItems()[GetCurrentSelection()]->GetMenuItemY() + 7);
		SetSelectItemX(GetMenuX() + GetMenuWidth() - 25);
		SetSelectItemHeight(20);
		SetSelectItemWidth(20);
	}

	void Menu::DrawMenuSelectorCube()
	{
		al_draw_filled_rectangle(GetSelectItemX(), GetSelectItemY(), GetSelectItemX() + GetSelectItemWidth(), GetSelectItemY() + GetSelectItemHeight(), al_map_rgb(0,125,255));	
		al_draw_rectangle(GetSelectItemX(), GetSelectItemY(), GetSelectItemX() + GetSelectItemWidth(), GetSelectItemY() + GetSelectItemHeight(), al_map_rgb(255,255,255),1);
	}

	void Menu::DrawMenu(){
		al_draw_filled_rectangle(menuHeaderX_, menuHeaderY_, menuHeaderX_ + menuHeaderWidth_, menuHeaderY_ + menuHeaderHeight_, al_map_rgb(0,125,255));	
		al_draw_rectangle(menuHeaderX_, menuHeaderY_, menuHeaderX_ + menuHeaderWidth_, menuHeaderY_ + menuHeaderHeight_, al_map_rgb(255,255,255),1);
		al_draw_text(font30_, al_map_rgb(255,255,255), menuHeaderX_ + (menuHeaderWidth_/2), menuHeaderY_ + 10, ALLEGRO_ALIGN_CENTRE, menuHeader_);//change the 10 into a value eg: (menuheaderheight-fontsize)/2 that will work

		//menu drawing rectangle
		al_draw_filled_rectangle(menuX_, menuY_, menuX_ + menuWidth_, menuY_ + menuHeight_, al_map_rgb(125,0,255));				
		al_draw_rectangle(menuX_, menuY_, menuX_ + menuWidth_, menuY_ + menuHeight_, al_map_rgb(255,255,255),1);


		for(int i = 0; i < menuItems_.size(); i++)
		{
			GetMenuItems()[i]->drawMenuItem();
		}
	}



	//down arrow up arrow per vector items....enter to submit or esc to leave menu/submenu so  (menutype - 1)...title = 0, options = 1 dunno yet
	////////////---------------------23/11 --- was changing my menus to not use numbers so i can reuse this for entering number in menu...so return menuname
	EnumDLL::STATES Menu::KeyPress(ALLEGRO_EVENT *ev)
	{
		BOOL doneflag = false;
		EnumDLL::STATES val = EnumDLL::STATES::NONE;
		
		if(ev->type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev->keyboard.keycode)
			{
				case ALLEGRO_KEY_UP://choose later....
					currentSelection_--;
					while(doneflag == false)//helps to loop and to not select untarGetable items
					{
						if(currentSelection_ < 0)
						{
							currentSelection_ = GetMenuItems().size() - 1;
						}
						//////////////////////Check this maybe refucktor the while and if
						//Matt-TODO:
						if(GetMenuItems()[currentSelection_]->GetMenuItemTargetable() == true)
						{
							doneflag = true;
						}
						while(GetMenuItems()[currentSelection_]->GetMenuItemTargetable() == false)
						{
							currentSelection_--;
							if(currentSelection_ < 0)
							{
								currentSelection_ = GetMenuItems().size() - 1;
							}
						}					
					}
					break;
				case ALLEGRO_KEY_DOWN://choose later....
					currentSelection_++;
					while(doneflag == false)//helps to loop and to not select untarGetable items
					{
						if(currentSelection_ >= GetMenuItems().size())
						{
							currentSelection_ = 0;
						}
						if(GetMenuItems()[currentSelection_]->GetMenuItemTargetable() == true)
						{
							doneflag = true;
						}
						while(GetMenuItems()[currentSelection_]->GetMenuItemTargetable() == false)
						{
							currentSelection_++;
							if(currentSelection_ >= GetMenuItems().size())
							{
								currentSelection_ = 0;
							}
						}					
					}
					break;

				case ALLEGRO_KEY_ENTER://choose later....
					val = GetMenuItems()[currentSelection_]->GetId();
					break;
				default:
					break;
			}
		}
		else if(ev->type == ALLEGRO_EVENT_KEY_CHAR)
		{
			if(GetMenuItems()[currentSelection_]->GetMenuItemProperty() != nullptr && ev->keyboard.unichar > 0)
			{
				ALLEGRO_USTR *test = al_ustr_new("");
				al_ustr_append_chr(test, ev->keyboard.unichar);
				GetMenuItems()[currentSelection_]->SetMenuItemProperty(test);
				al_ustr_free(test);
			}
		}



		if(ev->type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev->keyboard.keycode)
			{
				case ALLEGRO_KEY_ESCAPE:						
					//quit
					val = EnumDLL::STATES::RETURN;
					break;
			}
		}



		
		return val;
	}




}