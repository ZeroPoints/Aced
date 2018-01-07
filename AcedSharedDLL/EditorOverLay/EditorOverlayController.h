#ifndef EDITOROVERLAYCONTROLLER_H
#define EDITOROVERLAYCONTROLLER_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <vector>
#include "../World/tile.h"
#include "../Config/BaseSettings.h"
#include "../Static/Definitions.h"
#include "../Misc/ObjectBase.h"
#include "EditorOverLay.h"
#include "TilePage.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include <ctime>
#include "../Config/AssetLibrary.h"

#ifdef ACEDSHAREDDLL_EXPORTS
   #define ACEDSHAREDDLL_API __declspec(dllexport)
#else
   #define ACEDSHAREDDLL_API __declspec(dllimport)
#endif


namespace AcedSharedDLL{
	//This is the container for a GUI overlay
	//Contains pages that have the tiles that can be placed(objects)
	class EditorOverLayController
	{
		public:

			ACEDSHAREDDLL_API EditorOverLayController(BaseSettings *settings, AssetLibrary *assetLibrary);



			ACEDSHAREDDLL_API ~EditorOverLayController()
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
			

			ACEDSHAREDDLL_API void Resize();



			ACEDSHAREDDLL_API void PreCalc();
			


			//Updates the overlay. None is default and will exit doing nothing. 
			//Opening will open the overlay over time till it hits it cap. 
			//Closing will close the overlay over time till it hits it cap.
			ACEDSHAREDDLL_API void Update();



			//Returns true if the editor overlay took control of mouse activity actions focus
			//Might need to pass false if user clicked in tile overlay bounds but not on an object while overlay is opened. 
			//So it doesnt interact with the back layer
			ACEDSHAREDDLL_API bool MouseActivity(ALLEGRO_EVENT *event, int cursorX, int cursorY);


			//Takes tab click to interact with overlay
			ACEDSHAREDDLL_API void KeyBoardActivity(ALLEGRO_EVENT *event);


			//Draws the overlay
			//And all combined objects that need to drawn
			ACEDSHAREDDLL_API void Draw();


			//Draws Tile picker window
			ACEDSHAREDDLL_API void DrawEditorOverlayWindow();
			//Draws a menu bar ATM it has no functionality
			ACEDSHAREDDLL_API void DrawMenuBar();
			//Draws all arrow objects that are on the overlay
			ACEDSHAREDDLL_API void DrawArrows();
			 

			ACEDSHAREDDLL_API void CreateTileArrow();

			ACEDSHAREDDLL_API void CreateEditorOverlays();

			ACEDSHAREDDLL_API void CreateMenuBar();



			ACEDSHAREDDLL_API EditorOverLay* FindEditorOverLay(STATES id)
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





			ACEDSHAREDDLL_API OVERLAYSTATE GetOverLayState()
			{
				return overLayState_;
			}


			ACEDSHAREDDLL_API void SetOverLayAction(OVERLAYACTIONS action)
			{
				overLayAction_ = action;
			}


			

			ACEDSHAREDDLL_API std::pair<AcedSharedDLL::STATES, EditorItemBase*> GetSelectedObject()
			{
				std::pair<AcedSharedDLL::STATES, EditorItemBase*> val;

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
			/*ACEDSHAREDDLL_API Tile* GetSelectedTile()
			{
				return tilePages_[currentTilePage_]->GetSelectedTile();
			}
			ACEDSHAREDDLL_API int GetSelectedTileX()
			{
				return tilePages_[currentTilePage_]->GetSelectedTileX();
			}
			ACEDSHAREDDLL_API int GetSelectedTileY()
			{
				return tilePages_[currentTilePage_]->GetSelectedTileY();
			}*/



		private:

			int widthMax_;
			int height_;


			AcedSharedDLL::OVERLAYACTIONS overLayAction_;
			AcedSharedDLL::OVERLAYSTATE overLayState_;




			
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
			BaseSettings *settings_;
	};
}
#endif
