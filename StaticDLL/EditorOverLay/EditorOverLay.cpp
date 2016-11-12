#include "EditorOverLay.h"


namespace StaticDLL{

	EditorOverLay::EditorOverLay(Settings *settings, STATES id, AssetLibrary *assetLibrary)
	{
		id_ = id;

		settings_ = settings;
		assetLibrary_ = assetLibrary;

		widthMax_ = 9;
		tileVectorWidthMax_ = 4;

		height_ = settings_->GetDisplayHeight()*Constants::TileSize();

		overLayState_ = StaticDLL::OVERLAYSTATE::OVERLAYOPENED;
		overLayAction_ = StaticDLL::OVERLAYACTIONS::OVERLAYNONE;

		chosenColor_ = al_map_rgb_f(0.8,0.8,0.8);
		currentTilePage_ = 0;

		switch(id_)
		{
			case STATES::TILEIMAGEPICKER:
				imageSetId_ = StaticDLL::IMAGESETS::TILEIMAGESET;
				break;
			case STATES::TILECOLORPICKER:
				imageSetId_ = StaticDLL::IMAGESETS::TILECOLORSET;
				break;
			case STATES::OBJECTIMAGEPICKER:
				imageSetId_ = StaticDLL::IMAGESETS::OBJECTIMAGESET;
				break;
			case STATES::ENEMYPICKER:
				imageSetId_ = StaticDLL::IMAGESETS::ENEMYIMAGESET;
				break;
			case STATES::ITEMPICKER:
				imageSetId_ = StaticDLL::IMAGESETS::ITEMIMAGESET;
				break;
		}

		for(int i = 0; i < assetLibrary_->GetImageSetDictionary().size(); i ++)
		{
			if(assetLibrary_->GetImageSetDictionary()[i]->GetImageSetId() == imageSetId_)
			{
				imageDictionaryId_ = i;
				imageDictionarySize_ = assetLibrary_->GetImageSetDictionary()[i]->GetImageDictionary().size();
				break;
			}
		}


		FormatTiles();



		CreateTileWindow();

		

	}


	void EditorOverLay::Resize()
	{
		if(id_ == STATES::TILECOLORPICKER)
		{
			CreateTilesColors();
			CreateTilePages();
		}
		else if(id_ == STATES::TILEIMAGEPICKER)
		{
			CreateTileImagePicker();
			CreateTilePages();
		}
		else if(id_ == STATES::TILETYPEPICKER)
		{
			CreateTileTypes();
			CreateTilePages();
		}
		else if (id_ == STATES::OBJECTIMAGEPICKER)
		{
			CreateObjectImagePicker();
			CreateTilePages();
		}
		else if (id_ == STATES::ENEMYPICKER)
		{
			CreateEnemyImagePicker();
			CreateTilePages();
		}
		else if (id_ == STATES::ITEMPICKER)
		{
			CreateItemImagePicker();
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
		if(id_ == STATES::TILECOLORPICKER)
		{
			CreateTilesColors();
			CreateTilePages();
		}
		else if(id_ == STATES::TILEIMAGEPICKER)
		{
			CreateTileImagePicker();
			CreateTilePages();
		}
		else if(id_ == STATES::TILETYPEPICKER)
		{
			CreateTileTypes();
			CreateTilePages();
		}
		else if (id_ == STATES::OBJECTIMAGEPICKER)
		{
			CreateObjectImagePicker();
			CreateTilePages();
		}
		else if (id_ == STATES::ENEMYPICKER)
		{
			CreateEnemyImagePicker();
			CreateTilePages();
		}
		else if (id_ == STATES::ITEMPICKER)
		{
			CreateItemImagePicker();
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
		int pages = itemBaseList_[0].size()/(screenHeight/2);
		int extraPage = (itemBaseList_[0].size()%(screenHeight/2))>0?1:0;
		//There was a reason i added extra page but i cant remmeber but its working
		//Go through the tile pages adding in the tiles as a ref
		for(int i = 0; i < pages+extraPage; i++)
		{
			tilePages_.push_back(new TilePage(settings_));
			int newMin = (screenHeight/2*i) == 0 ? 0 : (screenHeight/2*i);
			int newMax = (screenHeight/2*i) + screenHeight/2;
			if(newMin > itemBaseList_[0].size())
			{
				newMin = itemBaseList_[0].size();
			}
			if(newMax > itemBaseList_[0].size())
			{
				newMax = itemBaseList_[0].size();
			}
			tilePages_[i]->SetTiles(newMin, newMax, tileVectorWidthMax_);
		}
	}


	
	//Draw all objects related to the overlay
	void EditorOverLay::Draw()
	{
		DrawTilePicker();
		DrawItemBaseList();
	}



	

	//Draw tile over lay background for pages
	//mmight be able to pass this to overlay controller and let it handle the picker window
	void EditorOverLay::DrawTilePicker()
	{
		tilePickerWindow_->DrawObject();
	}

	//Draw the tiles on the pages
	void EditorOverLay::DrawItemBaseList()
	{
		//draw collision boxes if page id is tiletype
		tilePages_[currentTilePage_]->DrawItemBaseList(itemBaseList_, (id_ == STATES::TILETYPEPICKER));
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
					if(tilePages_[currentTilePage_]->MouseActivity(itemBaseList_, mouseX, mouseY))
					{
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
		menuHeaderItem_->SetFont(al_load_font("arial.ttf", Constants::TileSize(), 0));
		menuHeaderItem_->SetColor(al_map_rgb_f(0,0,0));
		menuHeaderItem_->SetWidth(menuHeaderItem_->GetFontWidth());
		menuHeaderItem_->SetHeight(Constants::TileSize());
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
		itemBaseList_.resize(0);
		itemBaseList_.clear();

		itemBaseList_.resize(tileVectorWidthMax_);
		


		int i = 0;
		for(int j = 0; j < imageDictionarySize_; j++)
		{
			EditorItemBase* tempTile = new EditorItemBase();
			tempTile->SetTileType(TILETYPE::SOLIDTILE);
			tempTile->SetObjectImageColor(assetLibrary_->GetImageSetDictionary()[imageDictionaryId_]->GetImageDictionary()[j]);
			tempTile->SetWidth(1);
			tempTile->SetHeight(1);
			tempTile->SetImageSet(imageSetId_);


			int posX = leftOffset+(j%tileVectorWidthMax_)*displacementOffset;
			int posY = topOffset + (i/tileVectorWidthMax_*displacementOffset)%(screenHeight);

			tempTile->SetCurrentPosition(posX,posY);

			itemBaseList_[j%tileVectorWidthMax_].push_back(*tempTile);
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
		itemBaseList_.resize(0);
		itemBaseList_.clear();

		itemBaseList_.resize(tileVectorWidthMax_);
		

		int i = 0;
		for(int j = 0; j < imageDictionarySize_; j++)
		{
			EditorItemBase* tempTile = new EditorItemBase();
			tempTile->SetTileType(TILETYPE::SOLIDTILE);

			tempTile->SetObjectImageColor(assetLibrary_->GetImageSetDictionary()[imageDictionaryId_]->GetImageDictionary()[j]);

			tempTile->SetWidth(1);
			tempTile->SetHeight(1);

			int posX = leftOffset+(j%tileVectorWidthMax_)*displacementOffset;
			int posY = topOffset + (i/tileVectorWidthMax_*displacementOffset)%(screenHeight);

			tempTile->SetCurrentPosition(posX,posY);

			itemBaseList_[j%tileVectorWidthMax_].push_back(*tempTile);
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
		std::vector<EditorItemBase> objs;
		EditorItemBase* currentTile = new EditorItemBase();


		bool invert = settings_->GetColorCollisionInvert();


		currentTile = new EditorItemBase();
		currentTile->SetColor(al_map_rgb_f(!invert,!invert,!invert));
		currentTile->SetTileType(TILETYPE::EMPTYTILE);
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




		currentTile = new EditorItemBase();
		currentTile->SetColor(al_map_rgb_f(!invert,!invert,!invert));
		currentTile->SetTileType(TILETYPE::COLLISIONTOPTILE);
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




		currentTile = new EditorItemBase();
		currentTile->SetColor(al_map_rgb_f(!invert,!invert,!invert));
		currentTile->SetTileType(TILETYPE::COLLISIONLEFTTILE);
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




		currentTile = new EditorItemBase();
		currentTile->SetColor(al_map_rgb_f(!invert,!invert,!invert));
		currentTile->SetTileType(TILETYPE::COLLISIONRIGHTTILE);
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
		currentTile->SetTileType(TILETYPE::SOLIDTILE);
		currentTile->SetCurrentPosition(posX,posY);
		currentTile->SetWidth(1);
		currentTile->SetHeight(1);
		objs.push_back(*currentTile);

		
		itemBaseList_.resize(tileVectorWidthMax_);
		for(int i = 0; i < objs.size(); i++)
		{
			itemBaseList_[i%tileVectorWidthMax_].push_back(objs[i]);
		}
	}





	void EditorOverLay::CreateObjectImagePicker()
	{
		int topOffset = 2;
		int leftOffset = 1;
		int displacementOffset = 2;
		int screenHeight = settings_->GetDisplayHeight() - 2;
		//Displace counter for screen height if its not even
		if (screenHeight % 2 == 1)
		{
			screenHeight--;
		}

		//is this the best way to clean those objects?
		itemBaseList_.resize(0);
		itemBaseList_.clear();

		itemBaseList_.resize(tileVectorWidthMax_);



		int i = 0;
		for (int j = 0; j < imageDictionarySize_; j++)
		{
			EditorItemBase* tempTile = new EditorItemBase();
			tempTile->SetTileType(TILETYPE::SOLIDTILE);
			tempTile->SetObjectImageColor(assetLibrary_->GetImageSetDictionary()[imageDictionaryId_]->GetImageDictionary()[j]);
			tempTile->SetImageSet(imageSetId_);


			int posX = leftOffset + (j%tileVectorWidthMax_)*displacementOffset;
			int posY = topOffset + (i / tileVectorWidthMax_*displacementOffset) % (screenHeight);

			tempTile->SetCurrentPosition(posX, posY);

			itemBaseList_[j%tileVectorWidthMax_].push_back(*tempTile);
			//go to next placement

			i++;

			//delete the copy of object
			delete tempTile;
		}



	}





	void EditorOverLay::CreateEnemyImagePicker()
	{
		int topOffset = 2;
		int leftOffset = 1;
		int displacementOffset = 2;
		int screenHeight = settings_->GetDisplayHeight() - 2;
		//Displace counter for screen height if its not even
		if (screenHeight % 2 == 1)
		{
			screenHeight--;
		}

		//is this the best way to clean those objects?
		itemBaseList_.resize(0);
		itemBaseList_.clear();

		itemBaseList_.resize(tileVectorWidthMax_);



		int i = 0;
		for (int j = 0; j < imageDictionarySize_; j++)
		{
			EditorItemBase* tempTile = new EditorItemBase();
			tempTile->SetTileType(TILETYPE::SOLIDTILE);
			tempTile->SetObjectImageColor(assetLibrary_->GetImageSetDictionary()[imageDictionaryId_]->GetImageDictionary()[j]);
			tempTile->SetImageSet(imageSetId_);


			int posX = leftOffset + (j%tileVectorWidthMax_)*displacementOffset;
			int posY = topOffset + (i / tileVectorWidthMax_*displacementOffset) % (screenHeight);

			tempTile->SetCurrentPosition(posX, posY);

			itemBaseList_[j%tileVectorWidthMax_].push_back(*tempTile);
			//go to next placement

			i++;

			//delete the copy of object
			delete tempTile;
		}



	}






	void EditorOverLay::CreateItemImagePicker()
	{
		int topOffset = 2;
		int leftOffset = 1;
		int displacementOffset = 2;
		int screenHeight = settings_->GetDisplayHeight() - 2;
		//Displace counter for screen height if its not even
		if (screenHeight % 2 == 1)
		{
			screenHeight--;
		}

		//is this the best way to clean those objects?
		itemBaseList_.resize(0);
		itemBaseList_.clear();

		itemBaseList_.resize(tileVectorWidthMax_);



		int i = 0;
		for (int j = 0; j < imageDictionarySize_; j++)
		{
			EditorItemBase* tempTile = new EditorItemBase();
			tempTile->SetTileType(TILETYPE::SOLIDTILE);
			tempTile->SetObjectImageColor(assetLibrary_->GetImageSetDictionary()[imageDictionaryId_]->GetImageDictionary()[j]);
			tempTile->SetImageSet(imageSetId_);


			int posX = leftOffset + (j%tileVectorWidthMax_)*displacementOffset;
			int posY = topOffset + (i / tileVectorWidthMax_*displacementOffset) % (screenHeight);

			tempTile->SetCurrentPosition(posX, posY);

			itemBaseList_[j%tileVectorWidthMax_].push_back(*tempTile);
			//go to next placement

			i++;

			//delete the copy of object
			delete tempTile;
		}



	}


}