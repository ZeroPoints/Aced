#include "MenuItem.h"



namespace AcedSharedDLL{

	MenuItem::MenuItem()
	{
		font30_ = al_load_font("arial.ttf", 30, 0);
		targetable_ = true;
		editable_ = false;
		optionId_ = OPTIONTYPES::NOOPTION;
		Id_ = STATES::NONE;
		menuItemProperty_ = nullptr;
		//fprintf(stderr, "A Menu Item Created\n");
	}


	MenuItem::~MenuItem() {
		al_destroy_font(font30_);
		al_ustr_free(menuItemProperty_);
		//fprintf(stderr, "A Menu Item Destructed\n");
		return;
	}




	//-----------------------------------------------------------------------------------------------------

	//Gets


	 OPTIONTYPES MenuItem::GetOptionId()
	{
		return optionId_;
	}

	 STATES MenuItem::GetId()
	{
		return Id_;
	}
	 int MenuItem::GetMenuItemHeight()
	{
		return menuItemHeight_;
	}
	 int MenuItem::GetMenuItemWidth()
	{
		return menuItemWidth_;
	}
	 int MenuItem::GetMenuItemX()
	{
		return menuItemX_;
	}
	 int MenuItem::GetMenuItemPropertyX()
	{
		return menuItemPropertyX_;
	}
	 int MenuItem::GetMenuItemY()
	{
		return menuItemY_;
	}
	 char *MenuItem::GetMenuItemText()
	{
		return menuItemText_;
	}
	 ALLEGRO_USTR *MenuItem::GetMenuItemProperty()
	{
		return menuItemProperty_;
	}

	 bool MenuItem::GetMenuItemTargetable()
	{
		return targetable_;
	}


	 bool MenuItem::GetMenuItemValueEditable()
	{
		return editable_;
	}


	//-----------------------------------------------------------------------------------------------------

	//Sets



	void MenuItem::SetMenuItemText(char *menuItemText)
	{
		menuItemText_ = menuItemText;
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

	void MenuItem::SetMenuItemTargetable(bool targetable)
	{
		targetable_ = targetable;
	}

	void MenuItem::SetId(STATES newId)
	{
		Id_ = newId;
	}

	void MenuItem::SetOptionId(OPTIONTYPES newId)
	{
		optionId_ = newId;
	}

	void MenuItem::SetMenuItemValueEditable(bool editable)
	{
		editable_ = editable;
	}

	//-----------------------------------------------------------------------------------------------------

	//Draws

	void MenuItem::DrawMenuItem()
	{
		al_draw_text(font30_, al_map_rgb(255, 255, 255), menuItemX_, menuItemY_, ALLEGRO_ALIGN_CENTRE, menuItemText_);

		if (menuItemProperty_ != nullptr)
		{
			al_draw_ustr(font30_, al_map_rgb(255, 255, 255), menuItemPropertyX_, menuItemY_, ALLEGRO_ALIGN_CENTRE, menuItemProperty_);
		}
	}




	//-----------------------------------------------------------------------------------------------------

	//Misc


	void MenuItem::InitMenuItemProperty(ALLEGRO_USTR *menuItemProperty)
	{
		//menuItemProperty_ = al_ustr_new("");
		menuItemProperty_ = menuItemProperty;
		//al_ustr_append(menuItemProperty_, menuItemProperty);
	}



	//-----------------------------------------------------------------------------------------------------

	//Testing




}