#include "map.h"


namespace StaticDLL{

	Map::Map()
	{
		mapXoffset_ = 5;
		mapYoffset_ = 5;
		offSetBeforeRightClickDragY_ = 0;
		offSetBeforeRightClickDragX_ = 0;
		CreateTiles(10,10);
		displayHeight_ = 30;
		displayWidth_ = 40;
		for(int i = 0; i < width_; i++)
		{
			for(int j = 0; j < height_; j++)
			{
				tiles_[i][j].SetColor(al_map_rgb_f(0.5,0.5,0.5));//sets all tiles to grey
				tiles_[i][j].SetTileType(EnumDLL::TILETYPE::EMPTY);
				tiles_[i][j].SetCurrentPosition(i,j);
				tiles_[i][j].SetWidth(1);
				tiles_[i][j].SetHeight(1);
			}
		}

		font30_ = al_load_font("arial.ttf", 20, 0);
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
					tiles_[i][j].SetTileType(EnumDLL::TILETYPE::EMPTY);
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
					tiles_[i][j].SetTileType(EnumDLL::TILETYPE::EMPTY);
					tiles_[i][j].SetCurrentPosition(i,j);
					tiles_[i][j].SetWidth(1);
					tiles_[i][j].SetHeight(1);
				}
			}
		}	
	}

	void Map::SetDisplayHeight(int displayheight)
	{
		displayHeight_ = displayheight;
	}
	void Map::SetDisplayWidth(int displaywidth)
	{
		displayWidth_ = displaywidth;
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
			}
		}



		//Tile rectangle overlay may be useful for tile map later.
		/*for(i = leftViewPoint_; i < rightViewPoint_; i++)
		{
			for(j = topViewPoint_; j < botViewPoint_; j++)
			{				
				tiles_[i][j].DrawTriangleMapObject(mapXoffset_, mapYoffset_);	
			}
		}*/



		//debugging draw ammount
		//al_draw_textf(font30_, al_map_rgb(255,255,255), 0, 20, ALLEGRO_ALIGN_LEFT, "%i" , rightViewPoint_);
		//al_draw_textf(font30_, al_map_rgb(255,255,255), 0, 40, ALLEGRO_ALIGN_LEFT, "%i" , botViewPoint_);
		//al_draw_textf(font30_, al_map_rgb(255,255,255), 0, 60, ALLEGRO_ALIGN_LEFT, "%i" , leftViewPoint_);
		//al_draw_textf(font30_, al_map_rgb(255,255,255), 0, 80, ALLEGRO_ALIGN_LEFT, "%i" , topViewPoint_);

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




		if(displayWidth_ - tempXOffset < 0)
		{
			FinXRight = 0;
		}
		else if(XRight + tempXOffset > displayWidth_)
		{
			FinXRight = displayWidth_ - tempXOffset;
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




	
		if(displayHeight_ - tempYOffset < 0)
		{
			FinYBot = 0;
		}
		else if(tempYOffset + YBot > displayHeight_)
		{
			FinYBot = displayHeight_ - tempYOffset;
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
		if(FinXLeft >= 0 && FinXRight >= displayWidth_ && FinXRight < XRight)
		{
			FinXRight++;
		}
		//Add an extra cube to draw if the map is over screen dimensions so it draws the last cube position.
		if(FinYTop >= 0 && FinYBot >= displayHeight_ && FinYBot < YBot)
		{
			FinYBot++;
		}


		rightViewPoint_ = FinXRight;
		leftViewPoint_ = FinXLeft;
		botViewPoint_ = FinYBot;
		topViewPoint_ = FinYTop;

	}


	void Map::SetMapYOffset(int mapYoffset)
	{
		mapYoffset_ = mapYoffset;
	}

	void Map::SetMapXOffset(int mapXoffset)
	{
		mapXoffset_ = mapXoffset;
	}











	void Map::SaveMap(ALLEGRO_DISPLAY *display)
	{
		ALLEGRO_FILECHOOSER *save_window;
		save_window = al_create_native_file_dialog("D:\\C++\\Allegro\\Aced\\Maps\\", "Save Map", "*.*", ALLEGRO_FILECHOOSER_SAVE);
		al_show_native_file_dialog(display, save_window);
	

		const char *Path = NULL;
		Path = al_get_native_file_dialog_path(save_window,0);
	
		if(Path == NULL)
		{

		}
		else
		{
			ALLEGRO_FILE *FO = NULL;
			FO = al_fopen(Path,"w");



			char temp[20];
			sprintf_s(temp,"%d",width_);
			al_fputs(FO,"<MapWidth>");
			al_fputs(FO,temp);
			al_fputs(FO,"\n");

			sprintf_s(temp,"%d",height_);
			al_fputs(FO,"<MapHeight>");
			al_fputs(FO,temp);
			al_fputs(FO,"\n");

			sprintf_s(temp,"%d",playerStartX_);
			al_fputs(FO,"<playerStartX>");
			al_fputs(FO,temp);
			al_fputs(FO,"\n");

			sprintf_s(temp,"%d",playerStartY_);
			al_fputs(FO,"<playerStartY>");
			al_fputs(FO,temp);
			al_fputs(FO,"\n");


			for(int i = 0; i < width_; i++)
			{
				for(int j = 0; j < height_; j++)
				{			
					sprintf_s(temp,"%d",tiles_[i][j].GetCurrentPositionX());
					al_fputs(FO,"<TileX>");
					al_fputs(FO,temp);
					al_fputs(FO,"\n");
			
					sprintf_s(temp,"%d",tiles_[i][j].GetCurrentPositionY());
					al_fputs(FO,"<TileY>");
					al_fputs(FO,temp);
					al_fputs(FO,"\n");
			
					sprintf_s(temp,"%d",tiles_[i][j].GetTileType());
					al_fputs(FO,"<TileType>");
					al_fputs(FO,temp);
					al_fputs(FO,"\n");

					sprintf_s(temp,"%f",tiles_[i][j].GetColor().r);
					al_fputs(FO,"<TileColourR>");
					al_fputs(FO,temp);
					al_fputs(FO,"\n");

					sprintf_s(temp,"%f",tiles_[i][j].GetColor().g);
					al_fputs(FO,"<TileColourG>");
					al_fputs(FO,temp);
					al_fputs(FO,"\n");

					sprintf_s(temp,"%f",tiles_[i][j].GetColor().b);
					al_fputs(FO,"<TileColourB>");
					al_fputs(FO,temp);
					al_fputs(FO,"\n");
				}
			}
			al_fclose(FO);
		}
	}


	void Map::LoadMap(ALLEGRO_DISPLAY *display)
	{
		ALLEGRO_FILECHOOSER *load_window;
		load_window = al_create_native_file_dialog("D:\\C++\\Allegro\\Aced\\Maps\\", "Load Map", "*.*", 0);
		al_show_native_file_dialog(display, load_window);
	
		int newmapwidth = 0;
		int newmapheight = 0;

		const char *Path = NULL;
		Path = al_get_native_file_dialog_path(load_window,0);
	
		if(Path == NULL)
		{

		}
		else
		{
			ALLEGRO_FILE *FO = NULL;
			FO = al_fopen(Path,"r");


			///////////////////////////this stuff might be redundant...rethink the resetmapwidth/height/color/x/y/type...
			char temp[50];

			al_fgets(FO,temp,50);
			char *pch = strtok_s(temp, ">\n", NULL);
			pch = strtok_s(NULL, ">\n", NULL);	
			newmapwidth = atoi(pch);
			//resetMapWidth(atoi(pch));//width

			al_fgets(FO,temp,50);
			strtok_s(temp, ">\n", NULL);
			pch = strtok_s(NULL, ">\n", NULL);	
			newmapheight = atoi(pch);
			//resetMapHeight(atoi(pch));//height

			if(tiles_.empty() == true)
			{
				CreateTiles(newmapwidth, newmapheight);//leave this for later for main menu load mapping and for gamestuff.
			}
			else
			{
				SetMapSize(newmapwidth, newmapheight);
			}
			al_fgets(FO,temp,50);
			strtok_s(temp, ">\n", NULL);
			pch = strtok_s(NULL, ">\n", NULL);	
			SetPlayerStartX(atoi(pch));

			al_fgets(FO,temp,50);
			strtok_s(temp, ">\n", NULL);
			pch = strtok_s (NULL, ">\n", NULL);	
			SetPlayerStartY(atoi(pch));

			//tiles
			int x;
			int y;
			float r;
			float b;
			float g;
			int type;

	
			for(int i = 0; i < (width_ * height_); i++)
			{
				al_fgets(FO,temp,50);
				strtok_s(temp, ">\n", NULL);
				pch = strtok_s(NULL, ">\n", NULL);	
				x = atoi(pch);
	
				al_fgets(FO,temp,50);
				strtok_s(temp, ">\n", NULL);
				pch = strtok_s(NULL, ">\n", NULL);	
				y = atoi(pch);

				al_fgets(FO,temp,50);
				strtok_s(temp, ">\n", NULL);
				pch = strtok_s(NULL, ">\n", NULL);	
				type = atoi(pch);

				al_fgets(FO,temp,50);
				strtok_s(temp, ">\n", NULL);
				pch = strtok_s(NULL, ">\n", NULL);	
				r = atof(pch);

				al_fgets(FO,temp,50);
				strtok_s(temp, ">\n", NULL);
				pch = strtok_s(NULL, ">\n", NULL);	
				b = atof(pch);

				al_fgets(FO,temp,50);
				strtok_s(temp, ">\n", NULL);
				pch = strtok_s(NULL, ">\n", NULL);	
				g = atof(pch);
	


				//tiles_[x][y].setTileX(x);
				//tiles_[x][y].setTileY(y);
				tiles_[x][y].SetCurrentPosition(x,y);
				//tiles_[x][y].SetTileType(type);
				//tiles_[x][y].SetColor(al_map_rgb_f(r,b,g));
			}

			al_fclose(FO);
		}
	}


}
