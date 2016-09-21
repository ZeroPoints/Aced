#ifndef MENUTEMPLATES_H
#define MENUTEMPLATES_H

#define ALLEGRO_NO_MAGIC_MAIN

#include <vector>
#include <allegro5\allegro.h>
#include "../Static/Definitions.h"
#include <allegro5/allegro_primitives.h>
#include <algorithm>
#include "Menu.h"



#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif




namespace StaticDLL{

	//-------------------------------------------------Editor mode Menus-------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------


	//This is the Main editing mode menu
	class MenuEditorMain : public Menu
	{
		public:
			STATICDLL_API MenuEditorMain(Settings *settings);
			STATICDLL_API void InitMenu();
		private:
	};
	//This is the in editing esc(menu) 
	class MenuEditor : public Menu
	{
		public:
			STATICDLL_API MenuEditor(Settings *settings);
			STATICDLL_API void InitMenu();
		private:
	};

	//This is the map options menu
	class MenuMapOptions : public Menu
	{
	public:
		STATICDLL_API MenuMapOptions(Settings *settings, Map *currentMap);
		STATICDLL_API void InitMenu();

	private:

	};

	



	//-------------------------------------------------Shared mode Menus-------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------
	
	
	//This is the menu options for generic settings
	class MenuOptions : public Menu
	{
	public:
		STATICDLL_API MenuOptions(Settings *settings, Map *currentMap);
		STATICDLL_API void InitMenu();

	private:

	};


	//-------------------------------------------------Game mode Menus-------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------



	//This is the Main menu in gameplay
	class MenuGameMain : public Menu
	{
		public:
			STATICDLL_API MenuGameMain(Settings *settings);
			STATICDLL_API void InitMenu();
		private:
	};

}
#endif
