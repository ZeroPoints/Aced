#include "TilePage.h"


namespace StaticDLL{







	//Draws the tiles from reference. Uses set tiles as its range indicator
	void TilePage::DrawTiles(std::vector<std::vector<Tile>> &tileRef, bool showCollision)
	{
		int i;
		int j;
		for(i = 0; i < x_; i++)
		{
			for(j = yRangeMin_; j < (yRangeMax_>tileRef[i].size()?tileRef[i].size():yRangeMax_); j++)
			{				
				tileRef[i][j].DrawObject(0,0);
				if(showCollision)
				{
					tileRef[i][j].DrawObjectType(0,0,settings_->GetColorCollisionInvert());
				}
			}
		}
	}





	//Check each tile that is in range for click intersecting and returns the tile reference and the x and y value of that tile
	bool TilePage::MouseActivity(std::vector<std::vector<Tile>> &tileRef, int mouseX, int mouseY)
	{
		int i;
		int j;
		//REWRITE THIS JUST CHECK MOUSE CLICK IN BOUNDS
		//THEN ACCESS TILE PROPERTY DYNAMICALLY using x,y
		for(i = 0; i < x_; i++)
		{
			for(j = yRangeMin_; j < (yRangeMax_>tileRef[i].size()?tileRef[i].size():yRangeMax_); j++)
			{				
				if(tileRef[i][j].ClickIntersects(mouseX, mouseY))
				{
					//points to selected tile
					selectedTile_ = &tileRef[i][j];
					selectedTileX_ = i;
					selectedTileY_ = j;
					return true;	
				}
			}
		}


		return false;
	}






}