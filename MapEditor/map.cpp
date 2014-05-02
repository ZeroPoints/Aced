#include "map.h"

Map::Map()
{
	mapXoffset_ = 0;
	mapYoffset_ = 0;
}

void Map::createTiles()
{
	std::vector<std::vector<Tile> > tiles(mapwidth_,std::vector<Tile>(mapheight_));
	tiles_ = tiles;
}

void Map::resetMapWidth(int mapwidth)
{
	tiles_.resize(mapwidth);
	for(int i = 0; i < mapwidth; ++i)
	{
		tiles_[i].resize(mapheight_);//do i have to resize the second array if i only want to resize the first...will the second that is binded to it be created to the same height as original array.
	}
	oldmapwidth_ = mapwidth_;
	mapwidth_ = mapwidth;	

	for(int i = oldmapwidth_; i < mapwidth_; i++)//see i thought about wasted memory consumption here so it only sets values of newly spawned parts of the array
	{
		for(int j = 0; j < mapheight_; j++)
		{//but maybe this stuff is redundant or i should create a new class for loading...
			tiles_[i][j].setColour(al_map_rgb_f(0.5,0.5,0.5));//sets all tiles to grey
			tiles_[i][j].setTileType(0);
			tiles_[i][j].setTileX(i);
			tiles_[i][j].setTileY(j);
		}
	}
}

void Map::resetMapHeight(int mapheight)
{
	//tiles_.resize(mapwidth_);
	for(int i = 0; i < mapwidth_; ++i)
	{
		tiles_[i].resize(mapheight);
	}
	oldmapheight_ = mapheight_;
	mapheight_ = mapheight;

	for(int i = 0; i < mapwidth_; i++)
	{
		for(int j = oldmapheight_; j < mapheight_; j++)
		{
			tiles_[i][j].setColour(al_map_rgb_f(0.5,0.5,0.5));//sets all tiles to grey
			tiles_[i][j].setTileType(0);
			tiles_[i][j].setTileX(i);
			tiles_[i][j].setTileY(j);
		}
	}
}

void Map::setPlayerStartX(int playerStartX)
{
	playerStartX_ = playerStartX;
}

void Map::setPlayerStartY(int playerStartY)
{
	playerStartY_ = playerStartY;
}

void Map::setMapHeight(int mapheight)
{
	mapheight_ = mapheight;
}
void Map::setMapWidth(int mapwidth)
{
	mapwidth_ = mapwidth;
}

void Map::setDisplayHeight(int displayheight)
{
	displayheight_ = displayheight;
}
void Map::setDisplayWidth(int displaywidth)
{
	displaywidth_ = displaywidth;
}

void Map::saveMap(ALLEGRO_DISPLAY *display)
{
	ALLEGRO_FILECHOOSER *save_window;
	save_window = al_create_native_file_dialog("D:\\C++\\Allegro\\Aced\\Maps\\", "Save Map", "*.map", ALLEGRO_FILECHOOSER_SAVE);
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
		sprintf(temp,"%d",mapwidth_);
		al_fputs(FO,"<MapWidth>");
		al_fputs(FO,temp);
		al_fputs(FO,"\n");

		sprintf(temp,"%d",mapheight_);
		al_fputs(FO,"<MapHeight>");
		al_fputs(FO,temp);
		al_fputs(FO,"\n");

		sprintf(temp,"%d",playerStartX_);
		al_fputs(FO,"<playerStartX>");
		al_fputs(FO,temp);
		al_fputs(FO,"\n");

		sprintf(temp,"%d",playerStartY_);
		al_fputs(FO,"<playerStartY>");
		al_fputs(FO,temp);
		al_fputs(FO,"\n");


		for(int i = 0; i < mapwidth_; i++)
		{
			for(int j = 0; j < mapheight_; j++)
			{			
				sprintf(temp,"%d",tiles_[i][j].getTileX());
				al_fputs(FO,"<TileX>");
				al_fputs(FO,temp);
				al_fputs(FO,"\n");
			
				sprintf(temp,"%d",tiles_[i][j].getTileY());
				al_fputs(FO,"<TileY>");
				al_fputs(FO,temp);
				al_fputs(FO,"\n");
			
				sprintf(temp,"%d",tiles_[i][j].getTileType());
				al_fputs(FO,"<TileType>");
				al_fputs(FO,temp);
				al_fputs(FO,"\n");

				sprintf(temp,"%f",tiles_[i][j].getColour().r);
				al_fputs(FO,"<TileColourR>");
				al_fputs(FO,temp);
				al_fputs(FO,"\n");

				sprintf(temp,"%f",tiles_[i][j].getColour().g);
				al_fputs(FO,"<TileColourG>");
				al_fputs(FO,temp);
				al_fputs(FO,"\n");

				sprintf(temp,"%f",tiles_[i][j].getColour().b);
				al_fputs(FO,"<TileColourB>");
				al_fputs(FO,temp);
				al_fputs(FO,"\n");
			}
		}
		al_fclose(FO);
	}
}


void Map::loadMap(ALLEGRO_DISPLAY *display)
{
	ALLEGRO_FILECHOOSER *load_window;
	load_window = al_create_native_file_dialog("D:\\C++\\Allegro\\Aced\\Maps\\", "Load Map", "*.map", 0);
	al_show_native_file_dialog(display, load_window);
	

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
		char *pch = strtok(temp, ">\n");
		pch = strtok (NULL, ">\n");	
		mapwidth_ = atoi(pch);
		//resetMapWidth(atoi(pch));//width

		al_fgets(FO,temp,50);
		strtok(temp, ">\n");
		pch = strtok (NULL, ">\n");	
		mapheight_ = atoi(pch);
		//resetMapHeight(atoi(pch));//height

		createTiles();
		resetMapWidth(mapwidth_);
		resetMapHeight(mapheight_);

		al_fgets(FO,temp,50);
		strtok(temp, ">\n");
		pch = strtok (NULL, ">\n");	
		setPlayerStartX(atoi(pch));

		al_fgets(FO,temp,50);
		strtok(temp, ">\n");
		pch = strtok (NULL, ">\n");	
		setPlayerStartY(atoi(pch));

		//tiles
		int x;
		int y;
		float r;
		float b;
		float g;
		int type;

	
		for(int i = 0; i < (mapwidth_ * mapheight_); i++)
		{
			al_fgets(FO,temp,50);
			strtok(temp, ">\n");
			pch = strtok (NULL, ">\n");	
			x = atoi(pch);
	
			al_fgets(FO,temp,50);
			strtok(temp, ">\n");
			pch = strtok (NULL, ">\n");	
			y = atoi(pch);

			al_fgets(FO,temp,50);
			strtok(temp, ">\n");
			pch = strtok (NULL, ">\n");	
			type = atoi(pch);

			al_fgets(FO,temp,50);
			strtok(temp, ">\n");
			pch = strtok (NULL, ">\n");	
			r = atof(pch);

			al_fgets(FO,temp,50);
			strtok(temp, ">\n");
			pch = strtok (NULL, ">\n");	
			b = atof(pch);

			al_fgets(FO,temp,50);
			strtok(temp, ">\n");
			pch = strtok (NULL, ">\n");	
			g = atof(pch);
	


			tiles_[x][y].setTileX(x);
			tiles_[x][y].setTileY(y);
			tiles_[x][y].setTileType(type);
			tiles_[x][y].setColour(al_map_rgb_f(r,b,g));
		}

		al_fclose(FO);
	}
}

void Map::drawMap()
{
	int i;
	int j;
	

	int XLeft;
	int XRight;
	int YTop;
	int YBot;

//	//how can i reduce this
//[19:59:56] >>	whats that
//[20:00:12] <<	my thing
//[20:00:22] <<	check that happens before each draw
//[20:01:10] >>	do you have scrolling?
//[20:01:13] <<	ye
//[20:01:22] <<	hence offset
//[20:01:29] <<	?
//[20:02:36] <<	mmm
//[20:02:58] <<	i should do mine like yours my offset scrolly thingy
//[20:04:07] >>	dunno havent really seen what your doing for ages
//[20:04:15] >>	you should really use version control makes life so much easier
//[20:04:20] <<	meh
//[20:04:25] <<	my coms accessible
//[20:04:30] <<	shit gotta go toilet
//[20:04:40] >>	opposed to go elsewhere
//[20:06:47] <<	mmmm
//[20:07:30] >>	i think my slow map load may just possibly have something to do with 10 forloops
//[20:08:38] <<	alright see your code
//[20:08:39] <<	at
//[20:08:45] <<	if(leftXpos_/32 < 0)
//            {
//                leftXpos_=0;
//            }
//            if(topYpos_/32 < 0)
//            {
//                topYpos_=0;
//            }
//
//            if(rightXpos_/32 > gameMap_->getXDimensions())
//            {
//                rightXpos_=gameMap_->getXDimensions()*32;//1;
//            }
//
//            if(bottomYpos_/32 > gameMap_->getYDimensions())
//            {
//                bottomYpos_=gameMap_->getYDimensions()*32;
//            }
//[20:08:55] <<	around line 368 in game.cpp
//[20:08:59] <<	mines doing this ok
//[20:09:13] <<	but to a greater extent
//[20:09:24] <<	how does your 
//for (int i=floor(leftXpos_/32); i<ceil(rightXpos_/32); ++i)
//	{
//		for (int j=floor(topYpos_/32); j<floor(bottomYpos_/32);++j)//ceil(bottomYpos); ++j) //weird +!
//		{
//[20:09:52] <<	know that its tile[][]  isnt greater then your vector array
//[20:11:34] >>	because it isnt?
//[20:11:52] <<	mmmmmm
//[20:11:56] <<	wait thats in there
//[20:11:59] <<	but ummm
//[20:13:26] <<	hmmm
//[20:13:31] >>	im just drawing whats between leftx and rightx
//[20:13:33] <<	ok
//[20:13:35] <<	okokok
//[20:13:41] <<	so am i
//[20:14:11] <<	i get it now
//[20:14:13] <<	mmmm
//[20:14:19] >>	hmm
//[20:14:36] <<	its cos i havent been applying offset kinda before hand when it each time gets offset
//[20:14:44] <<	i apply offset during the equation 
//[20:15:28] <<	and you apply offset to a pos setting in your actual tile mmm but i just apply offset as an addon when i get to the draw 
//[20:15:46] <<	and i dont have actualy pos i just base it off the number it is in the vector hmmm
//[20:16:21] <<	so if i can apply this offset calculations during the times it happens instead of when i need to draw that will reduce some calculations
//[20:16:34] <<	of applying offset on the go when i need it
//[20:16:35] <<	hmmm
//[20:16:43] <<	sounds like a plan
//[20:16:49] <<	thankyou mister rubber ducky
//[20:16:53] <<	that helped
//[20:17:10] <<	now dont let me lose this chat so i dont forget
//[20:17:19] >>	ok then///
	//so to sum it up i was doing calcs at ondraw. you were doing calcs onchange hmmmk

	//------------------------------------//
	XLeft = 0;
	XRight = tiles_.capacity();
	YTop = 0;
	YBot = tiles_[0].capacity();
	int FinXLeft = 0;
	int FinXRight = 0;
	int FinYTop = 0;
	int FinYBot = 0;

	if(((displaywidth_/20) - mapXoffset_) < 0)
	{
		FinXRight = 0;
	}
	else if((XRight + mapXoffset_) > displaywidth_/20)
	{
		FinXRight = (displaywidth_/20) - mapXoffset_;
	}
	else
	{
		FinXRight = XRight;
	}

	if(((XLeft + mapXoffset_) <= 0) && (0 - mapXoffset_) < XRight)
	{
		FinXLeft = 0 - mapXoffset_;
	}
	else
	{
		FinXLeft = 0;
	}
	

	if(((displayheight_/20) - mapYoffset_) < 0)
	{
		FinYBot = 0;
	}
	else if((YBot + mapYoffset_) > displayheight_/20)
	{
		FinYBot = (displayheight_/20) - mapYoffset_;
	}
	else
	{
		FinYBot = YBot;
	}


	if((YTop + mapYoffset_) <= 0 && (0 - mapYoffset_) < YBot)
	{		
		FinYTop = 0 - mapYoffset_;
	}
	else
	{
		FinYTop = 0;		
	}


	


	for(i = FinXLeft; i < FinXRight; i++)
	{
		for(j = FinYTop; j < FinYBot; j++)
		{				
					tiles_[i][j].drawTile(mapXoffset_, mapYoffset_,displaywidth_,displayheight_);	
		}
	}


	//printf("FinXRight = %i\n", FinXRight);
	//printf("FinXLeft = %i\n", FinXLeft);
	//printf("FinYBot = %i\n", FinYBot);
	//printf("FinYTop = %i\n", FinYTop);
	///------------------------------------------------all above me is working

	



	
}

void Map::setMapYOffset(int mapYoffset)
{
	mapYoffset_ = mapYoffset;
}

void Map::setMapXOffset(int mapXoffset)
{
	mapXoffset_ = mapXoffset;
}
