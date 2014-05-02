#ifndef MENUITEM_H
#define MENUITEM_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts


class MenuItem
{
	public:
        MenuItem();
        
		void setMenuItemHeight(int menuItemHeight);
		void setMenuItemWidth(int menuItemWidth);
		void setMenuItemX(int menuItemX);
		void setMenuItemY(int menuItemY);
		void setMenuItemText(char menuItemText[]);

		int getMenuItemHeight()
		{
			return menuItemHeight_;
		}
		int getMenuItemWidth()
		{
			return menuItemWidth_;
		}
		int getMenuItemX()
		{
			return menuItemX_;
		}
		int getMenuItemY()
		{
			return menuItemY_;
		}
		char getMenuItemText()
		{
			return menuItemText_[20];
		}

		void setMenuItemTargetable(bool targetable);
		bool getMenuItemTargetable()
		{
			return targetable_;
		}


		void drawMenuItem();

    private:
		bool targetable_;//for subheaders i guess
		char menuItemText_[20];//title
		int menuItemWidth_, menuItemHeight_;//size
		int menuItemX_, menuItemY_;//location
		ALLEGRO_FONT * font30_;
};
#endif