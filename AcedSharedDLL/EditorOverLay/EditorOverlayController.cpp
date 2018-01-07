#include "EditorOverLayController.h"


namespace AcedSharedDLL{

	EditorOverLayController::EditorOverLayController(BaseSettings *settings, AssetLibrary *assetLibrary)
	{
		settings_ = settings;
		assetLibrary_ = assetLibrary;
		widthMax_ = 9;
		height_ = settings_->GetDisplayHeight()*Constants::TileSize();

		overLayState_ = AcedSharedDLL::OVERLAYSTATE::OVERLAYOPENED;
		overLayAction_ = AcedSharedDLL::OVERLAYACTIONS::OVERLAYNONE;


		chosenColor_ = al_map_rgb_f(0.8,0.8,0.8);


		//Ye keep this in the controller let thec ontroller keep a handle on the overlay (tile windows)
		CreateTileArrow();

		//Tile window this will create a bunch of editoroverlays(tile windows)
		CreateEditorOverlays();

		//Menu bar for editor overlay controller
		CreateMenuBar();

		

	}





	void EditorOverLayController::Resize()
	{
		menuBar_->SetWidth(settings_->GetDisplayWidth());
		tileWindowArrow_->SetCurrentPosition(widthMax_, settings_->GetDisplayHeight()/2);
		tileWindowBotLeftArrow_->SetCurrentPosition(0, settings_->GetDisplayHeight()-1);
		tileWindowBotRightArrow_->SetCurrentPosition(widthMax_-1, settings_->GetDisplayHeight()-1);

		for(int i = 0; i < editorOverLays_.size(); i++)
		{
			editorOverLays_[i]->Resize();
		}
		//tilePickerWindow_->SetWidth(widthMax_);
		//tilePickerWindow_->SetHeight(settings_->GetDisplayHeight());
		//currentTilePage_ = 0;
	}





	void EditorOverLayController::CreateTileArrow()
	{
		//Create an arrow object
		tileWindowArrow_ = new ObjectBase();
		tileWindowArrow_->SetCurrentPosition(widthMax_, settings_->GetDisplayHeight()/2);
		tileWindowArrow_->SetWidth(1);
		tileWindowArrow_->SetHeight(1);
		tileWindowArrow_->SetColor(al_map_rgb_f(0,0,0));

		tileWindowBotLeftArrow_ = new ObjectBase();
		tileWindowBotLeftArrow_->SetCurrentPosition(0, (double)(settings_->GetScreenHeight()-Constants::TileSize())/Constants::TileSize());
		tileWindowBotLeftArrow_->SetWidth(1);
		tileWindowBotLeftArrow_->SetHeight(1);
		tileWindowBotLeftArrow_->SetColor(al_map_rgb_f(0,0,0));

		tileWindowBotRightArrow_ = new ObjectBase();
		tileWindowBotRightArrow_->SetCurrentPosition(widthMax_-1, (double)(settings_->GetScreenHeight()-Constants::TileSize())/Constants::TileSize());
		tileWindowBotRightArrow_->SetWidth(1);
		tileWindowBotRightArrow_->SetHeight(1);
		tileWindowBotRightArrow_->SetColor(al_map_rgb_f(0,0,0));
	}


	void EditorOverLayController::CreateEditorOverlays()
	{
		//set first tile picker window
		currentEditorOverlayId_ = STATES::TILEIMAGEPICKER;

		//store them all in memory and access through id.
		//Dont want to use a push pop state system for it. 
		//making a window each click would be tedious
		int headerPositionX = 0;





		EditorOverLay* itemStore = new EditorOverLay(settings_, STATES::TILEIMAGEPICKER, assetLibrary_);
		itemStore->SetMenuHeader("  TILE IMAGES  ", 0,0);
		editorOverLays_.push_back(itemStore);
		headerPositionX = headerPositionX + itemStore->GetMenuHeader()->GetFontWidth();
/*
		itemStore = new EditorOverLay(settings_, STATES::TILECOLORPICKER, assetLibrary_);
		itemStore->SetMenuHeader("  TILE COLOURS  ", headerPositionX,0);
		editorOverLays_.push_back(itemStore);
		headerPositionX = headerPositionX + itemStore->GetMenuHeader()->GetFontWidth();
*/

		//load tile types from source pass into function
		itemStore = new EditorOverLay(settings_, STATES::TILETYPEPICKER, assetLibrary_);
		itemStore->SetMenuHeader("  TILE TYPES  ", headerPositionX,0);
		editorOverLays_.push_back(itemStore);
		headerPositionX = headerPositionX + itemStore->GetMenuHeader()->GetFontWidth();

		itemStore = new EditorOverLay(settings_, STATES::OBJECTIMAGEPICKER, assetLibrary_);
		itemStore->SetMenuHeader("  OBJECTS  ", headerPositionX, 0);
		editorOverLays_.push_back(itemStore);
		headerPositionX = headerPositionX + itemStore->GetMenuHeader()->GetFontWidth();

		itemStore = new EditorOverLay(settings_, STATES::ITEMPICKER, assetLibrary_);
		itemStore->SetMenuHeader("  ITEMS  ", headerPositionX, 0);
		editorOverLays_.push_back(itemStore);
		headerPositionX = headerPositionX + itemStore->GetMenuHeader()->GetFontWidth();

		itemStore = new EditorOverLay(settings_, STATES::ENEMYPICKER, assetLibrary_);
		itemStore->SetMenuHeader("  ENEMIES  ", headerPositionX, 0);
		editorOverLays_.push_back(itemStore);
		headerPositionX = headerPositionX + itemStore->GetMenuHeader()->GetFontWidth();
	}


	void EditorOverLayController::CreateMenuBar()
	{
		//Create an arrow object
		menuBar_ = new ObjectBase();
		menuBar_->SetCurrentPosition(0, 0);
		menuBar_->SetWidth(settings_->GetDisplayWidth());
		menuBar_->SetHeight(1);
		menuBar_->SetColor(al_map_rgb_f(0.8,0.8,0.8));
	}






	void EditorOverLayController::Update()
	{

		if(overLayAction_ == OVERLAYACTIONS::OVERLAYNONE)
		{
			return;
		}
		if(overLayAction_ == OVERLAYACTIONS::OVERLAYOPENING)
		{
			if(overLayState_ == OVERLAYSTATE::OVERLAYCLOSED)
			{
				auto result = FindEditorOverLay(currentEditorOverlayId_);
				if(result != nullptr)
				{
					if(result->GetOverlayWindowWidth() < widthMax_)
					{
						//Set tile picker overlay window width
						//Increment current overlays width
						result->IncrementOverLayWindowWidth();
						tileWindowArrow_->SetCurrentPositionX(tileWindowArrow_->GetCurrentPositionX() + (0.5));
					}
					else
					{
						overLayState_ = OVERLAYSTATE::OVERLAYOPENED;
						overLayAction_ = OVERLAYACTIONS::OVERLAYNONE;
					}
				}


				
			}
		}
		else if(overLayAction_ == OVERLAYACTIONS::OVERLAYCLOSING)
		{
			if(overLayState_ == OVERLAYSTATE::OVERLAYOPENED)
			{
				auto result = FindEditorOverLay(currentEditorOverlayId_);
				if(result != nullptr)
				{

					if(result->GetOverlayWindowWidth() > 0)
					{
						//Set tile picker overlay window width
						//Decrement current overlays width
						result->DecrementOverLayWindowWidth();
						tileWindowArrow_->SetCurrentPositionX(tileWindowArrow_->GetCurrentPositionX() - (0.5));
					}
					else
					{
						overLayState_ = OVERLAYSTATE::OVERLAYCLOSED;
						overLayAction_ = OVERLAYACTIONS::OVERLAYNONE;
					}
				}
				
			}
		}

	}


	
	//Draw all objects related to the overlay
	void EditorOverLayController::Draw()
	{
		
		//generic draw all object function
		DrawMenuBar();
		DrawEditorOverlayWindow();
		DrawArrows();
		
	}



	//Draws all arrow objects that are on the overlay
	void EditorOverLayController::DrawArrows()
	{
		tileWindowArrow_->DrawObject();
		////If its not opened dont draw it
		if(overLayState_ == OVERLAYSTATE::OVERLAYOPENED && overLayAction_ == OVERLAYACTIONS::OVERLAYNONE)
		{
			//Get current windows tile overlay and get its page to see if its greater then its size//function get total pages
			auto result = FindEditorOverLay(currentEditorOverlayId_);
			if(result != nullptr)
			{
				if(result->GetCurrentPage() > 0)
				{
					tileWindowBotLeftArrow_->DrawObject();
				}
				if(result->GetCurrentPage() < result->GetTotalPages())
				{
					tileWindowBotRightArrow_->DrawObject();
				}
			}
		}
	}


	void EditorOverLayController::DrawEditorOverlayWindow()
	{
		//draw all editoroverlay headers
		for(int i = 0; i < editorOverLays_.size(); i++)
		{
			editorOverLays_[i]->DrawHeaderText();
		}


		//GRAB current tile window overlay and pass drawing capabilities to it
		auto result = FindEditorOverLay(currentEditorOverlayId_);
		if(result != nullptr)
		{
			//If its not opened dont draw it
			result->DrawTilePicker();

			if(overLayState_ == OVERLAYSTATE::OVERLAYOPENED && overLayAction_ == OVERLAYACTIONS::OVERLAYNONE)
			{
				result->DrawItemBaseList();
			}

		}
	}

	

	void EditorOverLayController::DrawMenuBar()
	{
		menuBar_->DrawObject();
	}



	//Returns true if the editor overlay took control of mouse activity actions focus
	//Might need to pass false if user clicked in tile overlay bounds but not on an object while overlay is opened. 
	//So it doesnt interact with the back layer
	bool EditorOverLayController::MouseActivity(ALLEGRO_EVENT *event, int mouseX, int mouseY)
	{



		if(event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			switch(event->mouse.button)
			{
				case 1:
					if(tileWindowArrow_->ClickIntersects(mouseX, mouseY))
					{
						if(overLayState_ == OVERLAYSTATE::OVERLAYCLOSED)
						{
							overLayAction_ = OVERLAYACTIONS::OVERLAYOPENING;
						}
						else if(overLayState_ == OVERLAYSTATE::OVERLAYOPENED)
						{
							overLayAction_ = OVERLAYACTIONS::OVERLAYCLOSING;
						}
						return true;
					}



					//If its not opened dont detect mouse click
					if(overLayState_ == OVERLAYSTATE::OVERLAYOPENED && overLayAction_ == OVERLAYACTIONS::OVERLAYNONE)
					{
						//Mouse click for other tile arrows
						if(tileWindowBotLeftArrow_->ClickIntersects(mouseX, mouseY))
						{
							//Get current window overlay and call decrement page function
							auto result = FindEditorOverLay(currentEditorOverlayId_);
							if(result != nullptr)
							{
								result->DecrementCurrentPage();
							}

							return true;
						}

						//Mouse click for other tile arrows
						if(tileWindowBotRightArrow_->ClickIntersects(mouseX, mouseY))
						{
							//Get current window overlay and call increment page function
							auto result = FindEditorOverLay(currentEditorOverlayId_);
							if(result != nullptr)
							{
								result->IncrementCurrentPage();
							}

							return true;
						}
					}


					for(int i = 0; i < editorOverLays_.size(); i++)
					{
						if(editorOverLays_[i]->GetMenuHeader()->ClickIntersectsText(mouseX, mouseY))
						{
							currentEditorOverlayId_ = editorOverLays_[i]->GetId();

							overLayAction_ = OVERLAYACTIONS::OVERLAYOPENING;
							overLayState_ = OVERLAYSTATE::OVERLAYCLOSED;

							auto result = FindEditorOverLay(currentEditorOverlayId_);
							if(result != nullptr)
							{
								result->SetOverlayWindowWidth(0);
								tileWindowArrow_->SetCurrentPositionX(0);
							}


							return true;
						}
					}



					auto result = FindEditorOverLay(currentEditorOverlayId_);
					if(result != nullptr)
					{
						//Tile page took action over mouse activity so return true
						return result->MouseActivity(event, mouseX, mouseY);
						
					}


					break;
			}
		}


		return false;

	}



	//Takes tab click to interact with overlay
	void EditorOverLayController::KeyBoardActivity(ALLEGRO_EVENT *event){
		
		if(event->type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(event->keyboard.keycode)
			{
				case ALLEGRO_KEY_TAB:
					if(overLayState_ == OVERLAYSTATE::OVERLAYCLOSED)
					{
						overLayAction_ = OVERLAYACTIONS::OVERLAYOPENING;
					}
					else if(overLayState_ == OVERLAYSTATE::OVERLAYOPENED)
					{
						overLayAction_ = OVERLAYACTIONS::OVERLAYCLOSING;
					}
					break;
			}
		}
	}




}