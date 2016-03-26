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
	//This is the container for a GUI overlay
	//Contains pages that have the tiles that can be placed(objects)
	class EditorOverLay
	{
		public:

			STATICDLL_API EditorOverLay(Settings *settings, EnumDLL::STATES id);



			STATICDLL_API ~EditorOverLay()
			{
				delete tilePickerWindow_;

				for (TilePage* item : tilePages_)
				{
					delete item;
					item = nullptr;
				}

				

				fprintf(stderr,"An Overlay Destructed\n");
			}
			

			STATICDLL_API void Resize();



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
			STATICDLL_API void DrawTilePicker();
			//Draws Tile picker pages tiles
			STATICDLL_API void DrawTiles();
			 
			STATICDLL_API void DrawHeaderText();



			STATICDLL_API void CreateTileWindow();





			STATICDLL_API EnumDLL::OVERLAYSTATE GetOverLayState()
			{
				return overLayState_;
			}


			STATICDLL_API void SetOverLayAction(EnumDLL::OVERLAYACTIONS action)
			{
				overLayAction_ = action;
			}


			STATICDLL_API void CreateTileTypes();

			STATICDLL_API void FormatTiles();
			STATICDLL_API void CreateTiles(int x, int y);
			STATICDLL_API void CreateTilePages();

			
			STATICDLL_API Tile* GetSelectedTile()
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
			}



			STATICDLL_API int GetTotalPages()
			{
				return tilePages_.size()-1;
			}
			STATICDLL_API void SetCurrentPage(int page)
			{
				currentTilePage_ = page;
			}
			STATICDLL_API int GetCurrentPage()
			{
				return currentTilePage_;
			}
			STATICDLL_API void IncrementCurrentPage()
			{
				if(currentTilePage_ < tilePages_.size()-1)
				{
					currentTilePage_++;
				}
			}
			STATICDLL_API void DecrementCurrentPage()
			{
				if(currentTilePage_ > 0)
				{
					currentTilePage_--;
				}
			}


			
			STATICDLL_API void SetId(StaticDLL::EnumDLL::STATES id)
			{
				id_ = id;
			}
			STATICDLL_API StaticDLL::EnumDLL::STATES GetId()
			{
				return id_;
			}



			STATICDLL_API void IncrementOverLayWindowWidth()
			{
				tilePickerWindow_->SetWidth(tilePickerWindow_->GetWidth() + (10.0/Constants::TileSize));
			}
			STATICDLL_API void DecrementOverLayWindowWidth()
			{
				tilePickerWindow_->SetWidth(tilePickerWindow_->GetWidth() - (10.0/Constants::TileSize));
			}
			STATICDLL_API double GetOverlayWindowWidth()
			{
				return tilePickerWindow_->GetWidth();
			}
			STATICDLL_API void SetOverlayWindowWidth(double width)
			{
				tilePickerWindow_->SetWidth(width);
			}

			STATICDLL_API void SetMenuHeader(char *text, double positionX, double positionY);
			STATICDLL_API ObjectBase *GetMenuHeader()
			{
				return menuHeaderItem_;
			};

		private:



			StaticDLL::EnumDLL::STATES id_;
			
			int top_;
			int bottom_;
			//The border of the entire Map
			int width_;
			int widthMax_;
			int tileVectorWidthMax_;
			//The border of the entire Map
			int height_;
			
			
			StaticDLL::EnumDLL::OVERLAYACTIONS overLayAction_;
			StaticDLL::EnumDLL::OVERLAYSTATE overLayState_;



			ObjectBase *tilePickerWindow_;


			ObjectBase *menuHeaderItem_;



			int currentTilePage_;
			std::vector<TilePage*> tilePages_;


			std::vector<std::vector<Tile>> tiles_;

			std::vector<std::vector<Tile>> tilesTest_;



			//std::vector<Tile> tilesTest_;

			
			ALLEGRO_EVENT_QUEUE *eventQueue_;
			ALLEGRO_EVENT *event_;

			ALLEGRO_COLOR chosenColor_;



			Settings *settings_;
	};
}
#endif
