#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <vector>
#include "menuitem.h"


class Menu
{
	public:
        Menu(int menuType);
		Menu();

		void initMenuItems(int N);
		//void initNonTargetableMenuItems(int N);
        
		void setMenuHeight(int menuHeight);
		void setMenuWidth(int menuWidth);
		void setMenuX(int menuX);
		void setMenuY(int menuY);

		void setMenuHeaderHeight(int menuHeaderHeight);
		void setMenuHeaderWidth(int menuHeaderWidth);
		void setMenuHeaderX(int menuHeaderX);
		void setMenuHeaderY(int menuHeaderY);
		void setMenuHeader(char menuHeader[]);

		void setSubMenuHeaderHeight(int menuSubHeaderHeight);
		void setSubMenuHeaderWidth(int menuSubHeaderWidth);
		void setSubMenuHeaderX(int menuSubHeaderX);
		void setSubMenuHeaderY(int menuSubHeaderY);
		void setSubMenuHeader(char menuSubHeader[]);


		void createMenuItems();
		void setSubMenuOf(int subMenuOf);

		int getMenuHeight()
		{
			return menuHeight_;
		}
		int getMenuWidth()
		{
			return menuWidth_;
		}
		int getMenuX()
		{
			return menuX_;
		}
		int getMenuY()
		{
			return menuY_;
		}
		char getMenuHeader()
		{
			return menuHeader_[20];
		}


		int getSubMenuOf()
		{
			return menuY_;
		}


		std::vector<MenuItem> &getMenuItems()
		{
			return menuItems_;
		}

		void drawmenu();

    private:
		std::vector<int> subMenuOf_; //main menu//options menu//in-game menu
		char menuHeader_[20];//title
		int menuHeaderWidth_, menuHeaderHeight_;
		int menuHeaderX_, menuHeaderY_;

		char menuSubHeader_[20];//sub headings
		int menuSubHeaderWidth_, menuSubHeaderHeight_;
		int menuSubHeaderX_, menuSubHeaderY_;



		int menuWidth_, menuHeight_;//size
		int menuX_, menuY_;//location
		std::vector<MenuItem> menuItems_;
		ALLEGRO_FONT * font30_;
		int fontsize_;
};
#endif