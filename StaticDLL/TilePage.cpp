#include "TilePage.h"


namespace StaticDLL{

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


}