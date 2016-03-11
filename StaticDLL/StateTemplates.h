#ifndef STATETEMPLATES_H
#define STATETEMPLATES_H


#define ALLEGRO_NO_MAGIC_MAIN


#include <allegro5\allegro.h>
#include <vector>
#include "Player.h"
#include "map.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include "State.h"
#include "EditorOverLay.h"




#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL{
	class StateEditorMode : public State
	{
		public:
			STATICDLL_API void InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap);
			////key press probs goes in update
			STATICDLL_API void KeyPress();
			STATICDLL_API void MouseActivity();
			STATICDLL_API void EditorModeMouseActivity();
			STATICDLL_API void Update();
			STATICDLL_API void Draw();
			STATICDLL_API void Resume();
			STATICDLL_API void DragMap();
		private:
			EditorOverLay *editorOverLay_;
	};
	class StateEditorMainMenu : public State
	{
		public:
			STATICDLL_API void InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap);
			////key press probs goes in update
			STATICDLL_API void KeyPress();
			STATICDLL_API void Update();
			STATICDLL_API void Draw();
			STATICDLL_API void Resume();
		private:
	};
	class StateEditorMenu : public State
	{
		public:
			STATICDLL_API void InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap);
			////key press probs goes in update
			STATICDLL_API void KeyPress();
			STATICDLL_API void Update();
			STATICDLL_API void Draw();
			STATICDLL_API void Resume();
			STATICDLL_API void CleanUp();
		private:
	};
	class StateMapOptions : public State
	{
		public:
			STATICDLL_API void InitState(ALLEGRO_DISPLAY *display, Settings *settings, Map *currentMap);
			////key press probs goes in update
			STATICDLL_API void KeyPress();
			STATICDLL_API void Update();
			STATICDLL_API void Draw();
		private:
	};




}
#endif


