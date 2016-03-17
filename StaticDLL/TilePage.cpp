#include "TilePage.h"


namespace StaticDLL{







	//Draws the tiles from reference. Uses set tiles as its range indicator
	void TilePage::DrawTiles(std::vector<std::vector<Tile>> &tileRef)
	{
		int i;
		int j;
		for(i = 0; i < x_; i++)
		{
			for(j = yRangeMin_; j < yRangeMax_; j++)
			{				
				tileRef[i][j].DrawObject();
			}
		}
	}





	//Draws the tiles from reference. Uses set tiles as its range indicator
	bool TilePage::MouseActivity(std::vector<std::vector<Tile>> &tileRef, int mouseX, int mouseY)
	{
		int i;
		int j;
		for(i = 0; i < x_; i++)
		{
			for(j = yRangeMin_; j < yRangeMax_; j++)
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