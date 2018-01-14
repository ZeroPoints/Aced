#include "Menu.h"



namespace AcedSharedDLL{



	Menu::Menu(std::shared_ptr<BaseSettings> &settings) {
		SetSettings(settings);

		//fprintf(stderr, "A Menu Created\n");
	}
	 
	Menu::~Menu() {
		/*al_destroy_font(font30_);
		for (MenuItem* item : menuItems_)
		{
			delete item;
			item = nullptr;
		}*/
		//fprintf(stderr, "A Menu Destructed\n");
		return;
	}
	




	//-----------------------------------------------------------------------------------------------------

	//Gets

	 int Menu::GetCurrentSelection() {
		return currentSelection_;
	};
	 std::shared_ptr<BaseSettings> &Menu::GetSettings() {
		return settings_;
	}
	 std::shared_ptr<Map> &Menu::GetMap() {
		return currentMap_;
	}
	 STATES Menu::GetId()
	{
		return Id_;
	}
	 int Menu::GetMenuHeight()
	{
		return menuHeight_;
	}
	 int Menu::GetMenuWidth()
	{
		return menuWidth_;
	}
	 int Menu::GetMenuX()
	{
		return menuX_;
	}
	 int Menu::GetMenuY()
	{
		return menuY_;
	}
	 std::string Menu::GetMenuHeader()
	{
		return menuHeader_;
	}
	 int Menu::GetSelectItemY() {
		return selectItemY_;
	}
	 int Menu::GetSelectItemX() {
		return selectItemX_;
	}
	 int Menu::GetSelectItemWidth() {
		return selectItemWidth_;
	}
	 int Menu::GetSelectItemHeight() {
		return selectItemHeight_;
	}
	 ALLEGRO_FONT* Menu::GetFont()
	{
		return font30_;
	}
	 std::vector<std::shared_ptr<MenuItem>> &Menu::GetMenuItems()
	{
		return menuItems_;
	}

	//-----------------------------------------------------------------------------------------------------

	//Sets



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

	void Menu::SetMenuHeader(const std::string &menuHeader)
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

	void Menu::SetSubMenuHeader(const std::string &menuSubHeader)
	{
		menuSubHeader_ = menuSubHeader;
		//strcpy_s(menuSubHeader_, menuSubHeader);
	}
#pragma endregion submenuheader



	void Menu::SetSettings(std::shared_ptr<BaseSettings> &settings)
	{
		settings_ = settings;
	}
	void Menu::SetMap(std::shared_ptr<Map> &currentMap)
	{
		currentMap_ = currentMap;
	}
	void Menu::SetId(STATES newId)
	{
		Id_ = newId;
	}
	void Menu::SetCurrentSelection()
	{
		auto i = 0;

		currentSelection_ = i;
		while (GetMenuItems()[i]->GetMenuItemTargetable() == false)
		{
			i++;
			currentSelection_ = i;
		}
	}
	void Menu::SetSelectItemY(int val) {
		selectItemY_ = val;
	}
	void Menu::SetSelectItemX(int val) {
		selectItemX_ = val;
	}
	void Menu::SetSelectItemWidth(int val) {
		selectItemWidth_ = val;
	}
	void Menu::SetSelectItemHeight(int val) {
		selectItemHeight_ = val;
	}
	void Menu::SetFont(ALLEGRO_FONT* currentFont) {
		font30_ = currentFont;
	}


	//-----------------------------------------------------------------------------------------------------

	//Draws



	void Menu::DrawMenuSelectorCube()
	{
		al_draw_filled_rectangle(GetSelectItemX(), GetSelectItemY(), GetSelectItemX() + GetSelectItemWidth(), GetSelectItemY() + GetSelectItemHeight(), al_map_rgb(0, 125, 255));
		al_draw_rectangle(GetSelectItemX(), GetSelectItemY(), GetSelectItemX() + GetSelectItemWidth(), GetSelectItemY() + GetSelectItemHeight(), al_map_rgb(255, 255, 255), 1);
	}

	void Menu::DrawMenu() {
		al_draw_filled_rectangle(menuHeaderX_, menuHeaderY_, menuHeaderX_ + menuHeaderWidth_, menuHeaderY_ + menuHeaderHeight_, al_map_rgb(0, 125, 255));
		al_draw_rectangle(menuHeaderX_, menuHeaderY_, menuHeaderX_ + menuHeaderWidth_, menuHeaderY_ + menuHeaderHeight_, al_map_rgb(255, 255, 255), 1);
		al_draw_text(font30_, al_map_rgb(255, 255, 255), menuHeaderX_ + (menuHeaderWidth_ / 2), menuHeaderY_ + 10, ALLEGRO_ALIGN_CENTRE, menuHeader_.c_str());//change the 10 into a value eg: (menuheaderheight-fontsize)/2 that will work

																																					  //menu drawing rectangle
		al_draw_filled_rectangle(menuX_, menuY_, menuX_ + menuWidth_, menuY_ + menuHeight_, al_map_rgb(125, 0, 255));
		al_draw_rectangle(menuX_, menuY_, menuX_ + menuWidth_, menuY_ + menuHeight_, al_map_rgb(255, 255, 255), 1);


		for (int i = 0; i < menuItems_.size(); i++)
		{
			GetMenuItems()[i]->DrawMenuItem();
		}
	}



	//-----------------------------------------------------------------------------------------------------

	//Misc




	void Menu::AddMenuItem(std::shared_ptr<MenuItem> &newMenuItem)
	{
		menuItems_.push_back(newMenuItem);
	}



	void Menu::CalculateMenuSelectorCubePosition()
	{
		SetSelectItemY(GetMenuItems()[GetCurrentSelection()]->GetMenuItemY() + 7);
		SetSelectItemX(GetMenuX() + GetMenuWidth() - 25);
		SetSelectItemHeight(Constants::TileSize());
		SetSelectItemWidth(Constants::TileSize());
	}





	//down arrow up arrow per vector items....enter to submit or esc to leave menu/submenu so  (menutype - 1)...title = 0, options = 1 dunno yet
	STATES Menu::KeyPress(ALLEGRO_EVENT *ev)
	{
		BOOL doneflag = false;
		STATES val = STATES::NONE;

		if (ev->type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev->keyboard.keycode)
			{
			case ALLEGRO_KEY_UP://choose later....
				currentSelection_--;
				while (doneflag == false)//helps to loop and to not select untarGetable items
				{
					if (currentSelection_ < 0)
					{
						currentSelection_ = GetMenuItems().size() - 1;
					}
					//////////////////////Check this maybe refucktor the while and if
					//Matt-TODO:
					if (GetMenuItems()[currentSelection_]->GetMenuItemTargetable() == true)
					{
						doneflag = true;
					}
					while (GetMenuItems()[currentSelection_]->GetMenuItemTargetable() == false)
					{
						currentSelection_--;
						if (currentSelection_ < 0)
						{
							currentSelection_ = GetMenuItems().size() - 1;
						}
					}
				}
				break;
			case ALLEGRO_KEY_DOWN://choose later....
				currentSelection_++;
				while (doneflag == false)//helps to loop and to not select untarGetable items
				{
					if (currentSelection_ >= GetMenuItems().size())
					{
						currentSelection_ = 0;
					}
					if (GetMenuItems()[currentSelection_]->GetMenuItemTargetable() == true)
					{
						doneflag = true;
					}
					while (GetMenuItems()[currentSelection_]->GetMenuItemTargetable() == false)
					{
						currentSelection_++;
						if (currentSelection_ >= GetMenuItems().size())
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
		else if (ev->type == ALLEGRO_EVENT_KEY_CHAR)
		{
			if (GetMenuItems()[currentSelection_]->GetMenuItemProperty() != nullptr && ev->keyboard.unichar == 8) {
				//back space
				//TODO: Backspace stuff...
			}
			else if (GetMenuItems()[currentSelection_]->GetMenuItemProperty() != nullptr && ev->keyboard.unichar > 0)
			{
				ALLEGRO_USTR *test = al_ustr_new("");
				al_ustr_append_chr(test, ev->keyboard.unichar);
				GetMenuItems()[currentSelection_]->SetMenuItemProperty(test);
				al_ustr_free(test);
			}
		}



		if (ev->type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev->keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				//quit
				val = STATES::RETURN;
				break;
			}
		}




		return val;
	}








}