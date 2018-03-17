#include "MenuItem.h"



namespace AcedSharedDLL {

	MenuItem::MenuItem()
	{
		targetable_ = true;
		editable_ = false;
		optionId_ = OPTIONTYPES::NOOPTION;
		Id_ = STATES::NONE;
		menuItemPropertyU_ = nullptr;
		//fprintf(stderr, "A Menu Item Created\n");
	}


	MenuItem::~MenuItem() {
		//al_destroy_font(font30_);
		//al_ustr_free(menuItemProperty_);
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
	std::string MenuItem::GetMenuItemText()
	{
		return menuItemText_;
	}
	ALLEGRO_USTR *MenuItem::GetMenuItemPropertyU()
	{
		return menuItemPropertyU_;
	}
	std::string MenuItem::GetMenuItemProperty()
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



	void MenuItem::SetMenuItemText(const std::string &menuItemText)
	{
		menuItemText_ = std::move(menuItemText);
	}


	void MenuItem::SetMenuItemProperty(const std::string &menuItemProperty)
	{
		menuItemProperty_ = menuItemProperty_ + menuItemProperty;
		al_ustr_append(menuItemPropertyU_, al_ustr_new(menuItemProperty.c_str()));
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

	void MenuItem::DrawMenuItem(ALLEGRO_FONT* font)
	{
		al_draw_text(font, al_map_rgb(255, 255, 255), menuItemX_, menuItemY_, ALLEGRO_ALIGN_CENTRE, menuItemText_.c_str());

		if (menuItemPropertyU_ != nullptr)
		{
			al_draw_ustr(font, al_map_rgb(255, 255, 255), menuItemPropertyX_, menuItemY_, ALLEGRO_ALIGN_LEFT, menuItemPropertyU_);
		}
	}




	//-----------------------------------------------------------------------------------------------------

	//Misc


	void MenuItem::InitMenuItemProperty(const std::string &menuItemProperty)
	{
		menuItemProperty_ = menuItemProperty;
		menuItemPropertyU_ = al_ustr_new(menuItemProperty.c_str());
	}





	//-----------------------------------------------------------------------------------------------------

	//Testing




}