#include "menu.h"


Menu::Menu()
{
	fontsize_ = 30;
	font30_ = al_load_font("arial.ttf", fontsize_, 0);
}

#pragma region menusettings
//this is menu stuff
void Menu::setMenuHeight(int menuHeight)
{
	menuHeight_ = menuHeight;
}

void Menu::setMenuWidth(int menuWidth)
{
	menuWidth_ = menuWidth;
}

void Menu::setMenuY(int menuY)
{
	menuY_ = menuY;
}

void Menu::setMenuX(int menuX)
{
	menuX_ = menuX;
}
#pragma endregion menusettings


#pragma region menuheader //menu header stuff
void Menu::setMenuHeaderHeight(int menuHeaderHeight)
{
	menuHeaderHeight_ = menuHeaderHeight;
}

void Menu::setMenuHeaderWidth(int menuHeaderWidth)
{
	menuHeaderWidth_ = menuHeaderWidth;
}

void Menu::setMenuHeaderY(int menuHeaderY)
{
	menuHeaderY_ = menuHeaderY;
}

void Menu::setMenuHeaderX(int menuHeaderX)
{
	menuHeaderX_ = menuHeaderX;
}

void Menu::setMenuHeader(char menuHeader[])
{
	strcpy(menuHeader_, menuHeader);
}
#pragma endregion menuheader


#pragma region submenuheader //menu sub header stuff

void Menu::setSubMenuHeaderHeight(int menuSubHeaderHeight)
{
	menuSubHeaderHeight_ = menuSubHeaderHeight;
}

void Menu::setSubMenuHeaderWidth(int menuSubHeaderWidth)
{
	menuSubHeaderWidth_ = menuSubHeaderWidth;
}

void Menu::setSubMenuHeaderY(int menuSubHeaderY)
{
	menuSubHeaderY_ = menuSubHeaderY;
}

void Menu::setSubMenuHeaderX(int menuSubHeaderX)
{
	menuSubHeaderX_ = menuSubHeaderX;
}

void Menu::setSubMenuHeader(char menuSubHeader[])
{
	strcpy(menuSubHeader_, menuSubHeader);
}
#pragma endregion submenuheader




//this function is for menumanager
void Menu::initMenuItems(int N)
{
	std::vector<MenuItem> menuItems(N);
	menuItems_ = menuItems;
}


//tihs functions is for menumanager
void Menu::setSubMenuOf(int subMenuOf)
{
	subMenuOf_.push_back(subMenuOf);
}



void Menu::drawmenu()
{
	
	//menu header drawing rectangle
	al_draw_filled_rectangle(menuHeaderX_, menuHeaderY_, menuHeaderX_ + menuHeaderWidth_, menuHeaderY_ + menuHeaderHeight_, al_map_rgb(0,125,255));	
	al_draw_rectangle(menuHeaderX_, menuHeaderY_, menuHeaderX_ + menuHeaderWidth_, menuHeaderY_ + menuHeaderHeight_, al_map_rgb(255,255,255),1);
	al_draw_text(font30_, al_map_rgb(255,255,255), menuHeaderX_ + (menuHeaderWidth_/2), menuHeaderY_ + 10, ALLEGRO_ALIGN_CENTRE, menuHeader_);//change the 10 into a value eg: (menuheaderheight-fontsize)/2 that will work

	//menu drawing rectangle
	al_draw_filled_rectangle(menuX_, menuY_, menuX_ + menuWidth_, menuY_ + menuHeight_, al_map_rgb(125,0,255));				
	al_draw_rectangle(menuX_, menuY_, menuX_ + menuWidth_, menuY_ + menuHeight_, al_map_rgb(255,255,255),1);


	for(int i = 0; i < menuItems_.size(); i++)
	{
		menuItems_[i].drawMenuItem();
	}


}