#ifndef STATETEMPLATES_H
#define STATETEMPLATES_H


#define ALLEGRO_NO_MAGIC_MAIN


#include <allegro5\allegro.h>
#include <vector>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "State.h"



#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL{

	//-------------------------------------------------Editor mode States-------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------

	//This is the Main editing mode state whilst editing maps
	class StateEditorMode : public State
	{
		public:

			STATICDLL_API ~StateEditorMode()
			{
				//fprintf(stderr, "A StateEditorMode Destructed\n");
				delete editorOverLayController_;
			}

			STATICDLL_API void InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap, AssetLibrary *assetLibrary);
			////key press probs goes in update
			STATICDLL_API void KeyPress();
			STATICDLL_API void MouseActivity();
			STATICDLL_API void EditorModeMouseActivity();
			STATICDLL_API void Update();
			STATICDLL_API void Draw();
			STATICDLL_API void Resume();
			STATICDLL_API void DragMap();
		private:
			//This object isnt being Deleted at the moment
			EditorOverLayController *editorOverLayController_;
			
			std::pair<StaticDLL::EnumDLL::STATES, EditorItemBase*> selectedItemBase_;
	};



	//Main menu for edit app
	class StateEditorMainMenu : public State
	{
		public:

			STATICDLL_API void InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap, AssetLibrary *assetLibrary);
			////key press probs goes in update
			STATICDLL_API void KeyPress();
			STATICDLL_API void Update();
			STATICDLL_API void Draw();
			STATICDLL_API void Resume();
		private:
	};





	//Menu inside editor whilst editing
	class StateEditorMenu : public State
	{
		public:
			STATICDLL_API void InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap, AssetLibrary *assetLibrary);
			////key press probs goes in update
			STATICDLL_API void KeyPress();
			STATICDLL_API void Update();
			STATICDLL_API void Draw();
			STATICDLL_API void Resume();
			STATICDLL_API void CleanUp();
		private:
	};




	//Map resizing and customisation options
	class StateMapOptions : public State
	{
		public:
			STATICDLL_API void InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap, AssetLibrary *assetLibrary);
			////key press probs goes in update
			STATICDLL_API void KeyPress();
			STATICDLL_API void Update();
			STATICDLL_API void Draw();
		private:
	};









	//-------------------------------------------------Shared mode States-------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------



	//Application options menu
	class StateOptions : public State
	{
	public:
		STATICDLL_API void InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap, AssetLibrary *assetLibrary);
		////key press probs goes in update
		STATICDLL_API void KeyPress();
		STATICDLL_API void Update();
		STATICDLL_API void Draw();
	private:
	};




	//-------------------------------------------------Game mode States-------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------------------



	//Application game state for game play
	class StateGameMode : public State
	{
		public:
			STATICDLL_API void InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap, AssetLibrary *assetLibrary);
			////key press probs goes in update
			STATICDLL_API void KeyPress();
			STATICDLL_API void MouseActivity();
			STATICDLL_API void Update();
			STATICDLL_API void Draw();
			STATICDLL_API void Resume();
		private:
			std::vector<Player*> players_;
			Player* player1_;


	};




	//Application main menu
	class StateGameMainMenu : public State
	{
		public:
			STATICDLL_API void InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap, AssetLibrary *assetLibrary);
			////key press probs goes in update
			STATICDLL_API void KeyPress();
			STATICDLL_API void Update();
			STATICDLL_API void Draw();
			STATICDLL_API void Resume();
		private:

	};
}
#endif


