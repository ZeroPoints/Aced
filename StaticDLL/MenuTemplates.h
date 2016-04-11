#ifndef MENUTEMPLATES_H
#define MENUTEMPLATES_H

#define ALLEGRO_NO_MAGIC_MAIN

#include <vector>
#include <allegro5\allegro.h>
#include "Definitions.h"
#include <allegro5/allegro_primitives.h>
#include <algorithm>
#include "Menu.h"



#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif




namespace StaticDLL{
	class MenuEditorMain : public Menu
	{
		public:
			STATICDLL_API MenuEditorMain(Settings *settings);
			STATICDLL_API void InitMenu();
		private:
	};
	class MenuEditor : public Menu
	{
		public:
			STATICDLL_API MenuEditor(Settings *settings);
			STATICDLL_API void InitMenu();
		private:
	};

	class MenuMapOptions : public Menu
	{
		public:
			STATICDLL_API MenuMapOptions(Settings *settings, Map *currentMap);
			STATICDLL_API void InitMenu();

		private:

	};

	class MenuOptions : public Menu
	{
		public:
			STATICDLL_API MenuOptions(Settings *settings, Map *currentMap);
			STATICDLL_API void InitMenu();

		private:

	};


	//


	//-------------------------------------------------Game mode States-------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------

	class MenuGameMain : public Menu
	{
		public:
			STATICDLL_API MenuGameMain(Settings *settings);
			STATICDLL_API void InitMenu();
		private:
	};

}
#endif
