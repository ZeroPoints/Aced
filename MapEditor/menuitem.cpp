#include "menuitem.h"

MenuItem::MenuItem()
{
	font30_ = al_load_font("arial.ttf", 30, 0);
}

void MenuItem::setMenuItemText(char menuItemText[])
{
	strcpy(menuItemText_, menuItemText);
}

void MenuItem::setMenuItemX(int menuItemX)
{
	menuItemX_ = menuItemX;
}

void MenuItem::setMenuItemY(int menuItemY)
{
	menuItemY_ = menuItemY;
}

void MenuItem::drawMenuItem()
{
	al_draw_text(font30_, al_map_rgb(255,255,255), menuItemX_, menuItemY_, ALLEGRO_ALIGN_CENTRE, menuItemText_);	
}

void MenuItem::setMenuItemTargetable(bool targetable)
{
	targetable_ = targetable;
}