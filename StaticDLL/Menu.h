#ifndef MENU_H
#define MENU_H


#define ALLEGRO_NO_MAGIC_MAIN

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <vector>
#include "menuitem.h"
#include "Definitions.h"
#include "Settings.h"
#include "Map.h"

#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif




namespace StaticDLL{
	class Menu
	{
		public:

			
			STATICDLL_API Menu(){
				fprintf(stderr,"A Menu Created\n");
			}

			STATICDLL_API virtual ~Menu(){
				al_destroy_font(font30_);
				for (MenuItem* item : menuItems_)
				{
					delete item;
					item = nullptr;
				}
				fprintf(stderr,"A Menu Destructed\n");
				return;
			}

			STATICDLL_API virtual void InitMenu(Settings *settings){
				return;
			};

			STATICDLL_API void SetCurrentSelection();
			STATICDLL_API int GetCurrentSelection(){
				return currentSelection_;
			};


			STATICDLL_API void CalculateMenuSelectorCubePosition();
			STATICDLL_API void DrawMenuSelectorCube();


			STATICDLL_API void InitMenuItems();
        
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

			STATICDLL_API void AddMenuItem(MenuItem* newMenuItem);


			STATICDLL_API void SetId(EnumDLL::STATES newId);


			STATICDLL_API void SetSettings(Settings *settings);
			STATICDLL_API Settings* GetSettings(){
				return settings_;
			}

			STATICDLL_API void SetMap(Map *currentMap);
			STATICDLL_API Map* GetMap(){
				return currentMap_;
			}


			

			STATICDLL_API EnumDLL::STATES GetId()
			{
				return Id_;
			}
			STATICDLL_API int GetMenuHeight()
			{
				return menuHeight_;
			}
			STATICDLL_API int GetMenuWidth()
			{
				return menuWidth_;
			}
			STATICDLL_API int GetMenuX()
			{
				return menuX_;
			}
			STATICDLL_API int GetMenuY()
			{
				return menuY_;
			}
			STATICDLL_API char *GetMenuHeader()
			{
				return menuHeader_;
			}


			



			STATICDLL_API void DrawMenu();

			STATICDLL_API int GetSelectItemY(){
				return selectItemY_;
			}

			STATICDLL_API void SetSelectItemY(int val){
				selectItemY_ = val;
			}

			STATICDLL_API int GetSelectItemX(){
				return selectItemX_;
			}

			STATICDLL_API void SetSelectItemX(int val){
				selectItemX_ = val;
			}

			STATICDLL_API int GetSelectItemWidth(){
				return selectItemWidth_;
			}

			STATICDLL_API void SetSelectItemWidth(int val){
				selectItemWidth_ = val;
			}

			STATICDLL_API int GetSelectItemHeight(){
				return selectItemHeight_;
			}

			STATICDLL_API void SetSelectItemHeight(int val){
				selectItemHeight_ = val;
			}

			STATICDLL_API EnumDLL::STATES KeyPress(ALLEGRO_EVENT *ev);

			STATICDLL_API void SetFont(ALLEGRO_FONT* currentFont){
				font30_ = currentFont;
			}
			STATICDLL_API ALLEGRO_FONT* GetFont()
			{
				return font30_;
			}


			STATICDLL_API std::vector<MenuItem*> GetMenuItems()
			{
				return menuItems_;
			}


		private:
			EnumDLL::STATES Id_;
			std::vector<int> subMenuOf_; //main menu//options menu//in-game menu
			char *menuHeader_;//title
			int menuHeaderWidth_, menuHeaderHeight_;
			int menuHeaderX_, menuHeaderY_;

			char menuSubHeader_[20];//sub headings
			int menuSubHeaderWidth_, menuSubHeaderHeight_;
			int menuSubHeaderX_, menuSubHeaderY_;
			Settings *settings_;
			Map *currentMap_;

			int selectItemY_;
			int selectItemX_;
			int selectItemWidth_;
			int selectItemHeight_;


			int menuWidth_, menuHeight_;//size
			int menuX_, menuY_;//location
			std::vector<MenuItem*> menuItems_;
			ALLEGRO_FONT *font30_;
			int fontSize_;
			int currentSelection_;
	};
}
#endif