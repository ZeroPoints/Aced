#include "map.h"


namespace AcedSharedDLL {

	Map::Map(BaseSettings *settings, ALLEGRO_DISPLAY *display, AssetLibrary *assetLibrary)
	{
		assetLibrary_ = assetLibrary;
		settings_ = settings;
		display_ = display;
		font30_ = al_load_font("arial.ttf", Constants::TileSize(), 0);
		mapMoveXDelta_ = 0;
		mapMoveYDelta_ = 0;
		ResetMap();



	}




	Map::~Map() {

		for (Character* item : enemyList_)
		{
			delete item;
			item = nullptr;
		}

		for (Item* item : itemList_)
		{
			delete item;
			item = nullptr;
		}
		//fprintf(stderr, "A Map Destructed\n");

	}











	//-----------------------------------------------------------------------------------------------------

	//Gets



	bool Map::GetPlayerPlaced() {
		return playerplaced_;

	}
	double Map::GetMapYOffset() {
		return mapYoffset_;

	}
	double Map::GetMapXOffset() {
		return mapXoffset_;
	}
	int Map::GetOldMapXOffset() {
		return offSetBeforeRightClickDragX_;
	}
	int Map::GetOldMapYOffset() {
		return offSetBeforeRightClickDragY_;
	}
	int Map::GetMapWidth() {
		return width_;
	}
	int Map::GetMapHeight() {
		return height_;
	}
	int Map::GetPlayerStartX() {
		return playerStartX_;
	}
	int Map::GetPlayerStartY() {
		return playerStartY_;
	}
	std::vector<std::vector<Cell>> &Map::GetCellMap() {
		return cellMap_;
	}
	/*std::vector<ObjectBase> &Map::GetObjects() {
		return objects_;
	}*/


	double Map::GetMapMoveXDelta() {
		return mapMoveXDelta_;
	}
	double Map::GetMapMoveYDelta() {
		return mapMoveYDelta_;
	}


	std::vector<Character*> &Map::GetEnemyList() {
		return enemyList_;
	}

	std::vector<Item*> &Map::GetItemList() {
		return itemList_;
	}




	//-----------------------------------------------------------------------------------------------------

	//Sets

	void Map::SetMapSize(int newmapwidth, int newmapheight)
	{
		oldMapHeight_ = height_;
		oldMapWidth_ = width_;

		width_ = newmapwidth;
		height_ = newmapheight;

		cellMap_.resize(width_);//resize the first vector of vectors
							  //thenr esize each vector that is in them
		for (int i = 0; i < width_; i++)
		{
			cellMap_[i].resize(height_);
		}
	}

	void Map::SetPlayerStartX(int playerStartX)
	{
		playerStartX_ = playerStartX;
	}

	void Map::SetPlayerStartY(int playerStartY)
	{
		playerStartY_ = playerStartY;
	}

	void Map::SetPlayerPlaced(bool playerplaced)
	{
		playerplaced_ = playerplaced;
	}

	void Map::SetMapHeight(int newmapheight)
	{
		oldMapHeight_ = height_;
		height_ = newmapheight;

		for (int i = 0; i < width_; i++)
		{
			cellMap_[i].resize(height_);
		}

		int YGREATER = 0;
		int k = 0;
		if (height_ > oldMapHeight_)
		{
			k = oldMapHeight_;
			YGREATER = 1;
		}

		if (YGREATER == 1)//only do this stuff if new Y is greater then old y
		{
			for (int i = 0; i < width_; i++)
			{
				for (int j = k; j < height_; j++)
				{
					cellMap_[i][j].SetTileType(TILETYPE::EMPTYTILE);
					cellMap_[i][j].SetCurrentPosition(i, j);
				}
			}
		}
	}


	void Map::SetMapWidth(int newmapwidth)
	{
		oldMapWidth_ = width_;
		width_ = newmapwidth;
		cellMap_.resize(width_);
		int XGREATER = 0;
		int k = 0;
		if (width_ > oldMapWidth_)
		{
			k = oldMapWidth_;
			XGREATER = 1;
		}
		if (XGREATER == 1)//only do this stuff if new x is greater then old x
		{
			for (int i = k; i < width_; i++)
			{
				cellMap_[i].resize(height_);
			}
			for (int i = k; i < width_; i++)
			{
				for (int j = 0; j < height_; j++)
				{
					cellMap_[i][j].SetTileType(TILETYPE::EMPTYTILE);
					cellMap_[i][j].SetCurrentPosition(i, j);
				}
			}
		}
	}



	void Map::SetMapYOffset(double mapYoffset)
	{
		mapYoffset_ = mapYoffset;
	}

	void Map::SetMapXOffset(double mapXoffset)
	{
		mapXoffset_ = mapXoffset;
	}


	void Map::SetOldMapYOffset(int mapYoffset) {
		offSetBeforeRightClickDragY_ = mapYoffset;
	}
	void Map::SetOldMapXOffset(int mapXoffset) {
		offSetBeforeRightClickDragX_ = mapXoffset;
	}

	void Map::SetMapMoveXDelta(double val) {
		mapMoveXDelta_ = val;
	}
	void Map::SetMapMoveYDelta(double val) {
		mapMoveYDelta_ = val;
	}




	//-----------------------------------------------------------------------------------------------------

	//Draws

	void Map::DrawMap()
	{

		int i;
		int j;
		for (i = leftViewPoint_; i < rightViewPoint_; i++)
		{
			for (j = topViewPoint_; j < botViewPoint_; j++)
			{
				cellMap_[i][j].Draw(mapXoffset_, mapYoffset_, false/*settings_->GetColorCollisionInvert()*/);
			}
		}
		al_draw_rectangle(mapXoffset_, mapYoffset_, mapXoffset_ + width_*Constants::TileSize(), mapYoffset_ + height_*Constants::TileSize(), al_map_rgb_f(0, 0, 0), 1);




		for (int i = 0; i < enemyList_.size(); i++) {
			enemyList_[i]->DrawObjectRotate(mapXoffset_, mapYoffset_);

			/*char text[100];
			sprintf(text, "Player%d:x=%f:y=%f", i, enemyList_[i]->GetCurrentPositionX(), enemyList_[i]->GetCurrentPositionY());
			al_draw_text(font30_, al_map_rgb(0, 0, 0),
				0,
				20*(i+1), ALLEGRO_ALIGN_LEFT, text);*/
		}

		for (int i = 0; i < itemList_.size(); i++) {
			itemList_[i]->DrawObject(mapXoffset_, mapYoffset_);
		}
	}




	//-----------------------------------------------------------------------------------------------------

	//Misc

	void Map::Update()
	{
		//SetMapXOffset(GetMapXOffset() + GetMapMoveXDelta());
		//SetMapXOffset(GetMapXOffset() + GetMapMoveYDelta());
		SetMapMoveXDelta(0);
		SetMapMoveYDelta(0);



		int XRight;
		int YBot;
		XRight = cellMap_.size();
		YBot = cellMap_[0].size();
		int FinXLeft;
		int FinXRight;
		int FinYTop;
		int FinYBot;
		int tempXOffset = mapXoffset_ / Constants::TileSize();
		int tempYOffset = mapYoffset_ / Constants::TileSize();
		if (settings_->GetDisplayWidth() - tempXOffset < 0)
		{
			FinXRight = 0;
		}
		else if (XRight + tempXOffset > settings_->GetDisplayWidth())
		{
			FinXRight = settings_->GetDisplayWidth() - tempXOffset;
		}
		else if (XRight + tempXOffset <= 0)
		{
			FinXRight = 0;
		}
		else
		{
			FinXRight = XRight;
		}
		if (tempXOffset <= 0 && -tempXOffset < XRight)
		{
			FinXLeft = 0 - tempXOffset;
		}
		else
		{
			FinXLeft = 0;
		}
		if (settings_->GetDisplayHeight() - tempYOffset < 0)
		{
			FinYBot = 0;
		}
		else if (tempYOffset + YBot > settings_->GetDisplayHeight())
		{
			FinYBot = settings_->GetDisplayHeight() - tempYOffset;
		}
		else if (YBot + tempYOffset <= 0)
		{
			FinYBot = 0;
		}
		else
		{
			FinYBot = YBot;
		}
		if (tempYOffset <= 0 && -tempYOffset < YBot)
		{
			FinYTop = 0 - tempYOffset;
		}
		else
		{
			FinYTop = 0;
		}
		//Add an extra cube to draw if the map is over screen dimensions so it draws the last cube position.
		if (FinXLeft >= 0 && FinXRight >= settings_->GetDisplayWidth() && FinXRight < XRight)
		{
			FinXRight++;
		}
		//Add an extra cube to draw if the map is over screen dimensions so it draws the last cube position.
		if (FinYTop >= 0 && FinYBot >= settings_->GetDisplayHeight() && FinYBot < YBot)
		{
			FinYBot++;
		}
		rightViewPoint_ = FinXRight;
		leftViewPoint_ = FinXLeft;
		botViewPoint_ = FinYBot;
		topViewPoint_ = FinYTop;





		for (int i = 0; i < enemyList_.size(); i++) {
			enemyList_[i]->Update();
		}

		for (int i = 0; i < itemList_.size(); i++) {
			//itemList_[i]->Update();
		}
	}


	void Map::SaveMapDialog()
	{
		ALLEGRO_FILECHOOSER *saveDialog;
		saveDialog = al_create_native_file_dialog("..\\Maps\\", "Save Map", "*.*", ALLEGRO_FILECHOOSER_SAVE);
		al_show_native_file_dialog(display_, saveDialog);
		mapPath_ = al_create_path(al_get_native_file_dialog_path(saveDialog, 0));
		if (strcmp(al_get_path_extension(mapPath_), "") == 0)
		{
			al_set_path_extension(mapPath_, ".mapa");
		}
		SaveMap();
		al_destroy_native_file_dialog(saveDialog);
	}




	/*
	returns true or false if it saved----->do something with result to show user
	Saves the map in XML format
	hmmm using standard type members as attributes
	using complex objects members as nodes
	*/
	bool Map::SaveMap()
	{
		pugi::xml_document xmlDoc;
		pugi::xml_node xmlMap = xmlDoc.append_child("map");
		xmlMap.append_attribute("width").set_value(width_);
		xmlMap.append_attribute("height").set_value(height_);
		//objectify player soon
		xmlMap.append_attribute("playerplaced").set_value(playerplaced_);
		xmlMap.append_attribute("playerx").set_value(playerStartX_);
		xmlMap.append_attribute("playery").set_value(playerStartY_);


		if (enemyList_.size() > 0) {
			pugi::xml_node xmlenemyset = xmlMap.append_child("enemyspawn");
			for (int i = 0; i < enemyList_.size(); i++) {
				Character *currentEnemy = enemyList_[i];
				pugi::xml_node xmlcurrentEnemy = xmlenemyset.append_child("enemy");
				xmlcurrentEnemy.append_attribute("x").set_value(currentEnemy->GetCurrentPositionX());
				xmlcurrentEnemy.append_attribute("y").set_value(currentEnemy->GetCurrentPositionY());
				auto hasImage = currentEnemy->GetHasImage();
				xmlcurrentEnemy.append_attribute("hasImage").set_value(hasImage);
				if (hasImage)
				{
					pugi::xml_node xmlCurrentImage = xmlcurrentEnemy.append_child("image");
					xmlCurrentImage.append_attribute("id").set_value(currentEnemy->GetImageBundle()->GetId());
					xmlCurrentImage.append_attribute("imageSet").set_value((int)currentEnemy->GetImageSet());
				}
			}
		}

		if (itemList_.size() > 0) {
			pugi::xml_node xmlenemyset = xmlMap.append_child("itemspawn");
			for (int i = 0; i < itemList_.size(); i++) {
				Item *currentItem = itemList_[i];
				pugi::xml_node xmlcurrentEnemy = xmlenemyset.append_child("item");
				xmlcurrentEnemy.append_attribute("x").set_value(currentItem->GetPosX());
				xmlcurrentEnemy.append_attribute("y").set_value(currentItem->GetPosY());
				auto hasImage = currentItem->GetHasImage();
				xmlcurrentEnemy.append_attribute("hasImage").set_value(hasImage);
				if (hasImage)
				{
					pugi::xml_node xmlCurrentImage = xmlcurrentEnemy.append_child("image");
					xmlCurrentImage.append_attribute("id").set_value(currentItem->GetImageBundle()->GetId());
					xmlCurrentImage.append_attribute("imageSet").set_value((int)currentItem->GetImageSet());
				}
			}
		}



		pugi::xml_node xmlTileSet = xmlMap.append_child("tilevector");
		for (int i = 0; i < cellMap_.size(); i++)
		{
			for (int j = 0; j < cellMap_[i].size(); j++)
			{
				Cell *currentCell = &cellMap_[i][j];
				pugi::xml_node xmlcurrentCell = xmlTileSet.append_child("cell");

				xmlcurrentCell.append_attribute("x").set_value(currentCell->GetCurrentPositionX());
				xmlcurrentCell.append_attribute("y").set_value(currentCell->GetCurrentPositionY());
				xmlcurrentCell.append_attribute("tiletype").set_value((int)currentCell->GetTileType());

				if (currentCell->GetHasTile()) {
					//Store the TILES data in file
					pugi::xml_node xmlcurrentTile = xmlcurrentCell.append_child("tile");
					if (currentCell->GetTile()->GetHasColor()) {
						xmlcurrentTile.append_attribute("color_a").set_value(currentCell->GetTile()->GetColor().a);
						xmlcurrentTile.append_attribute("color_b").set_value(currentCell->GetTile()->GetColor().b);
						xmlcurrentTile.append_attribute("color_g").set_value(currentCell->GetTile()->GetColor().g);
						xmlcurrentTile.append_attribute("color_r").set_value(currentCell->GetTile()->GetColor().r);
					}
					auto hasImage = currentCell->GetTile()->GetHasImage();
					xmlcurrentTile.append_attribute("hasImage").set_value(hasImage);
					if (hasImage)
					{
						pugi::xml_node xmlCurrentImage = xmlcurrentTile.append_child("image");
						xmlCurrentImage.append_attribute("id").set_value(currentCell->GetTile()->GetImageBundle()->GetId());
						xmlCurrentImage.append_attribute("imageSet").set_value((int)currentCell->GetTile()->GetImageSet());
					}
				}

				if (currentCell->GetHasInteractiveObject()) {
					pugi::xml_node xmlcurrentInteractiveObject = xmlcurrentCell.append_child("interactiveobject");
					auto hasImage = currentCell->GetInteractiveObject()->GetHasImage();
					auto hasImageReference = currentCell->GetInteractiveObject()->GetHasImageReference();
					xmlcurrentInteractiveObject.append_attribute("hasImage").set_value(hasImage);
					xmlcurrentInteractiveObject.append_attribute("hasImageReference").set_value(hasImageReference);
					if (hasImage || hasImageReference)
					{
						pugi::xml_node xmlCurrentImage = xmlcurrentInteractiveObject.append_child("image");
						if (hasImage) {
							xmlCurrentImage.append_attribute("id").set_value(currentCell->GetInteractiveObject()->GetImageBundle()->GetId());
							xmlCurrentImage.append_attribute("imageSet").set_value((int)currentCell->GetInteractiveObject()->GetImageSet());
						}
						xmlCurrentImage.append_attribute("imageReferenceX").set_value(currentCell->GetInteractiveObject()->GetImageReferenceX());
						xmlCurrentImage.append_attribute("imageReferenceY").set_value(currentCell->GetInteractiveObject()->GetImageReferenceY());
					}
				}
			}
		}


		return xmlDoc.save_file(al_path_cstr(mapPath_, '/'));
	}



	void Map::LoadMapDialog(bool gamestart)
	{
		ALLEGRO_FILECHOOSER *loadDialog = NULL;
		loadDialog = al_create_native_file_dialog("..\\Maps\\", "Load Mapx file", "*.*", 0);
		al_show_native_file_dialog(display_, loadDialog);
		mapPath_ = al_create_path(al_get_native_file_dialog_path(loadDialog, 0));
		LoadMap(gamestart);
		//ADJUST offset if a player has been placed but since player placed is false somteimes set it to top left corner as players pos will be created at this point
		mapXoffset_ = width_*Constants::TileSize() <= settings_->GetScreenWidth() ? settings_->GetScreenWidth() / 2 - width_*Constants::TileSize() / 2 : 0;
		mapYoffset_ = height_*Constants::TileSize() <= settings_->GetScreenHeight() ? settings_->GetScreenHeight() / 2 - height_*Constants::TileSize() / 2 : 0;
		Update();
		al_destroy_native_file_dialog(loadDialog);
	}


	void Map::LoadMap(bool gamestart)
	{
		pugi::xml_document xmlDoc;
		pugi::xml_parse_result xmlParseResult = xmlDoc.load_file(al_path_cstr(mapPath_, '/'));
		//should check xmlParseResult
		pugi::xml_node xmlMap = xmlDoc.child("map");
		width_ = xmlMap.attribute("width").as_int();
		height_ = xmlMap.attribute("height").as_int();
		playerplaced_ = xmlMap.attribute("playerplaced").as_bool();
		playerStartY_ = xmlMap.attribute("playery").as_int();
		playerStartX_ = xmlMap.attribute("playerx").as_int();



		pugi::xml_node xmlenemyset = xmlMap.child("enemyspawn");
		for (pugi::xml_node_iterator xmlcurrentEnemy = xmlenemyset.children().begin(); xmlcurrentEnemy != xmlenemyset.children().end(); xmlcurrentEnemy++)
		{
			bool hasImage = false;

			auto enemy = new Character(settings_, width_, height_, &cellMap_);

			enemy->SetAIEnabled(gamestart);
			enemy->SetKeyRight(gamestart);


			enemyList_.push_back(enemy);


			//Cycle through attributes of this node
			for (pugi::xml_attribute_iterator xmlTileAttribute = xmlcurrentEnemy->attributes_begin(); xmlTileAttribute != xmlcurrentEnemy->attributes_end(); xmlTileAttribute++)
			{
				auto currentCellAttributeName = xmlTileAttribute->name();
				if (strcmp(currentCellAttributeName, "x") == 0)
				{
					enemy->SetCurrentPositionX(xmlTileAttribute->as_double());
				}
				else if (strcmp(currentCellAttributeName, "y") == 0)
				{
					enemy->SetCurrentPositionY(xmlTileAttribute->as_double());
				}
				else if (strcmp(currentCellAttributeName, "hasImage") == 0)
				{
					hasImage = xmlTileAttribute->as_bool();
				}
			}

			if (hasImage) {
				//go through the tiles actual nodes within this node
				for (pugi::xml_node_iterator xmlcurrentCellNode = xmlcurrentEnemy->children().begin(); xmlcurrentCellNode != xmlcurrentEnemy->children().end(); xmlcurrentCellNode++)
				{
					auto currentCellNodeName = xmlcurrentCellNode->name();
					//if no img property it will skip from settings its property
					if (strcmp(currentCellNodeName, "image") == 0)
					{
						auto imgId = xmlcurrentCellNode->attribute("id").as_int();
						auto imageSetId = xmlcurrentCellNode->attribute("imageSet").as_int();
						int indexOfImageSet = -1;
						for (int k = 0; k < assetLibrary_->GetImageSetDictionary().size(); k++)
						{
							if ((int)assetLibrary_->GetImageSetDictionary()[k]->GetImageSetId() == imageSetId)
							{
								indexOfImageSet = k;
							}
						}
						if (indexOfImageSet >= 0) {
							auto imageDictionary = assetLibrary_->GetImageSetDictionary()[indexOfImageSet]->GetImageBundleDictionary();
							for (int j = 0; j < imageDictionary.size(); j++)
							{
								if (imageDictionary[j]->GetId() == imgId)
								{
									enemy->SetImageBundle(imageDictionary[j]);
									enemy->SetImageSet(AcedSharedDLL::IMAGESETS(imageSetId));
									break;
								}
							}
						}
					}
				}
			}
		}



		pugi::xml_node xmlitemset = xmlMap.child("itemspawn");
		for (pugi::xml_node_iterator xmlcurrentItem = xmlitemset.children().begin(); xmlcurrentItem != xmlitemset.children().end(); xmlcurrentItem++)
		{
			bool hasImage = false;

			auto item = new Item();


			itemList_.push_back(item);


			//Cycle through attributes of this node
			for (pugi::xml_attribute_iterator xmlTileAttribute = xmlcurrentItem->attributes_begin(); xmlTileAttribute != xmlcurrentItem->attributes_end(); xmlTileAttribute++)
			{
				auto currentCellAttributeName = xmlTileAttribute->name();
				if (strcmp(currentCellAttributeName, "x") == 0)
				{
					item->SetPosX(xmlTileAttribute->as_double());
				}
				else if (strcmp(currentCellAttributeName, "y") == 0)
				{
					item->SetPosY(xmlTileAttribute->as_double());
				}
				else if (strcmp(currentCellAttributeName, "hasImage") == 0)
				{
					hasImage = xmlTileAttribute->as_bool();
				}
			}

			if (hasImage) {
				//go through the tiles actual nodes within this node
				for (pugi::xml_node_iterator xmlcurrentCellNode = xmlcurrentItem->children().begin(); xmlcurrentCellNode != xmlcurrentItem->children().end(); xmlcurrentCellNode++)
				{
					auto currentCellNodeName = xmlcurrentCellNode->name();
					//if no img property it will skip from settings its property
					if (strcmp(currentCellNodeName, "image") == 0)
					{
						auto imgId = xmlcurrentCellNode->attribute("id").as_int();
						auto imageSetId = xmlcurrentCellNode->attribute("imageSet").as_int();
						int indexOfImageSet = -1;
						for (int k = 0; k < assetLibrary_->GetImageSetDictionary().size(); k++)
						{
							if ((int)assetLibrary_->GetImageSetDictionary()[k]->GetImageSetId() == imageSetId)
							{
								indexOfImageSet = k;
							}
						}
						if (indexOfImageSet >= 0) {
							auto imageDictionary = assetLibrary_->GetImageSetDictionary()[indexOfImageSet]->GetImageBundleDictionary();
							for (int j = 0; j < imageDictionary.size(); j++)
							{
								if (imageDictionary[j]->GetId() == imgId)
								{
									item->SetImageBundle(imageDictionary[j]);
									item->SetImageSet(AcedSharedDLL::IMAGESETS(imageSetId));
									break;
								}
							}
						}
					}
				}
			}
		}










		//Start first node
		//Will probably make a node iterator later if the map has many objects in it
		pugi::xml_node xmlTileSet = xmlMap.child("tilevector");
		int i = 0;
		int j = 0;
		cellMap_.resize(0);
		cellMap_.clear();
		//is this the best way to clean those objects?
		cellMap_.resize(width_);
		for (i = 0; i < cellMap_.size(); i++)
		{
			cellMap_[i].resize(height_);
		}
		i = 0;
		for (pugi::xml_node_iterator xmlcurrentCell = xmlTileSet.children().begin();
			xmlcurrentCell != xmlTileSet.children().end();
			xmlcurrentCell++)
		{
			Cell* currentCell = &cellMap_[i][j];


			for (pugi::xml_attribute_iterator xmlCellAttribute = xmlcurrentCell->attributes_begin();
				xmlCellAttribute != xmlcurrentCell->attributes_end();
				xmlCellAttribute++)
			{
				auto currentCellAttributeName = xmlCellAttribute->name();
				if (strcmp(currentCellAttributeName, "x") == 0)
				{
					currentCell->SetCurrentPositionX(xmlCellAttribute->as_float());
				}
				else if (strcmp(currentCellAttributeName, "y") == 0)
				{
					currentCell->SetCurrentPositionY(xmlCellAttribute->as_float());
				}
				else if (strcmp(currentCellAttributeName, "tiletype") == 0)
				{
					currentCell->SetTileType(TILETYPE(xmlCellAttribute->as_int()));
				}
			}





			for (pugi::xml_node_iterator xmlcurrentCellInnerNode = xmlcurrentCell->children().begin();
				xmlcurrentCellInnerNode != xmlcurrentCell->children().end();
				xmlcurrentCellInnerNode++)
			{
				auto currentCellNodeName = xmlcurrentCellInnerNode->name();
				//Build tile object from properties
				if (strcmp(currentCellNodeName, "tile") == 0) {
					Tile* currentTile = new Tile();
					bool hasImage = false;
					//Cycle through attributes of this node
					for (pugi::xml_attribute_iterator xmlTileAttribute = xmlcurrentCellInnerNode->attributes_begin();
						xmlTileAttribute != xmlcurrentCellInnerNode->attributes_end();
						xmlTileAttribute++)
					{
						auto currentTileAttributeName = xmlTileAttribute->name();
						if (strcmp(currentTileAttributeName, "color_a") == 0)
						{
							currentTile->SetColorA(xmlTileAttribute->as_float());
						}
						else if (strcmp(currentTileAttributeName, "color_b") == 0)
						{
							currentTile->SetColorB(xmlTileAttribute->as_float());
						}
						else if (strcmp(currentTileAttributeName, "color_g") == 0)
						{
							currentTile->SetColorG(xmlTileAttribute->as_float());
						}
						else if (strcmp(currentTileAttributeName, "color_r") == 0)
						{
							currentTile->SetColorR(xmlTileAttribute->as_float());
						}
						else if (strcmp(currentTileAttributeName, "hasImage") == 0)
						{
							hasImage = xmlTileAttribute->as_bool();
						}
					}
					if (hasImage) {
						//go through the tiles actual nodes within this node
						for (pugi::xml_node_iterator xmlcurrentTileInnerNode = xmlcurrentCellInnerNode->children().begin();
							xmlcurrentTileInnerNode != xmlcurrentCellInnerNode->children().end();
							xmlcurrentTileInnerNode++)
						{
							auto currentTileNodeName = xmlcurrentTileInnerNode->name();
							//if no img property it will skip from settings its property
							if (strcmp(currentTileNodeName, "image") == 0)
							{
								//Grab img set id and img id and cycle through the imageset dictionary for selected imageset
								//And grab the selected img and set tiles img
								//turn into a funciton
								auto imgId = xmlcurrentTileInnerNode->attribute("id").as_int();
								auto imageSetId = xmlcurrentTileInnerNode->attribute("imageSet").as_int();
								int indexOfImageSet = -1;
								for (int k = 0; k < assetLibrary_->GetImageSetDictionary().size(); k++)
								{
									if ((int)assetLibrary_->GetImageSetDictionary()[k]->GetImageSetId() == imageSetId)
									{
										indexOfImageSet = k;
									}
								}
								if (indexOfImageSet >= 0) {
									auto imageDictionary = assetLibrary_->GetImageSetDictionary()[indexOfImageSet]->GetImageBundleDictionary();
									for (int j = 0; j < imageDictionary.size(); j++)
									{
										if (imageDictionary[j]->GetId() == imgId)
										{

											currentTile->SetImageBundle(imageDictionary[j]);
											currentTile->SetImageSet(AcedSharedDLL::IMAGESETS(imageSetId));
											break;
										}
									}
								}
							}
						}
					}
					currentCell->SetTile(currentTile);
				}


				else if (strcmp(currentCellNodeName, "interactiveobject") == 0) {
					InteractiveObject* currentInteractiveObject = new InteractiveObject();
					bool hasImage = false;
					bool hasImageReference = false;

					//Cycle through attributes of this node
					for (pugi::xml_attribute_iterator xmlInteractiveObjectAttribute = xmlcurrentCellInnerNode->attributes_begin();
						xmlInteractiveObjectAttribute != xmlcurrentCellInnerNode->attributes_end();
						xmlInteractiveObjectAttribute++)
					{
						auto currentInteractiveObjectAttributeName = xmlInteractiveObjectAttribute->name();
						if (strcmp(currentInteractiveObjectAttributeName, "hasImage") == 0)
						{
							hasImage = xmlInteractiveObjectAttribute->as_bool();
						}
						else if (strcmp(currentInteractiveObjectAttributeName, "hasImageReference") == 0)
						{
							hasImageReference = xmlInteractiveObjectAttribute->as_bool();
						}
					}
					if (hasImage || hasImageReference) {
						for (pugi::xml_node_iterator xmlcurrentInteractiveObjectInnerNode = xmlcurrentCellInnerNode->children().begin();
							xmlcurrentInteractiveObjectInnerNode != xmlcurrentCellInnerNode->children().end();
							xmlcurrentInteractiveObjectInnerNode++)
						{
							auto currentInteractiveObjectNodeName = xmlcurrentInteractiveObjectInnerNode->name();
							if (strcmp(currentInteractiveObjectNodeName, "image") == 0)
							{
								auto imgId = xmlcurrentInteractiveObjectInnerNode->attribute("id").as_int();
								auto imageSetId = xmlcurrentInteractiveObjectInnerNode->attribute("imageSet").as_int();
								auto imageReferenceX = xmlcurrentInteractiveObjectInnerNode->attribute("imageReferenceX").as_int();
								auto imageReferenceY = xmlcurrentInteractiveObjectInnerNode->attribute("imageReferenceY").as_int();

								int indexOfImageSet = -1;
								for (int k = 0; k < assetLibrary_->GetImageSetDictionary().size(); k++)
								{
									if ((int)assetLibrary_->GetImageSetDictionary()[k]->GetImageSetId() == imageSetId)
									{
										indexOfImageSet = k;
									}
								}
								if (indexOfImageSet >= 0) {
									auto imageDictionary = assetLibrary_->GetImageSetDictionary()[indexOfImageSet]->GetImageBundleDictionary();
									for (int j = 0; j < imageDictionary.size(); j++)
									{
										if (imageDictionary[j]->GetId() == imgId)
										{
											currentInteractiveObject->SetImageBundle(imageDictionary[j]);
											currentInteractiveObject->SetHasImageReference(hasImageReference);
											currentInteractiveObject->SetImageReferenceX(imageReferenceX);
											currentInteractiveObject->SetImageReferenceY(imageReferenceY);
											currentInteractiveObject->SetImageSet(AcedSharedDLL::IMAGESETS(imageSetId));
											break;
										}
									}
								}
							}
						}
					}
					currentCell->SetInteractiveObject(currentInteractiveObject);
					currentCell->SetInteractiveObjectReference(hasImageReference);
				}
			}
			//if we at the end of current row of vector of tiles we go to the next vector of vectors
			j++;
			if (j % height_ == 0)
			{
				j = 0;
				i++;
			}
		}
	}



	void Map::ResetMap()
	{

		offSetBeforeRightClickDragY_ = 0;
		offSetBeforeRightClickDragX_ = 0;
		CreateCellMap(10, 10);
		for (int i = 0; i < width_; i++)
		{
			for (int j = 0; j < height_; j++)
			{
				cellMap_[i][j].SetTileType(TILETYPE::EMPTYTILE);
				cellMap_[i][j].SetCurrentPosition(i, j);
			}
		}


		while (enemyList_.size() > 0) {
			delete enemyList_[0];
			enemyList_.erase(enemyList_.begin() + 0);
		}

		while (itemList_.size() > 0) {
			delete itemList_[0];
			itemList_.erase(itemList_.begin() + 0);
		}


		mapXoffset_ = settings_->GetScreenWidth() / 2 - width_*Constants::TileSize() / 2;
		mapYoffset_ = settings_->GetScreenHeight() / 2 - height_*Constants::TileSize() / 2;

		Update();
	}


	void Map::CreateCellMap(int newmapwidth, int newmapheight)
	{
		height_ = newmapheight;
		width_ = newmapwidth;
		std::vector<std::vector<Cell>> cells(newmapwidth, std::vector<Cell>(newmapheight));
		cellMap_ = cells;
	}






	void Map::AddEnemyToMap(EditorItemBase *item, int tileXPos, int tileYPos) {


		auto enemy = new Character(settings_, item->GetWidth(), item->GetHeight(), &cellMap_);
		//enemy->SetGravityY(0);
		enemy->SetCurrentPositionX(tileXPos);
		enemy->SetCurrentPositionY(tileYPos);
		enemy->SetImageBundle(item->GetImageBundle());
		enemy->SetImageSet(item->GetImageSet());
		//enemy->SetMoveSpeed(0);
		//enemy->SetMoveSpeedDelta(0);
		//enemy->SetVelocityY(0);
		enemy->SetAIEnabled(false);

		enemyList_.push_back(enemy);

	}



	void Map::AddItemToMap(EditorItemBase *item, int tileXPos, int tileYPos) {


		auto thing = new Item();

		thing->SetPosX(tileXPos);
		thing->SetPosY(tileYPos);
		thing->SetImageBundle(item->GetImageBundle());
		thing->SetImageSet(item->GetImageSet());

		itemList_.push_back(thing);

	}




	void Map::RemoveEnemyFromMap(int tileXPos, int tileYPos) {

		for (auto i = 0; i < enemyList_.size(); i++) {
			if (enemyList_[i]->GetCurrentPositionX() == tileXPos && enemyList_[i]->GetCurrentPositionY() == tileYPos) {
				//Go through vector find the one then remove
				delete enemyList_[i];
				enemyList_.erase(enemyList_.begin() + i);
			}
		}
	}



	void Map::RemoveItemFromMap(int tileXPos, int tileYPos) {

		for (auto i = 0; i < itemList_.size(); i++) {
			if (itemList_[i]->GetPosX() == tileXPos && itemList_[i]->GetPosY() == tileYPos) {
				//Go through vector find the one then remove
				delete itemList_[i];
				itemList_.erase(itemList_.begin() + i);
			}
		}
	}





	bool Map::EnemyAlreadyExistsAtXY(int tileXPos, int tileYPos) {

		for (auto i = 0; i < enemyList_.size(); i++) {
			if (enemyList_[i]->GetCurrentPositionX() == tileXPos && enemyList_[i]->GetCurrentPositionY() == tileYPos) {
				return true;
			}
		}
		return false;
	}



	bool Map::ItemAlreadyExistsAtXY(int tileXPos, int tileYPos) {

		for (auto i = 0; i < itemList_.size(); i++) {
			if (itemList_[i]->GetPosX() == tileXPos && itemList_[i]->GetPosY() == tileYPos) {
				return true;
			}
		}
		return false;
	}


	Item* Map::ItemCollisionCheckAtXY(double playerX, double playerY, double width, double height) {
		for (auto i = 0; i < itemList_.size(); i++) {
			auto item = itemList_[i];
			if (playerX < item->GetPosX() + item->GetImageBundle()->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetWidth() 
				&& playerX + width > item->GetPosX() &&
				playerY < item->GetPosY() + item->GetImageBundle()->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetHeight()
				&& playerY + height > item->GetPosY()
				) {
				itemList_.erase(itemList_.begin() + i);
				return item;
			}
		}
		return nullptr;
	}





	//-----------------------------------------------------------------------------------------------------

	//Testing

	/*void Map::AddObjectToMap(ObjectBase obj) {



		objects_.push_back(obj);


	}*/

}
