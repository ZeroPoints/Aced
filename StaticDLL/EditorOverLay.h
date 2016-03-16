#ifndef EDITOROVERLAY_H
#define EDITOROVERLAY_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <vector>
#include "tile.h"
#include "Settings.h"
#include "Definitions.h"
#include "ObjectBase.h"
#include "TilePage.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include <ctime>


#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL{
	class EditorOverLay
	{
		public:

			STATICDLL_API EditorOverLay(Settings *settings);



			STATICDLL_API ~EditorOverLay()
			{
				delete tileWindowArrow_;
				delete tilePickerWindow_;
				delete menuBar_;
				fprintf(stderr,"An Overlay Destructed\n");
			}
			




			STATICDLL_API void PreCalc();
			


			//Updates the overlay. None is default and will exit doing nothing. 
			//Opening will open the overlay over time till it hits it cap. 
			//Closing will close the overlay over time till it hits it cap.
			STATICDLL_API void Update();



			STATICDLL_API void MouseActivity(ALLEGRO_EVENT *event, int cursorX, int cursorY);


			STATICDLL_API void KeyBoardActivity(ALLEGRO_EVENT *event);



			STATICDLL_API void Draw();


			STATICDLL_API void DrawTilePicker();
			STATICDLL_API void DrawTiles();
			STATICDLL_API void DrawMenuBar();



			STATICDLL_API void DrawArrows();
			 

			STATICDLL_API void CreateTileArrow();
			STATICDLL_API void CreateTileWindow();
			STATICDLL_API void CreateMenuBar();





			STATICDLL_API EnumDLL::OVERLAYSTATE GetOverLayState()
			{
				return overLayState_;
			}


			STATICDLL_API void SetOverLayAction(EnumDLL::OVERLAYACTIONS action)
			{
				overLayAction_ = action;
			}



			STATICDLL_API void CreateTiles(int x, int y);

			


		private:










			int top_;
			int bottom_;
			//The border of the entire Map
			int width_;
			int widthMax_;
			//The border of the entire Map
			int height_;
			
			
			StaticDLL::EnumDLL::OVERLAYACTIONS overLayAction_;
			StaticDLL::EnumDLL::OVERLAYSTATE overLayState_;


			ObjectBase *tileWindowArrow_;
			ObjectBase *tileWindowBotLeftArrow_;
			ObjectBase *tileWindowBotRightArrow_;


			ObjectBase *tilePickerWindow_;


			ObjectBase *menuBar_;

			int currentTilePage_;
			std::vector<TilePage*> tilePages_;


			std::vector<std::vector<Tile>> tiles_;

			
			ALLEGRO_EVENT_QUEUE *eventQueue_;
			ALLEGRO_EVENT *event_;

			ALLEGRO_COLOR chosenColor_;
			ALLEGRO_FONT *font30_;

			Settings *settings_;
	};
}
#endif
