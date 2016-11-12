#ifndef MENU_H
#define MENU_H


#define ALLEGRO_NO_MAGIC_MAIN

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <vector>
#include "menuitem.h"
#include "../Static/Definitions.h"
#include "../Config/Settings.h"
#include "../World/Map.h"

#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif




namespace StaticDLL{
	class Menu
	{
	public:


		STATICDLL_API Menu();

		STATICDLL_API ~Menu();







		//-----------------------------------------------------------------------------------------------------

		//Gets


		STATICDLL_API int GetCurrentSelection();
		STATICDLL_API Settings* GetSettings();
		STATICDLL_API Map* GetMap();
		STATICDLL_API STATES GetId();
		STATICDLL_API int GetMenuHeight();
		STATICDLL_API int GetMenuWidth();
		STATICDLL_API int GetMenuX();
		STATICDLL_API int GetMenuY();
		STATICDLL_API char *GetMenuHeader();
		STATICDLL_API int GetSelectItemY();
		STATICDLL_API int GetSelectItemX();
		STATICDLL_API int GetSelectItemWidth();
		STATICDLL_API int GetSelectItemHeight();
		STATICDLL_API ALLEGRO_FONT* GetFont();
		STATICDLL_API std::vector<MenuItem*> GetMenuItems();



		//-----------------------------------------------------------------------------------------------------

		//Sets

		STATICDLL_API void SetCurrentSelection();
		STATICDLL_API void SetMenuHeight(int menuHeight);
		STATICDLL_API void SetMenuWidth(int menuWidth);
		STATICDLL_API void SetMenuX(int menuX);
		STATICDLL_API void SetMenuY(int menuY);
		STATICDLL_API void SetMenuHeaderHeight(int menuHeaderHeight);
		STATICDLL_API void SetMenuHeaderWidth(int menuHeaderWidth);
		STATICDLL_API void SetMenuHeaderX(int menuHeaderX);
		STATICDLL_API void SetMenuHeaderY(int menuHeaderY);
		STATICDLL_API void SetMenuHeader(char *menuHeader);
		STATICDLL_API void SetSubMenuHeaderHeight(int menuSubHeaderHeight);
		STATICDLL_API void SetSubMenuHeaderWidth(int menuSubHeaderWidth);
		STATICDLL_API void SetSubMenuHeaderX(int menuSubHeaderX);
		STATICDLL_API void SetSubMenuHeaderY(int menuSubHeaderY);
		STATICDLL_API void SetSubMenuHeader(char menuSubHeader[]);
		STATICDLL_API void SetId(STATES newId);
		STATICDLL_API void SetMap(Map *currentMap);
		STATICDLL_API void SetSelectItemY(int val);
		STATICDLL_API void SetSelectItemX(int val);
		STATICDLL_API void SetSelectItemWidth(int val);
		STATICDLL_API void SetSelectItemHeight(int val);
		STATICDLL_API void SetFont(ALLEGRO_FONT* currentFont);
		STATICDLL_API void SetSettings(Settings *settings);



		//-----------------------------------------------------------------------------------------------------

		//Draws

		STATICDLL_API void DrawMenuSelectorCube();

		STATICDLL_API void DrawMenu();



		//-----------------------------------------------------------------------------------------------------

		//Misc

		//This is virtual so it will be used somewhere so ignore mister squiggle underneath
		STATICDLL_API virtual void InitMenu(Settings *settings){}


		STATICDLL_API void InitMenuItems();
		STATICDLL_API void CalculateMenuSelectorCubePosition();
		STATICDLL_API void AddMenuItem(MenuItem* newMenuItem);
		STATICDLL_API STATES KeyPress(ALLEGRO_EVENT *ev);


			//-----------------------------------------------------------------------------------------------------

			//Testing




		private:
			ALLEGRO_FONT *font30_;
			STATES Id_;
			Map *currentMap_;
			Settings *settings_;
			char *menuHeader_;//title
			char menuSubHeader_[20];//sub headings
			int currentSelection_;
			int fontSize_;
			int menuHeaderWidth_, menuHeaderHeight_;
			int menuHeaderX_, menuHeaderY_;
			int menuSubHeaderWidth_, menuSubHeaderHeight_;
			int menuSubHeaderX_, menuSubHeaderY_;
			int menuWidth_, menuHeight_;//size
			int menuX_, menuY_;//location
			int selectItemHeight_;
			int selectItemWidth_;
			int selectItemX_;
			int selectItemY_;
			std::vector<MenuItem*> menuItems_;
			std::vector<int> subMenuOf_; //main menu//options menu//in-game menu




	};
}
#endif