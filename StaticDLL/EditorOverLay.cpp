#include "EditorOverLay.h"


namespace StaticDLL{

	EditorOverLay::EditorOverLay(Settings *settings, EnumDLL::STATES id)
	{
		id_ = id;

		settings_ = settings;


		widthMax_ = 9;
		tileVectorWidthMax_ = 4;

		height_ = settings_->GetDisplayHeight()*Constants::TileSize;

		overLayState_ = StaticDLL::EnumDLL::OVERLAYSTATE::OVERLAYOPENED;
		overLayAction_ = StaticDLL::EnumDLL::OVERLAYACTIONS::OVERLAYNONE;

		chosenColor_ = al_map_rgb_f(0.8,0.3,0.3);
		currentTilePage_ = 0;


		FormatTiles();

		//CreateTiles(4,143);


		CreateTileWindow();

		
		fprintf(stderr,"An Overlay Created\n");

	}


	void EditorOverLay::Resize()
	{
		if(id_ == EnumDLL::STATES::TILEPICKER)
		{
			CreateTiles(tileVectorWidthMax_,60);
		}
		else if(id_ == EnumDLL::STATES::TILETYPEPICKER)
		{
			CreateTileTypes();
			CreateTilePages();
		}
		tilePickerWindow_->SetWidth(widthMax_);
		tilePickerWindow_->SetHeight(settings_->GetDisplayHeight());
		currentTilePage_ = 0;
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





	//Load list of all tiles into tile pages
	//also sizes display of these
	void EditorOverLay::FormatTiles()
	{
		if(id_ == EnumDLL::STATES::TILEPICKER)
		{
			CreateTiles(tileVectorWidthMax_,60);
		}
		else if(id_ == EnumDLL::STATES::TILETYPEPICKER)
		{
			CreateTileTypes();
			CreateTilePages();
		}
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

		CreateTilePages();
	}


	void EditorOverLay::CreateTilePages()
	{
		int screenHeight = settings_->GetDisplayHeight() - 2;
		if(screenHeight%2 == 1)
		{
			screenHeight--;
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
			tilePages_[i]->SetTiles(newMin, newMax, tileVectorWidthMax_);
		}
	}


	
	//Draw all objects related to the overlay
	void EditorOverLay::Draw()
	{
		DrawTilePicker();
		DrawTiles();
	}



	

	//Draw tile over lay background for pages
	//mmight be able to pass this to overlay controller and let it handle the picker window
	void EditorOverLay::DrawTilePicker()
	{
		tilePickerWindow_->DrawObject();
	}

	//Draw the tiles on the pages
	void EditorOverLay::DrawTiles()
	{
		//draw collision boxes if page id is tiletype
		tilePages_[currentTilePage_]->DrawTiles(tiles_, (id_ == EnumDLL::STATES::TILETYPEPICKER));
	}


	//Draw the tiles on the pages
	void EditorOverLay::DrawHeaderText()
	{
		menuHeaderItem_->DrawObjectText();
		menuHeaderItem_->DrawObjectLeftBorder();
		menuHeaderItem_->DrawObjectRightBorder();
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


					if(tilePages_[currentTilePage_]->MouseActivity(tiles_, mouseX, mouseY))
					{
						return true;
					}
					break;
			}
		}
		return false;

	}




	void EditorOverLay::SetMenuHeader(char *text, double positionX, double positionY)
	{
		menuHeaderItem_ = new ObjectBase();
		menuHeaderItem_->SetText(al_ustr_new(text));
		menuHeaderItem_->SetCurrentPosition(positionX,positionY);
		menuHeaderItem_->SetFont(al_load_font("arial.ttf", 20, 0));
		menuHeaderItem_->SetColor(al_map_rgb_f(0,0,0));
		menuHeaderItem_->SetWidth(menuHeaderItem_->GetFontWidth());
		menuHeaderItem_->SetHeight(20);
	}

	


















	//Big mess of code to create tile types menu
	void EditorOverLay::CreateTileTypes()
	{
		int screenHeight = settings_->GetDisplayHeight() - 2;
		//Displace counter for screen height if its not even
		if(screenHeight%2 == 1)
		{
			screenHeight--;
		}
		int topOffset = 2;
		int leftOffset = 1;
		int displacementOffset = 2;
		int k = 0;
		int l = 0;
		int posX = leftOffset+k*displacementOffset;
		int posY = topOffset + ((l*displacementOffset)%(screenHeight));
		std::vector<Tile> objs;
		Tile* currentTile = new Tile();
		currentTile->SetColor(al_map_rgb_f(0.3,0.6,0.6));
		currentTile->SetTileType(EnumDLL::TILETYPE::SOLIDTILE);
		currentTile->SetCurrentPosition(posX,posY);
		currentTile->SetWidth(1);
		currentTile->SetHeight(1);
		objs.push_back(*currentTile);
		k = (k + 1)%tileVectorWidthMax_;
		if(k % tileVectorWidthMax_ == 0)
		{
			l++;
		}
		posX = leftOffset+k*displacementOffset;
		posY = topOffset + ((l*displacementOffset)%(screenHeight));
		currentTile = new Tile();
		currentTile->SetColor(al_map_rgb_f(0.3,0.6,0.6));
		currentTile->SetTileType(EnumDLL::TILETYPE::COLLISIONTOPTILE);
		currentTile->SetCurrentPosition(posX,posY);
		currentTile->SetWidth(1);
		currentTile->SetHeight(1);
		objs.push_back(*currentTile);
		k = (k + 1)%tileVectorWidthMax_;
		if(k % tileVectorWidthMax_ == 0)
		{
			l++;
		}
		posX = leftOffset+k*displacementOffset;
		posY = topOffset + ((l*displacementOffset)%(screenHeight));
		currentTile = new Tile();
		currentTile->SetColor(al_map_rgb_f(0.3,0.6,0.6));
		currentTile->SetTileType(EnumDLL::TILETYPE::COLLISIONLEFTTILE);
		currentTile->SetCurrentPosition(posX,posY);
		currentTile->SetWidth(1);
		currentTile->SetHeight(1);
		objs.push_back(*currentTile);
		k = (k + 1)%tileVectorWidthMax_;
		if(k % tileVectorWidthMax_ == 0)
		{
			l++;
		}
		posX = leftOffset+k*displacementOffset;
		posY = topOffset + ((l*displacementOffset)%(screenHeight));
		currentTile = new Tile();
		currentTile->SetColor(al_map_rgb_f(0.3,0.6,0.6));
		currentTile->SetTileType(EnumDLL::TILETYPE::COLLISIONRIGHTTILE);
		currentTile->SetCurrentPosition(posX,posY);
		currentTile->SetWidth(1);
		currentTile->SetHeight(1);
		objs.push_back(*currentTile);
		k = (k + 1)%tileVectorWidthMax_;
		if(k % tileVectorWidthMax_ == 0)
		{
			l++;
		}
		posX = leftOffset+k*displacementOffset;
		posY = topOffset + ((l*displacementOffset)%(screenHeight));
		currentTile = new Tile();
		currentTile->SetColor(al_map_rgb_f(0.3,0.6,0.6));
		currentTile->SetTileType(EnumDLL::TILETYPE::EMPTYTILE);
		currentTile->SetCurrentPosition(posX,posY);
		currentTile->SetWidth(1);
		currentTile->SetHeight(1);
		objs.push_back(*currentTile);
		tiles_.resize(tileVectorWidthMax_);
		for(int i = 0; i < objs.size(); i++)
		{
			tiles_[i%tileVectorWidthMax_].push_back(objs[i]);
		}
	}
}