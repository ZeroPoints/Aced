#include "Tile.h"


namespace AcedSharedDLL {

	Tile::Tile()
	{
		chosenColor_ = al_map_rgb_f(1, 1, 1);
		hasImage_ = false;
		hasColor_ = false;
	}


	Tile::~Tile()
	{
		//fprintf(stderr, "A Tile Destructed\n");
	}







	//-----------------------------------------------------------------------------------------------------

	//Gets





	
	bool Tile::GetHasColor()
	{
		return hasColor_;
	}

	ImageBundle *Tile::GetImageBundle()
	{
		return imageBundle_;
	}
	bool Tile::GetHasImage()
	{
		return hasImage_;
	}


	ALLEGRO_COLOR Tile::GetColor() {
		return chosenColor_;
	}

	AcedSharedDLL::IMAGESETS Tile::GetImageSet() {
		return imageSet_;
	}

	






	//-----------------------------------------------------------------------------------------------------

	//Sets


	



	//Seperate all Setting property types for setting tiles to a value
	void Tile::SetTileBase(EditorItemBase *selectedTile) {
		//Both tiles ref or not will be same collision type
		hasImage_ = true;
		imageBundle_ = selectedTile->GetImageBundle();
		imageSet_ = selectedTile->GetImageSet();
	}







	void Tile::SetImageBundle(ImageBundle *imageBundle) {
		hasImage_ = true;
		imageBundle_ = imageBundle;
	}









	void Tile::SetColor(ALLEGRO_COLOR color) {
		hasColor_ = true;
		chosenColor_ = color;
	}
	void Tile::SetColorR(float r) {
		hasColor_ = true;
		chosenColor_.r = r;
	}
	void Tile::SetColorG(float g) {
		hasColor_ = true;
		chosenColor_.g = g;
	}
	void Tile::SetColorB(float b) {
		hasColor_ = true;
		chosenColor_.b = b;
	}
	void Tile::SetColorA(float a) {
		hasColor_ = true;
		chosenColor_.a = a;
	}
	

	void Tile::SetImageSet(AcedSharedDLL::IMAGESETS set) {
		imageSet_ = set;
	}




	//-----------------------------------------------------------------------------------------------------

	//Draws



	





	void Tile::DrawObject(double currentPositionX, double currentPositionY, int xOffset, int yOffset) {
		if (hasImage_ &&  hasColor_)
		{
			al_draw_tinted_scaled_bitmap(
				imageBundle_->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetImage(),
				chosenColor_,
				0, 0, 
				imageBundle_->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetWidth()*Constants::TileSize(), 
				imageBundle_->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetHeight()*Constants::TileSize(),
				currentPositionX*Constants::TileSize() + xOffset,
				currentPositionY*Constants::TileSize() + yOffset,
				imageBundle_->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetWidth()*Constants::TileSize(),
				imageBundle_->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetHeight()*Constants::TileSize(),
				0
			);
		}
		else if (hasImage_)
		{
			al_draw_scaled_bitmap(
				imageBundle_->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetImage(),
				0, 0, 
				imageBundle_->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetWidth()*Constants::TileSize(), 
				imageBundle_->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetHeight()*Constants::TileSize(),
				currentPositionX*Constants::TileSize() + xOffset,
				currentPositionY*Constants::TileSize() + yOffset,
				imageBundle_->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetWidth()*Constants::TileSize(),
				imageBundle_->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetHeight()*Constants::TileSize(),
				0
			);
		}
		else if (hasColor_)
		{
			al_draw_filled_rectangle(
				currentPositionX*Constants::TileSize() + xOffset,
				currentPositionY*Constants::TileSize() + yOffset,
				currentPositionX*Constants::TileSize() + Constants::TileSize() + xOffset,
				currentPositionY*Constants::TileSize() + Constants::TileSize() + yOffset,
				chosenColor_
			);
		}

	};











	




	//set et props of tile to empty
	void Tile::RemoveAllProperties() {
		RemoveImage();
		RemoveColor();
	};

	void Tile::RemoveImage() {
		hasImage_ = false;
		imageBundle_ = nullptr;
	};

	void Tile::RemoveColor() {
		hasColor_ = false;
		chosenColor_.r = 1;
		chosenColor_.g = 1;
		chosenColor_.b = 1;
		chosenColor_.a = 0;
	};
}
