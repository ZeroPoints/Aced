#ifndef MENUITEM_H
#define MENUITEM_H

#define ALLEGRO_NO_MAGIC_MAIN

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include "../Static/Definitions.h"
#include <string>


#ifdef ACEDSHAREDDLL_EXPORTS
   #define ACEDSHAREDDLL_API __declspec(dllexport)
#else
   #define ACEDSHAREDDLL_API __declspec(dllimport)
#endif


namespace AcedSharedDLL{
	class MenuItem
	{
		public:
			ACEDSHAREDDLL_API MenuItem();


			ACEDSHAREDDLL_API ~MenuItem();

			//-----------------------------------------------------------------------------------------------------

			//Gets



			ACEDSHAREDDLL_API OPTIONTYPES GetOptionId();

			ACEDSHAREDDLL_API STATES GetId();
			ACEDSHAREDDLL_API int GetMenuItemHeight();
			ACEDSHAREDDLL_API int GetMenuItemWidth();
			ACEDSHAREDDLL_API int GetMenuItemX();
			ACEDSHAREDDLL_API int GetMenuItemPropertyX();
			ACEDSHAREDDLL_API int GetMenuItemY();
			ACEDSHAREDDLL_API std::string GetMenuItemText();
			ACEDSHAREDDLL_API ALLEGRO_USTR *GetMenuItemProperty();
			ACEDSHAREDDLL_API bool GetMenuItemTargetable();
			ACEDSHAREDDLL_API bool GetMenuItemValueEditable();


			//-----------------------------------------------------------------------------------------------------

			//Sets



			ACEDSHAREDDLL_API void SetMenuItemHeight(int menuItemHeight);
			ACEDSHAREDDLL_API void SetMenuItemWidth(int menuItemWidth);
			ACEDSHAREDDLL_API void SetMenuItemPropertyX(int menuItemPropertyX);
			ACEDSHAREDDLL_API void SetMenuItemX(int menuItemX);
			ACEDSHAREDDLL_API void SetMenuItemY(int menuItemY);
			ACEDSHAREDDLL_API void SetMenuItemText(const std::string &menuItemText);
			ACEDSHAREDDLL_API void SetMenuItemProperty(ALLEGRO_USTR *menuItemProperty);
			ACEDSHAREDDLL_API void SetId(STATES newId);
			ACEDSHAREDDLL_API void SetOptionId(OPTIONTYPES newId);


			ACEDSHAREDDLL_API void SetMenuItemTargetable(bool targetable);

			ACEDSHAREDDLL_API void SetMenuItemValueEditable(bool editable);



			//-----------------------------------------------------------------------------------------------------

			//Draws

			ACEDSHAREDDLL_API void DrawMenuItem();




			//-----------------------------------------------------------------------------------------------------

			//Misc

			ACEDSHAREDDLL_API void InitMenuItemProperty(ALLEGRO_USTR *menuItemProperty);





			//-----------------------------------------------------------------------------------------------------

			//Testing












		private:
			ALLEGRO_FONT *font30_;
			ALLEGRO_USTR *menuItemProperty_;
			OPTIONTYPES optionId_;
			STATES Id_;
			bool editable_;
			bool targetable_;
			std::string menuItemText_;//text
			int menuItemPropertyX_;//location
			int menuItemWidth_, menuItemHeight_;//size
			int menuItemX_, menuItemY_;//location






	};
}


#endif