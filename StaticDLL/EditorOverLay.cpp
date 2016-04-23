#include "EditorOverLay.h"


namespace StaticDLL{

	EditorOverLay::EditorOverLay(Settings *settings, EnumDLL::STATES id, ImageLoader *imageLoader)
	{
		id_ = id;

		settings_ = settings;
		imageLoader_ = imageLoader;

		widthMax_ = 9;
		tileVectorWidthMax_ = 4;

		height_ = settings_->GetDisplayHeight()*Constants::TileSize;

		overLayState_ = StaticDLL::EnumDLL::OVERLAYSTATE::OVERLAYOPENED;
		overLayAction_ = StaticDLL::EnumDLL::OVERLAYACTIONS::OVERLAYNONE;

		chosenColor_ = al_map_rgb_f(0.8,0.8,0.8);
		currentTilePage_ = 0;

		switch(id_)
		{
			case EnumDLL::STATES::TILEIMAGEPICKER:
				imageSetId_ = EnumDLL::IMAGESETS::TILEIMAGESET;
				break;
			case EnumDLL::STATES::TILECOLORPICKER:
				imageSetId_ = EnumDLL::IMAGESETS::TILECOLORSET;
				break;
		}

		for(int i = 0; i < imageLoader_->GetImageSetDictionary().size(); i ++)
		{
			if(imageLoader_->GetImageSetDictionary()[i]->GetImageSetId() == imageSetId_)
			{
				imageDictionaryId_ = i;
				imageDictionarySize_ = imageLoader_->GetImageSetDictionary()[i]->GetImageDictionary().size();
				break;
			}
			else if(imageLoader_->GetImageSetDictionary()[i]->GetImageSetId() == imageSetId_)
			{
				imageDictionaryId_ = i;
				imageDictionarySize_ = imageLoader_->GetImageSetDictionary()[i]->GetImageDictionary().size();
				break;
			}
		}


		FormatTiles();



		CreateTileWindow();

		
		fprintf(stderr,"An Overlay Created\n");

	}


	void EditorOverLay::Resize()
	{
		if(id_ == EnumDLL::STATES::TILECOLORPICKER)
		{
			CreateTilesColors();
			CreateTilePages();
		}
		else if(id_ == EnumDLL::STATES::TILEIMAGEPICKER)
		{
			CreateTileImagePicker();
			CreateTilePages();
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
		tilePickerWindow_->SetColor(al_map_rgb_f(0.8,0.8,0.8));
	}





	//Load list of all tiles into tile pages
	//also sizes display of these
	void EditorOverLay::FormatTiles()
	{
		if(id_ == EnumDLL::STATES::TILECOLORPICKER)
		{
			CreateTilesColors();
			CreateTilePages();
		}
		else if(id_ == EnumDLL::STATES::TILEIMAGEPICKER)
		{
			CreateTileImagePicker();
			CreateTilePages();
		}
		else if(id_ == EnumDLL::STATES::TILETYPEPICKER)
		{
			CreateTileTypes();
			CreateTilePages();
		}
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
			tilePages_.push_back(new TilePage(settings_));
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
						if(id_ == EnumDLL::STATES::TILETYPEPICKER)
						{
							if(GetSelectedTile()->GetTileType() == EnumDLL::TILETYPE::INVERTCOLLISIONCOLOR)
							{
								for(int i = 0; i < tiles_.size(); i++)
								{
									for(int j = 0; j < tiles_[i].size(); j++)
									{
										ALLEGRO_COLOR curColor = tiles_[i][j].GetColor();
										curColor.r = !curColor.r;
										curColor.g = !curColor.g;
										curColor.b = !curColor.b;

										tiles_[i][j].SetColor(curColor);
									}
								}
								settings_->SetColorCollisionInvert(!settings_->GetColorCollisionInvert());
								settings_->SaveSettings();
							}
						}
						return true;

					}
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
	void EditorOverLay::CreateTileImagePicker()
	{
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

		tiles_.resize(tileVectorWidthMax_);
		


		int i = 0;
		for(int j = 0; j < imageDictionarySize_; j++)
		{
			Tile* tempTile = new Tile();
			tempTile->SetTileType(EnumDLL::TILETYPE::SOLIDTILE);
			tempTile->SetObjectImageColor(imageLoader_->GetImageSetDictionary()[imageDictionaryId_]->GetImageDictionary()[j]);
			tempTile->SetWidth(1);
			tempTile->SetHeight(1);

			int posX = leftOffset+(j%tileVectorWidthMax_)*displacementOffset;
			int posY = topOffset + (i/tileVectorWidthMax_*displacementOffset)%(screenHeight);

			tempTile->SetCurrentPosition(posX,posY);

			tiles_[j%tileVectorWidthMax_].push_back(*tempTile);
			//go to next placement

			i++;

			//delete the copy of object
			delete tempTile;
		}



	}


	
	//Load list of all tiles into tile pages
	//also sizes display of these
	void EditorOverLay::CreateTilesColors()
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

		tiles_.resize(tileVectorWidthMax_);
		

		int i = 0;
		for(int j = 0; j < imageDictionarySize_; j++)
		{
			Tile* tempTile = new Tile();
			tempTile->SetTileType(EnumDLL::TILETYPE::SOLIDTILE);

			tempTile->SetObjectImageColor(imageLoader_->GetImageSetDictionary()[imageDictionaryId_]->GetImageDictionary()[j]);

			tempTile->SetWidth(1);
			tempTile->SetHeight(1);

			int posX = leftOffset+(j%tileVectorWidthMax_)*displacementOffset;
			int posY = topOffset + (i/tileVectorWidthMax_*displacementOffset)%(screenHeight);

			tempTile->SetCurrentPosition(posX,posY);

			tiles_[j%tileVectorWidthMax_].push_back(*tempTile);
			//go to next placement

			i++;

			//delete the copy of object
			delete tempTile;
		}

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


		bool invert = settings_->GetColorCollisionInvert();

		currentTile = new Tile();
		currentTile->SetColor(al_map_rgb_f(!invert,!invert,!invert));
		currentTile->SetTileType(EnumDLL::TILETYPE::EMPTYTILE);
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
		currentTile->SetColor(al_map_rgb_f(invert,invert,invert));
		currentTile->SetTileType(EnumDLL::TILETYPE::INVERTCOLLISIONCOLOR);
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
		currentTile->SetColor(al_map_rgb_f(!invert,!invert,!invert));
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
		currentTile->SetColor(al_map_rgb_f(!invert,!invert,!invert));
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
		currentTile->SetColor(al_map_rgb_f(!invert,!invert,!invert));
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



		currentTile->SetColor(al_map_rgb_f(!invert,!invert,!invert));
		currentTile->SetTileType(EnumDLL::TILETYPE::SOLIDTILE);
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