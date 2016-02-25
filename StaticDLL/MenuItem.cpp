#include "MenuItem.h"



namespace StaticDLL{

	


	MenuItem::MenuItem()
	{
		font30_ = al_load_font("arial.ttf", 30, 0);
		targetable_ = true;
		editable_ = false;
		optionId_ = EnumDLL::OPTIONTYPES::NOOPTION;
		Id_ = EnumDLL::STATES::NONE;
	}

	void MenuItem::SetMenuItemText(char *menuItemText)
	{
		menuItemText_ = menuItemText;
	}


	void MenuItem::InitMenuItemProperty(ALLEGRO_USTR *menuItemProperty)
	{
		//menuItemProperty_ = al_ustr_new("");
		menuItemProperty_ = menuItemProperty;
		//al_ustr_append(menuItemProperty_, menuItemProperty);
	}

	void MenuItem::SetMenuItemProperty(ALLEGRO_USTR *menuItemProperty)
	{
		al_ustr_append(menuItemProperty_, menuItemProperty);
	}

	void MenuItem::SetMenuItemX(int menuItemX)
	{
		menuItemX_ = menuItemX;
	}

	void MenuItem::SetMenuItemPropertyX(int menuItemPropertyX)
	{
		menuItemPropertyX_ = menuItemPropertyX;
	}

	void MenuItem::SetMenuItemY(int menuItemY)
	{
		menuItemY_ = menuItemY;
	}

	void MenuItem::drawMenuItem()
	{
		al_draw_text(font30_, al_map_rgb(255,255,255), menuItemX_, menuItemY_, ALLEGRO_ALIGN_CENTRE, menuItemText_);	

		if(menuItemProperty_ != nullptr)
		{
			al_draw_ustr(font30_, al_map_rgb(255,255,255), menuItemPropertyX_, menuItemY_, ALLEGRO_ALIGN_CENTRE, menuItemProperty_);	
		}
	}

	void MenuItem::SetMenuItemTargetable(bool targetable)
	{
		targetable_ = targetable;
	}

	void MenuItem::SetId(EnumDLL::STATES newId)
	{
		Id_ = newId;
	}
	
	void MenuItem::SetOptionId(EnumDLL::OPTIONTYPES newId)
	{
		optionId_ = newId;
	}



}