#include "map.h"


namespace StaticDLL{

	Map::Map(Settings *settings, ALLEGRO_DISPLAY *display, ImageLoader *imageLoader)
	{
		imageLoader_ = imageLoader;
		settings_ = settings;
		display_ = display;
		font30_ = al_load_font("arial.ttf", 20, 0);
		ResetMap();
	}

	void Map::ResetMap()
	{
		
		offSetBeforeRightClickDragY_ = 0;
		offSetBeforeRightClickDragX_ = 0;
		CreateTiles(10,10);
		for(int i = 0; i < width_; i++)
		{
			for(int j = 0; j < height_; j++)
			{
				tiles_[i][j].SetColor(al_map_rgb_f(0.5,0.5,0.5));//sets all tiles to grey
				tiles_[i][j].SetTileType(EnumDLL::TILETYPE::EMPTYTILE);
				tiles_[i][j].SetCurrentPosition(i,j);
				tiles_[i][j].SetWidth(1);
				tiles_[i][j].SetHeight(1);
			}
		}

		
		mapXoffset_ = settings_->GetScreenWidth()/2-width_*Constants::TileSize/2;
		mapYoffset_ = settings_->GetScreenHeight()/2-height_*Constants::TileSize/2;

		PreCalc();
	}


	//Init of tiles vector. Must be called.
	void Map::CreateTiles(int newmapwidth, int newmapheight)
	{
		height_ = newmapheight;
		width_ = newmapwidth;
		std::vector<std::vector<Tile>> tiles(newmapwidth,std::vector<Tile>(newmapheight));
		tiles_ = tiles;
	}



	void Map::SetMapSize(int newmapwidth, int newmapheight)
	{
		oldMapHeight_ = height_;
		oldMapWidth_ = width_;

		width_ = newmapwidth;
		height_ = newmapheight;

		tiles_.resize(width_);//resize the first vector of vectors
		//thenr esize each vector that is in them
		for(int i = 0; i < width_; i++)
		{
			tiles_[i].resize(height_);
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

		for(int i = 0; i < width_; i++)
		{
			tiles_[i].resize(height_);	
		}

		int YGREATER = 0;
		int k = 0;
		if(height_ > oldMapHeight_)
		{		
			k = oldMapHeight_;
			YGREATER = 1;
		}

		if(YGREATER == 1)//only do this stuff if new Y is greater then old y
		{
			for (int i = 0; i < width_; i++)
			{
				for (int j = k; j < height_; j++)
				{
					tiles_[i][j].SetColor(al_map_rgb_f(0.5,0.5,0.5));//sets all tiles to grey
					tiles_[i][j].SetTileType(EnumDLL::TILETYPE::EMPTYTILE);
					tiles_[i][j].SetCurrentPosition(i,j);
					tiles_[i][j].SetWidth(1);
					tiles_[i][j].SetHeight(1);
				}
			}
		}
	}


	void Map::SetMapWidth(int newmapwidth)
	{
		oldMapWidth_ = width_;	
		width_ = newmapwidth;
		tiles_.resize(width_);
		int XGREATER = 0;
		int k = 0;
		if(width_ > oldMapWidth_)
		{
			k = oldMapWidth_;
			XGREATER = 1;
		}
		if(XGREATER == 1)//only do this stuff if new x is greater then old x
		{
			for(int i = k; i < width_; i++)
			{
				tiles_[i].resize(height_);	
			}
			for (int i = k; i < width_; i++)
			{
				for (int j = 0; j < height_; j++)
				{
					tiles_[i][j].SetColor(al_map_rgb_f(0.5,0.5,0.5));//sets all tiles to grey
					tiles_[i][j].SetTileType(EnumDLL::TILETYPE::EMPTYTILE);
					tiles_[i][j].SetCurrentPosition(i,j);
					tiles_[i][j].SetWidth(1);
					tiles_[i][j].SetHeight(1);
				}
			}
		}	
	}


	


	void Map::DrawMap()
	{
		int i;
		int j;
		for(i = leftViewPoint_; i < rightViewPoint_; i++)
		{
			for(j = topViewPoint_; j < botViewPoint_; j++)
			{				
				tiles_[i][j].DrawObject(mapXoffset_, mapYoffset_);	
				tiles_[i][j].DrawObjectType(mapXoffset_, mapYoffset_);	
			}
		}



		//Tile rectangle overlay may be useful for tile map later.
		/*for(i = leftViewPoint_; i < rightViewPoint_; i++)
		{
			for(j = topViewPoint_; j < botViewPoint_; j++)
			{				
				tiles_[i][j].DrawRectangleMapObject(mapXoffset_, mapYoffset_);	
			}
		}*/

	}




	//This Pre Calc function will calculate the drawing range for the maps boundaries. This should be run in update method
	void Map::PreCalc()
	{
			
		int XRight;
		int YBot;
		XRight = tiles_.size();
		YBot = tiles_[0].size();
		int FinXLeft;
		int FinXRight;
		int FinYTop;
		int FinYBot;

		int tempXOffset = mapXoffset_/Constants::TileSize;
		int tempYOffset = mapYoffset_/Constants::TileSize;




		if(settings_->GetDisplayWidth() - tempXOffset < 0)
		{
			FinXRight = 0;
		}
		else if(XRight + tempXOffset > settings_->GetDisplayWidth())
		{
			FinXRight = settings_->GetDisplayWidth() - tempXOffset;
		}
		else if(XRight + tempXOffset <= 0)
		{
			FinXRight = 0;
		}
		else
		{
			FinXRight = XRight;
		}




		if(tempXOffset <= 0 && -tempXOffset < XRight)
		{
			FinXLeft = 0 - tempXOffset;
		}
		else
		{
			FinXLeft = 0;
		}




	
		if(settings_->GetDisplayHeight() - tempYOffset < 0)
		{
			FinYBot = 0;
		}
		else if(tempYOffset + YBot > settings_->GetDisplayHeight())
		{
			FinYBot = settings_->GetDisplayHeight()  - tempYOffset;
		}
		else if(YBot + tempYOffset <= 0)
		{
			FinYBot = 0;
		}
		else
		{
			FinYBot = YBot;
		}



		if(tempYOffset <= 0 && -tempYOffset < YBot)
		{		
			FinYTop = 0 - tempYOffset;
		}
		else
		{
			FinYTop = 0;		
		}

		



		//Add an extra cube to draw if the map is over screen dimensions so it draws the last cube position.
		if(FinXLeft >= 0 && FinXRight >= settings_->GetDisplayWidth() && FinXRight < XRight)
		{
			FinXRight++;
		}
		//Add an extra cube to draw if the map is over screen dimensions so it draws the last cube position.
		if(FinYTop >= 0 && FinYBot >= settings_->GetDisplayHeight() && FinYBot < YBot)
		{
			FinYBot++;
		}


		rightViewPoint_ = FinXRight;
		leftViewPoint_ = FinXLeft;
		botViewPoint_ = FinYBot;
		topViewPoint_ = FinYTop;
	}


	void Map::SetMapYOffset(double mapYoffset)
	{
		mapYoffset_ = mapYoffset;
	}

	void Map::SetMapXOffset(double mapXoffset)
	{
		mapXoffset_ = mapXoffset;
	}





	void Map::SaveMapDialog()
	{
		ALLEGRO_FILECHOOSER *saveDialog;
		saveDialog = al_create_native_file_dialog("..\\Maps\\", "Save Map", "*.*", ALLEGRO_FILECHOOSER_SAVE);
		al_show_native_file_dialog(display_, saveDialog);
		mapPath_ = al_create_path(al_get_native_file_dialog_path(saveDialog,0));
		if(strcmp(al_get_path_extension(mapPath_),"") == 0)
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
		<map attrib1="" attrib2="" attrib3="">
			<tileset>
				<tile attribute1="blah" />
				<tile attribute1="blah" />
				<tile attribute1="blah" />
				<tile attribute1="blah" />
			</tileset>

		</map>
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
		pugi::xml_node xmlTileSet = xmlMap.append_child("tilevector");
		for(int i = 0; i < tiles_.size(); i++)
		{
			for(int j = 0; j < tiles_[i].size(); j++)
			{
				Tile *currentTile = &tiles_[i][j];
				pugi::xml_node xmlCurrentTile = xmlTileSet.append_child("tile");
				xmlCurrentTile.append_attribute("tiletype").set_value(currentTile->GetTileType());
				xmlCurrentTile.append_attribute("x").set_value(currentTile->GetCurrentPositionX());
				xmlCurrentTile.append_attribute("y").set_value(currentTile->GetCurrentPositionY());
				xmlCurrentTile.append_attribute("clickable").set_value(currentTile->GetClickable());
				xmlCurrentTile.append_attribute("color_a").set_value(currentTile->GetColor().a);
				xmlCurrentTile.append_attribute("color_b").set_value(currentTile->GetColor().b);
				xmlCurrentTile.append_attribute("color_g").set_value(currentTile->GetColor().g);
				xmlCurrentTile.append_attribute("color_r").set_value(currentTile->GetColor().r);
				xmlCurrentTile.append_attribute("height").set_value(currentTile->GetHeight());
				xmlCurrentTile.append_attribute("width").set_value(currentTile->GetWidth());
				xmlCurrentTile.append_attribute("movespeed").set_value(currentTile->GetMoveSpeed());


				if(currentTile->GetHasImage())
				{
					pugi::xml_node xmlCurrentImage = xmlCurrentTile.append_child("image");
					xmlCurrentImage.append_attribute("id").set_value(currentTile->GetObjectImage()->GetId());
				}
			}
		}
		return xmlDoc.save_file(al_path_cstr(mapPath_,'/'));
	}



	void Map::LoadMapDialog()
	{
		ALLEGRO_FILECHOOSER *loadDialog = NULL;
		loadDialog = al_create_native_file_dialog("..\\Maps\\", "Load Mapx file","*.*",0);	
		al_show_native_file_dialog(display_, loadDialog);
		mapPath_ = al_create_path(al_get_native_file_dialog_path(loadDialog, 0));
		LoadMap();


		//ADJUST offset if a player has been placed but since player placed is false somteimes set it to top left corner as players pos will be created at this point
		mapXoffset_ = width_*Constants::TileSize <= settings_->GetScreenWidth() ? settings_->GetScreenWidth()/2-width_*Constants::TileSize/2 : 0;
		mapYoffset_ = height_*Constants::TileSize <= settings_->GetScreenHeight() ? settings_->GetScreenHeight()/2-height_*Constants::TileSize/2 : 0;

		PreCalc();


		al_destroy_native_file_dialog(loadDialog);

	}


	void Map::LoadMap()
	{
		pugi::xml_document xmlDoc;
		pugi::xml_parse_result xmlParseResult = xmlDoc.load_file(al_path_cstr(mapPath_,'/'));
		//should check xmlParseResult
		pugi::xml_node xmlMap = xmlDoc.child("map");
		width_ = xmlMap.attribute("width").as_int();
		height_ = xmlMap.attribute("height").as_int();
		playerplaced_ = xmlMap.attribute("playerplaced").as_bool();
		playerStartY_ = xmlMap.attribute("playery").as_int();
		playerStartX_ = xmlMap.attribute("playerx").as_int();
		//Start first node
		//Will probably make a node iterator later if the map has many objects in it
		pugi::xml_node xmlTileSet = xmlMap.child("tilevector");
		int i = 0;
		int j = 0;
		tiles_.resize(0);
		tiles_.clear();
		//is this the best way to clean those objects?
		tiles_.resize(width_);
		for(i = 0; i < tiles_.size(); i++)
		{
			tiles_[i].resize(height_);
		}
		i = 0;
		for (pugi::xml_node_iterator xmlCurrentTile = xmlTileSet.children().begin(); xmlCurrentTile != xmlTileSet.children().end(); xmlCurrentTile++)
		{
			Tile* currentTile = &tiles_[i][j];
			for(pugi::xml_attribute_iterator xmlTileAttribute = xmlCurrentTile->attributes_begin(); xmlTileAttribute != xmlCurrentTile->attributes_end(); xmlTileAttribute++)
			{
				auto currentTileAttributeName = xmlTileAttribute->name();
				if(strcmp(currentTileAttributeName,"tiletype") == 0)
				{
					currentTile->SetTileType(EnumDLL::TILETYPE(xmlTileAttribute->as_int()));
				}
				else if(strcmp(currentTileAttributeName,"x") == 0)
				{
					currentTile->SetCurrentPositionX(xmlTileAttribute->as_double());
				}
				else if(strcmp(currentTileAttributeName,"y") == 0)
				{
					currentTile->SetCurrentPositionY(xmlTileAttribute->as_double());
				}
				else if(strcmp(currentTileAttributeName,"clickable") == 0)
				{
					currentTile->SetClickable(xmlTileAttribute->as_bool());
				}
				else if(strcmp(currentTileAttributeName,"color_a") == 0)
				{
					currentTile->SetColorA(xmlTileAttribute->as_float());
				}
				else if(strcmp(currentTileAttributeName,"color_b") == 0)
				{
					currentTile->SetColorB(xmlTileAttribute->as_float());
				}
				else if(strcmp(currentTileAttributeName,"color_g") == 0)
				{
					currentTile->SetColorG(xmlTileAttribute->as_float());
				}
				else if(strcmp(currentTileAttributeName,"color_r") == 0)
				{
					currentTile->SetColorR(xmlTileAttribute->as_float());
				}
				else if(strcmp(currentTileAttributeName,"height") == 0)
				{
					currentTile->SetHeight(xmlTileAttribute->as_double());
				}
				else if(strcmp(currentTileAttributeName,"width") == 0)
				{
					currentTile->SetWidth(xmlTileAttribute->as_double());
				}
				else if(strcmp(currentTileAttributeName,"movespeed") == 0)
				{
					currentTile->SetMoveSpeed(xmlTileAttribute->as_double());
				}
			}


			//go through the tiles actual nodes for images
			for (pugi::xml_node_iterator xmlCurrentTileNode = xmlCurrentTile->children().begin(); xmlCurrentTileNode != xmlCurrentTile->children().end(); xmlCurrentTileNode++)
			{
				auto currentTileNodeName = xmlCurrentTileNode->name();
				//if no img property it will skip from settings its property
				if(strcmp(currentTileNodeName,"image") == 0)
				{
					auto imgId = xmlCurrentTileNode->attribute("id").as_int();
					for(int k = 0; k < imageLoader_->GetImageSetDictionary().size(); k++)
					{
						if(imageLoader_->GetImageSetDictionary()[k]->GetImageSetId() == EnumDLL::IMAGESETS::TILEIMAGESET)
						{
							for(int j = 0; j < imageLoader_->GetImageSetDictionary()[k]->GetImageDictionary().size(); j++)
							{
								if(imageLoader_->GetImageSetDictionary()[k]->GetImageDictionary()[j]->GetId() == imgId)
								{
									currentTile->SetObjectImage(imageLoader_->GetImageSetDictionary()[k]->GetImageDictionary()[j]);
								}
							}
						}
					}
				}
			}
			
			
			//if we at the end of current row of vector of tiles we go to the next vector of vectors
			j++;
			if(j % height_ == 0)
			{
				j = 0;
				i++;
			}
		}
	}





}
