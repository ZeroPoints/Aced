#ifndef EDITOROVERLAYCONTROLLER_H
#define EDITOROVERLAYCONTROLLER_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <vector>
#include "../World/tile.h"
#include "../Config/Settings.h"
#include "../Static/Definitions.h"
#include "../ObjectBase.h"
#include "EditorOverLay.h"
#include "TilePage.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include <ctime>
#include "../Config/AssetLibrary.h"

#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL{
	//This is the container for a GUI overlay
	//Contains pages that have the tiles that can be placed(objects)
	class EditorOverLayController
	{
		public:

			STATICDLL_API EditorOverLayController(Settings *settings, AssetLibrary *assetLibrary);



			STATICDLL_API ~EditorOverLayController()
			{
				//fprintf(stderr, "A EditorOverLayController Destructed\n");
				delete tileWindowArrow_;
				delete tileWindowBotLeftArrow_;
				delete tileWindowBotRightArrow_;

				for (EditorOverLay* item : editorOverLays_)
				{
					delete item;
					item = nullptr;
				}

				delete menuBar_;
			}
			

			STATICDLL_API void Resize();



			STATICDLL_API void PreCalc();
			


			//Updates the overlay. None is default and will exit doing nothing. 
			//Opening will open the overlay over time till it hits it cap. 
			//Closing will close the overlay over time till it hits it cap.
			STATICDLL_API void Update();



			//Returns true if the editor overlay took control of mouse activity actions focus
			//Might need to pass false if user clicked in tile overlay bounds but not on an object while overlay is opened. 
			//So it doesnt interact with the back layer
			STATICDLL_API bool MouseActivity(ALLEGRO_EVENT *event, int cursorX, int cursorY);


			//Takes tab click to interact with overlay
			STATICDLL_API void KeyBoardActivity(ALLEGRO_EVENT *event);


			//Draws the overlay
			//And all combined objects that need to drawn
			STATICDLL_API void Draw();


			//Draws Tile picker window
			STATICDLL_API void DrawEditorOverlayWindow();
			//Draws a menu bar ATM it has no functionality
			STATICDLL_API void DrawMenuBar();
			//Draws all arrow objects that are on the overlay
			STATICDLL_API void DrawArrows();
			 

			STATICDLL_API void CreateTileArrow();

			STATICDLL_API void CreateEditorOverlays();

			STATICDLL_API void CreateMenuBar();



			STATICDLL_API EditorOverLay* FindEditorOverLay(STATES id)
			{
				for(int i = 0; i < editorOverLays_.size(); i++)
				{
					if(editorOverLays_[i]->GetId() == id)
					{
						return editorOverLays_[i];
					}
				}
				return nullptr;
			}





			STATICDLL_API OVERLAYSTATE GetOverLayState()
			{
				return overLayState_;
			}


			STATICDLL_API void SetOverLayAction(OVERLAYACTIONS action)
			{
				overLayAction_ = action;
			}


			

			STATICDLL_API std::pair<StaticDLL::STATES, EditorItemBase*> GetSelectedObject()
			{
				std::pair<StaticDLL::STATES, EditorItemBase*> val;

				auto result = FindEditorOverLay(currentEditorOverlayId_);
				if(result != nullptr)
				{
					val.second = result->GetSelectedItemBase();
					val.first = result->GetId();
					return val;
				}
				return val;
			}






			//i might need these or something similar to return tile to parent above this
			/*STATICDLL_API Tile* GetSelectedTile()
			{
				return tilePages_[currentTilePage_]->GetSelectedTile();
			}
			STATICDLL_API int GetSelectedTileX()
			{
				return tilePages_[currentTilePage_]->GetSelectedTileX();
			}
			STATICDLL_API int GetSelectedTileY()
			{
				return tilePages_[currentTilePage_]->GetSelectedTileY();
			}*/



		private:

			int widthMax_;
			int height_;


			StaticDLL::OVERLAYACTIONS overLayAction_;
			StaticDLL::OVERLAYSTATE overLayState_;




			
			ObjectBase *tileWindowArrow_;
			ObjectBase *tileWindowBotLeftArrow_;
			ObjectBase *tileWindowBotRightArrow_;

			ObjectBase *menuBar_;


			STATES currentEditorOverlayId_;

			std::vector<EditorOverLay*> editorOverLays_;
			
			ALLEGRO_EVENT_QUEUE *eventQueue_;
			ALLEGRO_EVENT *event_;

			ALLEGRO_COLOR chosenColor_;
			ALLEGRO_FONT *font30_;


			AssetLibrary *assetLibrary_;
			Settings *settings_;
	};
}
#endif
