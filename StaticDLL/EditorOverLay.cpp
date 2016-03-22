#include "EditorOverLay.h"


namespace StaticDLL{

	EditorOverLay::EditorOverLay(Settings *settings)
	{

		settings_ = settings;


		widthMax_ = 9;
		height_ = settings_->GetDisplayHeight()*Constants::TileSize;

		overLayState_ = StaticDLL::EnumDLL::OVERLAYSTATE::OVERLAYOPENED;
		overLayAction_ = StaticDLL::EnumDLL::OVERLAYACTIONS::OVERLAYNONE;

		chosenColor_ = al_map_rgb_f(0.8,0.3,0.3);
		currentTilePage_ = 0;

		std::vector<std::vector<Tile>> tiles_(4,std::vector<Tile>(143));
		CreateTiles(4,143);


		CreateTileArrow();
		CreateTileWindow();
		CreateMenuBar();

		
		fprintf(stderr,"An Overlay Created\n");

	}


	void EditorOverLay::Resize()
	{
		CreateTiles(4,143);
		menuBar_->SetWidth(settings_->GetDisplayWidth());
		tileWindowArrow_->SetCurrentPosition(widthMax_, settings_->GetDisplayHeight()/2);
		tileWindowBotLeftArrow_->SetCurrentPosition(0, settings_->GetDisplayHeight()-1);
		tileWindowBotRightArrow_->SetCurrentPosition(widthMax_-1, settings_->GetDisplayHeight()-1);
		tilePickerWindow_->SetWidth(widthMax_);
		tilePickerWindow_->SetHeight(settings_->GetDisplayHeight());
		currentTilePage_ = 0;
	}





	void EditorOverLay::CreateTileArrow()
	{
		//Create an arrow object
		tileWindowArrow_ = new ObjectBase();
		tileWindowArrow_->SetCurrentPosition(widthMax_, settings_->GetDisplayHeight()/2);
		tileWindowArrow_->SetWidth(1);
		tileWindowArrow_->SetHeight(1);
		tileWindowArrow_->SetColor(al_map_rgb_f(0.3,0.6,0.6));

		tileWindowBotLeftArrow_ = new ObjectBase();
		tileWindowBotLeftArrow_->SetCurrentPosition(0, (double)(settings_->GetScreenHeight()-Constants::TileSize)/Constants::TileSize);
		tileWindowBotLeftArrow_->SetWidth(1);
		tileWindowBotLeftArrow_->SetHeight(1);
		tileWindowBotLeftArrow_->SetColor(al_map_rgb_f(0.3,0.6,0.6));

		tileWindowBotRightArrow_ = new ObjectBase();
		tileWindowBotRightArrow_->SetCurrentPosition(widthMax_-1, (double)(settings_->GetScreenHeight()-Constants::TileSize)/Constants::TileSize);
		tileWindowBotRightArrow_->SetWidth(1);
		tileWindowBotRightArrow_->SetHeight(1);
		tileWindowBotRightArrow_->SetColor(al_map_rgb_f(0.3,0.6,0.6));
	}


	void EditorOverLay::CreateTileWindow()
	{
		//Create an arrow object
		tilePickerWindow_ = new ObjectBase();
		tilePickerWindow_->SetCurrentPosition(0, 1);
		tilePickerWindow_->SetWidth(widthMax_);
		tilePickerWindow_->SetHeight(settings_->GetDisplayHeight());
		tilePickerWindow_->SetColor(al_map_rgb_f(0.8,0.3,0.3));
	}


	void EditorOverLay::CreateMenuBar()
	{
		//Create an arrow object
		menuBar_ = new ObjectBase();
		menuBar_->SetCurrentPosition(0, 0);
		menuBar_->SetWidth(settings_->GetDisplayWidth());
		menuBar_->SetHeight(1);
		menuBar_->SetColor(al_map_rgb_f(1,1,1));
	}




	//Load list of all tiles into tile pages
	//also sizes display of these
	void EditorOverLay::CreateTiles(int x, int y)
	{
		srand(time(nullptr));

		int topOffset = 2;
		int leftOffset = 1;
		int displacementOffset = 2;
		int screenHeight = settings_->GetDisplayHeight() - 2;
		//Displace counter for screen height if its not even
		if(screenHeight%2 == 1)
		{
			screenHeight--;
		}


		//is this the best way to clean those objects?
		tiles_.resize(0);
		tiles_.clear();
		tiles_.resize(x);
		for(int i = 0; i < tiles_.size(); i++)
		{
			tiles_[i].resize(y);
		}

		

		//math in here seems wrong
		//FIX IT so resizing or different size screens get adjusted properly
		for(int i = 0; i < x; i++)
		{
			for(int j = 0; j < y; j++)
			{
				tiles_[i][j].SetColor(al_map_rgb_f((double)rand() / RAND_MAX,(double)rand() / RAND_MAX,(double)rand() / RAND_MAX));//sets all tiles to grey
				tiles_[i][j].SetTileType(EnumDLL::TILETYPE::SOLIDTILE);
				int posX = leftOffset+i*displacementOffset;
				int posY = topOffset + ((j*displacementOffset)%(screenHeight));
				tiles_[i][j].SetCurrentPosition(posX,posY);
				tiles_[i][j].SetWidth(1);
				tiles_[i][j].SetHeight(1);
			}
		}

		//reset pages
		tilePages_.resize(0);
		tilePages_.clear();
		int pages = tiles_[0].size()/(screenHeight/2);
		int extraPage = (tiles_[0].size()%(screenHeight/2))>0?1:0;
		//There was a reason i added extra page but i cant remmeber but its working
		//Go through the tile pages adding in the tiles as a ref
		for(int i = 0; i < pages+extraPage; i++)
		{
			tilePages_.push_back(new TilePage());
			int newMin = (screenHeight/2*i) == 0 ? 0 : (screenHeight/2*i);
			int newMax = (screenHeight/2*i) + screenHeight/2;
			if(newMin > tiles_[0].size())
			{
				newMin = tiles_[0].size();
			}
			if(newMax > tiles_[0].size())
			{
				newMax = tiles_[0].size();
			}
			tilePages_[i]->SetTiles(newMin, newMax, x);
		}
	}


	void EditorOverLay::Update()
	{
		if(overLayAction_ == EnumDLL::OVERLAYACTIONS::OVERLAYNONE)
		{
			return;
		}
		if(overLayAction_ == EnumDLL::OVERLAYACTIONS::OVERLAYOPENING)
		{
			if(overLayState_ == EnumDLL::OVERLAYSTATE::OVERLAYCLOSED)
			{
				if(tilePickerWindow_->GetWidth() < widthMax_)
				{
					tilePickerWindow_->SetWidth(tilePickerWindow_->GetWidth() + (10.0/Constants::TileSize));
					tileWindowArrow_->SetCurrentPositionX(tileWindowArrow_->GetCurrentPositionX() + (10.0/Constants::TileSize));
				}
				else
				{
					overLayState_ = EnumDLL::OVERLAYSTATE::OVERLAYOPENED;
					overLayAction_ = EnumDLL::OVERLAYACTIONS::OVERLAYNONE;
				}
			}
		}
		else if(overLayAction_ == EnumDLL::OVERLAYACTIONS::OVERLAYCLOSING)
		{
			if(overLayState_ == EnumDLL::OVERLAYSTATE::OVERLAYOPENED)
			{
				if(tilePickerWindow_->GetWidth() > 0)
				{
					tilePickerWindow_->SetWidth(tilePickerWindow_->GetWidth() - (10.0/Constants::TileSize));
					tileWindowArrow_->SetCurrentPositionX(tileWindowArrow_->GetCurrentPositionX() - (10.0/Constants::TileSize));
				}
				else
				{
					overLayState_ = EnumDLL::OVERLAYSTATE::OVERLAYCLOSED;
					overLayAction_ = EnumDLL::OVERLAYACTIONS::OVERLAYNONE;
				}
			}
		}
	}


	
	//Draw all objects related to the overlay
	void EditorOverLay::Draw()
	{
		DrawMenuBar();
		DrawTilePicker();
		DrawArrows();
		DrawTiles();
	}



	//Draws all arrow objects that are on the overlay
	void EditorOverLay::DrawArrows()
	{
		tileWindowArrow_->DrawObject();
		//If its not opened dont draw it
		if(overLayState_ == EnumDLL::OVERLAYSTATE::OVERLAYOPENED && overLayAction_ == EnumDLL::OVERLAYACTIONS::OVERLAYNONE)
		{
			if(currentTilePage_ > 0)
			{
				tileWindowBotLeftArrow_->DrawObject();
			}
			if(currentTilePage_ < tilePages_.size()-1)
			{
				tileWindowBotRightArrow_->DrawObject();
			}
		}
	}


	//Draw tile over lay background for pages
	void EditorOverLay::DrawTilePicker()
	{
		tilePickerWindow_->DrawObject();
	}

	//Draw the tiles on the pages
	void EditorOverLay::DrawTiles()
	{
		//If its not opened dont draw it
		if(overLayState_ == EnumDLL::OVERLAYSTATE::OVERLAYOPENED && overLayAction_ == EnumDLL::OVERLAYACTIONS::OVERLAYNONE)
		{
			tilePages_[currentTilePage_]->DrawTiles(tiles_);
		}
	}

	void EditorOverLay::DrawMenuBar()
	{
		menuBar_->DrawObject();
	}



	//Returns true if the editor overlay took control of mouse activity actions focus
	//Might need to pass false if user clicked in tile overlay bounds but not on an object while overlay is opened. 
	//So it doesnt interact with the back layer
	bool EditorOverLay::MouseActivity(ALLEGRO_EVENT *event, int mouseX, int mouseY)
	{
		if(event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			switch(event->mouse.button)
			{
				case 1:
					if(tileWindowArrow_->ClickIntersects(mouseX, mouseY))
					{
						if(overLayState_ == EnumDLL::OVERLAYSTATE::OVERLAYCLOSED)
						{
							overLayAction_ = EnumDLL::OVERLAYACTIONS::OVERLAYOPENING;
						}
						else if(overLayState_ == EnumDLL::OVERLAYSTATE::OVERLAYOPENED)
						{
							overLayAction_ = EnumDLL::OVERLAYACTIONS::OVERLAYCLOSING;
						}
						return true;
					}



					//If its not opened dont detect mouse click
					if(overLayState_ == EnumDLL::OVERLAYSTATE::OVERLAYOPENED && overLayAction_ == EnumDLL::OVERLAYACTIONS::OVERLAYNONE)
					{
						//Mouse click for other tile arrows
						if(tileWindowBotLeftArrow_->ClickIntersects(mouseX, mouseY))
						{
							if(currentTilePage_ > 0)
							{
								currentTilePage_--;
							}	
							return true;
						}

						//Mouse click for other tile arrows
						if(tileWindowBotRightArrow_->ClickIntersects(mouseX, mouseY))
						{
							if(currentTilePage_ < tilePages_.size()-1)
							{
								currentTilePage_++;
							}	
							return true;
						}
					}



					//Tile page took action over mouse activity so return true
					if(tilePages_[currentTilePage_]->MouseActivity(tiles_, mouseX, mouseY))
					{
						return true;
					}


					break;
			}
		}


		return false;

	}



	//Takes tab click to interact with overlay
	void EditorOverLay::KeyBoardActivity(ALLEGRO_EVENT *event){
		if(event->type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(event->keyboard.keycode)
			{
				case ALLEGRO_KEY_TAB:
					if(overLayState_ == EnumDLL::OVERLAYSTATE::OVERLAYCLOSED)
					{
						overLayAction_ = EnumDLL::OVERLAYACTIONS::OVERLAYOPENING;
					}
					else if(overLayState_ == EnumDLL::OVERLAYSTATE::OVERLAYOPENED)
					{
						overLayAction_ = EnumDLL::OVERLAYACTIONS::OVERLAYCLOSING;
					}
					break;
			}
		}
	}
}