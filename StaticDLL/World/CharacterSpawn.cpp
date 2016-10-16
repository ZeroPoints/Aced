#include "CharacterSpawn.h"

namespace StaticDLL {

	//CharacterSpawn::CharacterSpawn(Settings *settings, Map *map)
	CharacterSpawn::CharacterSpawn(Settings *settings)
	{
		hasImage_ = false;
		hasColor_ = false;
		hasImageReference_ = false;
		currentRotation_ = 0;
		settings_ = settings;
		//map_ = map;
		SetCurrentPosition(1, 1);
		SetColor(al_map_rgb_f(1, 1, 1));
		SetWidth(0.8);
		SetHeight(0.8);




		//fprintf(stderr, "An CharacterSpawn created\n");
	}





	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//Sets




	void CharacterSpawn::SetCurrentPosition(double x, double y) {
		currentPositionX_ = x;
		currentPositionY_ = y;
	}
	void CharacterSpawn::SetColor(ALLEGRO_COLOR color) {
		chosenColor_ = color;
	}
	void CharacterSpawn::SetWidth(double val) {
		width_ = val;
	}
	void CharacterSpawn::SetHeight(double val) {
		height_ = val;
	}

	void CharacterSpawn::SetCurrentPositionX(double val) {
		currentPositionX_ = val;
	}

	void CharacterSpawn::SetCurrentPositionY(double val) {
		currentPositionY_ = val;
	}



	void CharacterSpawn::SetObjectImageColor(Image *image)
	{
		if (image->GetImage() != nullptr)
		{
			hasImage_ = true;
			image_ = image;
			height_ = image->GetHeight();
			width_ = image->GetWidth();
		}
		else
		{
			hasColor_ = true;
			chosenColor_ = image->GetColor();
		}
	}








	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//Gets







	double CharacterSpawn::GetCurrentPositionX() {
		return currentPositionX_;
	};


	double CharacterSpawn::GetCurrentPositionY() {
		return currentPositionY_;
	};









	double CharacterSpawn::GetHeight() {
		return height_;
	}
	double CharacterSpawn::GetWidth() {
		return width_;
	}









	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//Misc





	//Offsets are the map offset
	void CharacterSpawn::DrawObjectRotate(int xOffset, int yOffset) {
		//0.8




		if (hasImage_ &&  hasColor_)
		{
			al_draw_tinted_scaled_rotated_bitmap(
				image_->GetImage(),
				chosenColor_,
				image_->GetImageWidth() / 2.0,
				image_->GetImageHeight() / 2.0,
				(currentPositionY_ + width_ / 2)*Constants::TileSize() + xOffset,
				(currentPositionY_ + height_ / 2)*Constants::TileSize() + yOffset,
				width_*Constants::TileSize() / (image_->GetImageWidth()*1.0),
				height_*Constants::TileSize() / (image_->GetImageHeight()*1.0),
				currentRotation_,
				0
			);
		}
		else if (hasImage_)
		{
			al_draw_scaled_rotated_bitmap(
				image_->GetImage(),
				image_->GetImageWidth() / 2.0,
				image_->GetImageHeight() / 2.0,
				(currentPositionY_ + width_ / 2)*Constants::TileSize() + xOffset,
				(currentPositionY_ + height_ / 2)*Constants::TileSize() + yOffset,
				width_*Constants::TileSize() / (image_->GetImageWidth()*1.0),
				height_*Constants::TileSize() / (image_->GetImageHeight()*1.0),
				currentRotation_,
				0
			);
		}





	};




























	void CharacterSpawn::Update()
	{
		

	}










	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//------------
	//------------
	//------------






}