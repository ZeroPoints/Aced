#ifndef EDITOROVERLAY_H
#define EDITOROVERLAY_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <vector>
//#include "../World/Tile.h"
#include "../Config/BaseSettings.h"
#include "../Static/Definitions.h"
#include "../Misc/ObjectBase.h"
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
	class EditorOverLay
	{
		public:

			ACEDSHAREDDLL_API EditorOverLay(BaseSettings *settings, STATES id, AssetLibrary *assetLibrary);



			ACEDSHAREDDLL_API ~EditorOverLay()
			{
				//fprintf(stderr, "A EditorOverLay Destructed\n");

				delete tilePickerWindow_;

				for (TilePage* item : tilePages_)
				{
					delete item;
					item = nullptr;
				}

				

			}
			

			ACEDSHAREDDLL_API void Resize();



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
			ACEDSHAREDDLL_API void DrawTilePicker();
			//Draws Tile picker pages tiles
			ACEDSHAREDDLL_API void DrawItemBaseList();
			 
			ACEDSHAREDDLL_API void DrawHeaderText();



			ACEDSHAREDDLL_API void CreateTileWindow();





			ACEDSHAREDDLL_API OVERLAYSTATE GetOverLayState()
			{
				return overLayState_;
			}


			ACEDSHAREDDLL_API void SetOverLayAction(OVERLAYACTIONS action)
			{
				overLayAction_ = action;
			}

			ACEDSHAREDDLL_API void CreateObjectImagePicker();
			ACEDSHAREDDLL_API void CreateEnemyImagePicker();
			ACEDSHAREDDLL_API void CreateItemImagePicker();
			
			ACEDSHAREDDLL_API void CreateTileImagePicker();
			ACEDSHAREDDLL_API void CreateTileTypes();

			ACEDSHAREDDLL_API void FormatTiles();
			ACEDSHAREDDLL_API void CreateTilesColors();
			ACEDSHAREDDLL_API void CreateTilePages();

			
			ACEDSHAREDDLL_API EditorItemBase* GetSelectedItemBase()
			{
				return tilePages_[currentTilePage_]->GetSelectedItemBase();
			}
			ACEDSHAREDDLL_API int GetSelectedTileX()
			{
				return tilePages_[currentTilePage_]->GetSelectedTileX();
			}
			ACEDSHAREDDLL_API int GetSelectedTileY()
			{
				return tilePages_[currentTilePage_]->GetSelectedTileY();
			}



			ACEDSHAREDDLL_API int GetTotalPages()
			{
				return tilePages_.size()-1;
			}
			ACEDSHAREDDLL_API void SetCurrentPage(int page)
			{
				currentTilePage_ = page;
			}
			ACEDSHAREDDLL_API int GetCurrentPage()
			{
				return currentTilePage_;
			}
			ACEDSHAREDDLL_API void IncrementCurrentPage()
			{
				if(currentTilePage_ < tilePages_.size()-1)
				{
					currentTilePage_++;
				}
			}
			ACEDSHAREDDLL_API void DecrementCurrentPage()
			{
				if(currentTilePage_ > 0)
				{
					currentTilePage_--;
				}
			}


			
			ACEDSHAREDDLL_API void SetId(AcedSharedDLL::STATES id)
			{
				id_ = id;
			}
			ACEDSHAREDDLL_API AcedSharedDLL::STATES GetId()
			{
				return id_;
			}



			ACEDSHAREDDLL_API void IncrementOverLayWindowWidth()
			{
				tilePickerWindow_->SetWidth(tilePickerWindow_->GetWidth() + (0.5));
			}
			ACEDSHAREDDLL_API void DecrementOverLayWindowWidth()
			{
				tilePickerWindow_->SetWidth(tilePickerWindow_->GetWidth() - (0.5));
			}
			ACEDSHAREDDLL_API double GetOverlayWindowWidth()
			{
				return tilePickerWindow_->GetWidth();
			}
			ACEDSHAREDDLL_API void SetOverlayWindowWidth(double width)
			{
				tilePickerWindow_->SetWidth(width);
			}

			ACEDSHAREDDLL_API void SetMenuHeader(char *text, double positionX, double positionY);
			ACEDSHAREDDLL_API ObjectBase *GetMenuHeader()
			{
				return menuHeaderItem_;
			};

		private:



			AcedSharedDLL::STATES id_;
			
			int top_;
			int bottom_;
			//The border of the entire Map
			int width_;
			int widthMax_;
			int tileVectorWidthMax_;
			//The border of the entire Map
			int height_;
			int imageBundleDictionarySize_;
			int imageBundleDictionaryId_;
			Image *remove_;

			
			AcedSharedDLL::OVERLAYACTIONS overLayAction_;
			AcedSharedDLL::OVERLAYSTATE overLayState_;

			AcedSharedDLL::IMAGESETS imageSetId_;

			ObjectBase *tilePickerWindow_;


			ObjectBase *menuHeaderItem_;



			int currentTilePage_;
			std::vector<TilePage*> tilePages_;


			std::vector<std::vector<EditorItemBase>> itemBaseList_;


			
			ALLEGRO_EVENT_QUEUE *eventQueue_;
			ALLEGRO_EVENT *event_;

			ALLEGRO_COLOR chosenColor_;


			AssetLibrary *assetLibrary_;
			BaseSettings *settings_;
	};
}
#endif
