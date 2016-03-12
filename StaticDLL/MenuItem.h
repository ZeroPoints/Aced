#ifndef MENUITEM_H
#define MENUITEM_H

#define ALLEGRO_NO_MAGIC_MAIN

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include "Definitions.h"


#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif
#include <string>


namespace StaticDLL{
	class MenuItem
	{
		public:
			STATICDLL_API MenuItem()
			{
				font30_ = al_load_font("arial.ttf", 30, 0);
				targetable_ = true;
				editable_ = false;
				optionId_ = EnumDLL::OPTIONTYPES::NOOPTION;
				Id_ = EnumDLL::STATES::NONE;
				fprintf(stderr,"A Menu Item Created\n");
			}


			STATICDLL_API ~MenuItem(){
				al_destroy_font(font30_);
				//TODO: Destroy the ALLEGRO_USTR
				al_ustr_free(menuItemProperty_);
				fprintf(stderr,"A Menu Item Destructed\n");
				return;
			}
        

			STATICDLL_API void InitMenuItemProperty(ALLEGRO_USTR *menuItemProperty);


			STATICDLL_API void SetMenuItemHeight(int menuItemHeight);
			STATICDLL_API void SetMenuItemWidth(int menuItemWidth);
			STATICDLL_API void SetMenuItemPropertyX(int menuItemPropertyX);
			STATICDLL_API void SetMenuItemX(int menuItemX);
			STATICDLL_API void SetMenuItemY(int menuItemY);
			STATICDLL_API void SetMenuItemText(char *menuItemText);
			STATICDLL_API void SetMenuItemProperty(ALLEGRO_USTR *menuItemProperty);
			STATICDLL_API void SetId(EnumDLL::STATES newId);
			STATICDLL_API void SetOptionId(EnumDLL::OPTIONTYPES newId);

			STATICDLL_API EnumDLL::OPTIONTYPES GetOptionId()
			{
				return optionId_;
			}

			STATICDLL_API EnumDLL::STATES GetId()
			{
				return Id_;
			}
			STATICDLL_API int GetMenuItemHeight()
			{
				return menuItemHeight_;
			}
			STATICDLL_API int GetMenuItemWidth()
			{
				return menuItemWidth_;
			}
			STATICDLL_API int GetMenuItemX()
			{
				return menuItemX_;
			}
			STATICDLL_API int GetMenuItemPropertyX()
			{
				return menuItemPropertyX_;
			}
			STATICDLL_API int GetMenuItemY()
			{
				return menuItemY_;
			}
			STATICDLL_API char *GetMenuItemText()
			{
				return menuItemText_;
			}
			STATICDLL_API ALLEGRO_USTR *GetMenuItemProperty()
			{
				return menuItemProperty_;
			}


			STATICDLL_API void SetMenuItemTargetable(bool targetable);

			STATICDLL_API bool GetMenuItemTargetable()
			{
				return targetable_;
			}


			STATICDLL_API void SetMenuItemValueEditable(bool editable)
			{
				editable_ = editable;
			}

			STATICDLL_API bool GetMenuItemValueEditable()
			{
				return editable_;
			}



			STATICDLL_API void drawMenuItem();

		private:
			EnumDLL::STATES Id_;

			EnumDLL::OPTIONTYPES optionId_;


			bool targetable_;
			bool editable_;
			char *menuItemText_;//text

			//char *menuItemProperty_;//value

			ALLEGRO_USTR *menuItemProperty_;

			int menuItemWidth_, menuItemHeight_;//size
			int menuItemX_, menuItemY_;//location
			int menuItemPropertyX_;//location
			ALLEGRO_FONT *font30_;
	};
}
#endif