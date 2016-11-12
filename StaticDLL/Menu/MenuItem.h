#ifndef MENUITEM_H
#define MENUITEM_H

#define ALLEGRO_NO_MAGIC_MAIN

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include "../Static/Definitions.h"


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
			STATICDLL_API MenuItem();


			STATICDLL_API ~MenuItem();

			//-----------------------------------------------------------------------------------------------------

			//Gets



			STATICDLL_API OPTIONTYPES GetOptionId();

			STATICDLL_API STATES GetId();
			STATICDLL_API int GetMenuItemHeight();
			STATICDLL_API int GetMenuItemWidth();
			STATICDLL_API int GetMenuItemX();
			STATICDLL_API int GetMenuItemPropertyX();
			STATICDLL_API int GetMenuItemY();
			STATICDLL_API char *GetMenuItemText();
			STATICDLL_API ALLEGRO_USTR *GetMenuItemProperty();
			STATICDLL_API bool GetMenuItemTargetable();
			STATICDLL_API bool GetMenuItemValueEditable();


			//-----------------------------------------------------------------------------------------------------

			//Sets



			STATICDLL_API void SetMenuItemHeight(int menuItemHeight);
			STATICDLL_API void SetMenuItemWidth(int menuItemWidth);
			STATICDLL_API void SetMenuItemPropertyX(int menuItemPropertyX);
			STATICDLL_API void SetMenuItemX(int menuItemX);
			STATICDLL_API void SetMenuItemY(int menuItemY);
			STATICDLL_API void SetMenuItemText(char *menuItemText);
			STATICDLL_API void SetMenuItemProperty(ALLEGRO_USTR *menuItemProperty);
			STATICDLL_API void SetId(STATES newId);
			STATICDLL_API void SetOptionId(OPTIONTYPES newId);


			STATICDLL_API void SetMenuItemTargetable(bool targetable);

			STATICDLL_API void SetMenuItemValueEditable(bool editable);



			//-----------------------------------------------------------------------------------------------------

			//Draws

			STATICDLL_API void DrawMenuItem();




			//-----------------------------------------------------------------------------------------------------

			//Misc

			STATICDLL_API void InitMenuItemProperty(ALLEGRO_USTR *menuItemProperty);





			//-----------------------------------------------------------------------------------------------------

			//Testing












		private:
			ALLEGRO_FONT *font30_;
			ALLEGRO_USTR *menuItemProperty_;
			OPTIONTYPES optionId_;
			STATES Id_;
			bool editable_;
			bool targetable_;
			char *menuItemText_;//text
			int menuItemPropertyX_;//location
			int menuItemWidth_, menuItemHeight_;//size
			int menuItemX_, menuItemY_;//location






	};
}
#endif