#ifndef MENU_H
#define MENU_H


#define ALLEGRO_NO_MAGIC_MAIN

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <vector>
#include <memory>
#include "menuitem.h"
#include "../Static/Definitions.h"
#include "../Config/BaseSettings.h"
#include "../World/Map.h"



#ifdef ACEDSHAREDDLL_EXPORTS
   #define ACEDSHAREDDLL_API __declspec(dllexport)
#else
   #define ACEDSHAREDDLL_API __declspec(dllimport)
#endif




namespace AcedSharedDLL{
	class Menu
	{
	public:


		ACEDSHAREDDLL_API Menu(std::shared_ptr<BaseSettings> &settings);

		ACEDSHAREDDLL_API ~Menu();







		//-----------------------------------------------------------------------------------------------------

		//Gets


		ACEDSHAREDDLL_API int GetCurrentSelection();
		ACEDSHAREDDLL_API std::shared_ptr<BaseSettings> &GetSettings();
		ACEDSHAREDDLL_API std::shared_ptr<Map> &GetMap();
		ACEDSHAREDDLL_API STATES GetId();
		ACEDSHAREDDLL_API int GetMenuHeight();
		ACEDSHAREDDLL_API int GetMenuWidth();
		ACEDSHAREDDLL_API int GetMenuX();
		ACEDSHAREDDLL_API int GetMenuY();
		ACEDSHAREDDLL_API std::string GetMenuHeader();
		ACEDSHAREDDLL_API int GetSelectItemY();
		ACEDSHAREDDLL_API int GetSelectItemX();
		ACEDSHAREDDLL_API int GetSelectItemWidth();
		ACEDSHAREDDLL_API int GetSelectItemHeight();

		ACEDSHAREDDLL_API std::vector<std::shared_ptr<MenuItem>> &GetMenuItems();



		//-----------------------------------------------------------------------------------------------------

		//Sets

		ACEDSHAREDDLL_API void SetCurrentSelection();
		ACEDSHAREDDLL_API void SetMenuHeight(int menuHeight);
		ACEDSHAREDDLL_API void SetMenuWidth(int menuWidth);
		ACEDSHAREDDLL_API void SetMenuX(int menuX);
		ACEDSHAREDDLL_API void SetMenuY(int menuY);
		ACEDSHAREDDLL_API void SetMenuHeaderHeight(int menuHeaderHeight);
		ACEDSHAREDDLL_API void SetMenuHeaderWidth(int menuHeaderWidth);
		ACEDSHAREDDLL_API void SetMenuHeaderX(int menuHeaderX);
		ACEDSHAREDDLL_API void SetMenuHeaderY(int menuHeaderY);
		ACEDSHAREDDLL_API void SetMenuHeader(const std::string &menuHeader);
		ACEDSHAREDDLL_API void SetSubMenuHeaderHeight(int menuSubHeaderHeight);
		ACEDSHAREDDLL_API void SetSubMenuHeaderWidth(int menuSubHeaderWidth);
		ACEDSHAREDDLL_API void SetSubMenuHeaderX(int menuSubHeaderX);
		ACEDSHAREDDLL_API void SetSubMenuHeaderY(int menuSubHeaderY);
		ACEDSHAREDDLL_API void SetSubMenuHeader(const std::string &menuSubHeader);
		ACEDSHAREDDLL_API void SetId(STATES newId);
		ACEDSHAREDDLL_API void SetMap(std::shared_ptr<Map> &currentMap);
		ACEDSHAREDDLL_API void SetSelectItemY(int val);
		ACEDSHAREDDLL_API void SetSelectItemX(int val);
		ACEDSHAREDDLL_API void SetSelectItemWidth(int val);
		ACEDSHAREDDLL_API void SetSelectItemHeight(int val);

		ACEDSHAREDDLL_API void SetSettings(std::shared_ptr<BaseSettings> &settings);



		//-----------------------------------------------------------------------------------------------------

		//Draws

		ACEDSHAREDDLL_API void DrawMenuSelectorCube();

		ACEDSHAREDDLL_API void DrawMenu(ALLEGRO_FONT* font);



		//-----------------------------------------------------------------------------------------------------

		//Misc


		ACEDSHAREDDLL_API void InitMenuItems();
		ACEDSHAREDDLL_API void CalculateMenuSelectorCubePosition();
		ACEDSHAREDDLL_API void AddMenuItem(std::shared_ptr<MenuItem> &newMenuItem);
		ACEDSHAREDDLL_API STATES KeyPress(ALLEGRO_EVENT *ev);


			//-----------------------------------------------------------------------------------------------------

			//Testing




		private:

			STATES Id_;
			std::shared_ptr<Map> currentMap_;
			std::shared_ptr<BaseSettings> settings_;
			std::string menuHeader_;//title
			std::string menuSubHeader_;//sub headings
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
			std::vector<std::shared_ptr<MenuItem>> menuItems_;
			std::vector<int> subMenuOf_; //main menu//options menu//in-game menu




	};
}
#endif