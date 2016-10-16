#include "Tile.h"


namespace StaticDLL {

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

	Image *Tile::GetObjectImage()
	{
		return image_;
	}
	bool Tile::GetHasImage()
	{
		return hasImage_;
	}


	ALLEGRO_COLOR Tile::GetColor() {
		return chosenColor_;
	}

	EnumDLL::IMAGESETS Tile::GetImageSet() {
		return imageSet_;
	}

	






	//-----------------------------------------------------------------------------------------------------

	//Sets


	



	//Seperate all Setting property types for setting tiles to a value
	void Tile::SetTileObjectImageFromTile(EditorItemBase *selectedTile, int x, int y) {
		//Both tiles ref or not will be same collision type
		hasImage_ = true;
		image_ = selectedTile->GetObjectImage();
		imageSet_ = selectedTile->GetImageSet();
	}

	void Tile::SetTileImage(Image *selectedImage) {
		hasImage_ = true;
		image_ = selectedImage;
	}




	void Tile::SetObjectProperties(EditorItemBase *selectedObject) {

		if (selectedObject->GetHasColor() && selectedObject->GetHasImage())
		{
			SetImage(selectedObject->GetObjectImage());
			SetColor(selectedObject->GetColor());
		}
		else if (selectedObject->GetObjectImage())
		{
			SetImage(selectedObject->GetObjectImage());
		}
		else if (selectedObject->GetHasColor())
		{
			SetColor(selectedObject->GetColor());
		}

		return;

	}



	void Tile::SetImage(Image *image)
	{
		hasImage_ = true;
		image_ = image;
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
	

	void Tile::SetImageSet(EnumDLL::IMAGESETS set) {
		imageSet_ = set;
	}




	//-----------------------------------------------------------------------------------------------------

	//Draws



	





	void Tile::DrawObject(double currentPositionX, double currentPositionY, int xOffset, int yOffset) {
		if (hasImage_ &&  hasColor_)
		{
			al_draw_tinted_scaled_bitmap(
				image_->GetImage(),
				chosenColor_,
				0, 0, image_->GetWidth()*Constants::TileSize(), image_->GetHeight()*Constants::TileSize(),
				currentPositionX*Constants::TileSize() + xOffset,
				currentPositionY*Constants::TileSize() + yOffset,
				image_->GetWidth()*Constants::TileSize(),
				image_->GetHeight()*Constants::TileSize(),
				0
			);
		}
		else if (hasImage_)
		{
			al_draw_scaled_bitmap(
				image_->GetImage(),
				0, 0, image_->GetWidth()*Constants::TileSize(), image_->GetHeight()*Constants::TileSize(),
				currentPositionX*Constants::TileSize() + xOffset,
				currentPositionY*Constants::TileSize() + yOffset,
				image_->GetWidth()*Constants::TileSize(),
				image_->GetHeight()*Constants::TileSize(),
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
		image_ = nullptr;
	};

	void Tile::RemoveColor() {
		hasColor_ = false;
		chosenColor_.r = 1;
		chosenColor_.g = 1;
		chosenColor_.b = 1;
		chosenColor_.a = 0;
	};
}
