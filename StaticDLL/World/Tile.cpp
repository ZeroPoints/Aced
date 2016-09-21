#include "Tile.h"


namespace StaticDLL {

	Tile::Tile()
	{
		tileCollisionTypeColor_ = al_map_rgb_f(0, 0, 0);
		hasImageReference_ = false;
		hasImage_ = false;
		hasColor_ = false;
		height_ = 1;
		width_ = 1;
	}


	Tile::~Tile()
	{
		//i should really set the position to something mmm or have a bool. 
		//Shouldnt really need this soon later anyway its just a debug msg
		fprintf(stderr, "A Tile[%f][%f] Destructed\n", GetCurrentPositionX(), GetCurrentPositionY());
	}







	//-----------------------------------------------------------------------------------------------------

	//Gets




	
	EnumDLL::TILETYPE Tile::GetTileType()
	{
		return tileType_;
	}
	double Tile::GetCurrentPositionY() {
		return currentPositionY_;
	}
	double Tile::GetCurrentPositionX() {
		return currentPositionX_;
	}
	double Tile::GetWidth() {
		return width_;
	}

	double Tile::GetHeight() {
		return height_;
	}
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

	bool Tile::GetClickable() {
		return clickable_;
	}

	ALLEGRO_COLOR Tile::GetColor() {
		return chosenColor_;
	}

	EnumDLL::IMAGESETS Tile::GetImageSet() {
		return imageSet_;
	}

	bool Tile::GetHasImageOrReference() {
		return hasImageReference_ || hasImage_;
	}

	bool Tile::GetHasImageReference() {
		return hasImageReference_;
	}

	double Tile::GetImageReferenceX() {
		return imageReferenceX_;
	}
	double Tile::GetImageReferenceY() {
		return imageReferenceY_;
	}






	//-----------------------------------------------------------------------------------------------------

	//Sets


	//Sets equivalent properties for the tile from another tile object
	void Tile::SetTileProperties(Tile *selectedTile, bool isReference)
	{
		//So if the current location tile is not already empty force new tile SOLID properties over it.
		if (GetTileType() == EnumDLL::TILETYPE::EMPTYTILE)
		{
			SetTileTypeProperties(selectedTile);
		}
		SetObjectProperties(selectedTile, isReference);
	}





	void Tile::SetTileType(EnumDLL::TILETYPE tileType)
	{
		tileType_ = tileType;
	}

	//Set Collision Type
	void Tile::SetTileTypeProperties(Tile *selectedTile)
	{
		tileType_ = selectedTile->GetTileType();
	}



	void Tile::SetWidth(double x) {
		width_ = x;
	}

	void Tile::SetHeight(double y) {
		height_ = y;
	}




	//Seperate all Setting property types for setting tiles to a value
	void Tile::SetTileObjectImageFromTile(Tile *selectedTile, bool isReference, int x, int y) {

		//Both tiles ref or not will be same collision type
		tileType_ = selectedTile->GetTileType();

		imageReferenceX_ = x;
		imageReferenceY_ = y;


		if (isReference) {
			hasImageReference_ = true;
		}
		else {
			hasImage_ = true;
			image_ = selectedTile->GetObjectImage();
			imageSet_ = selectedTile->GetImageSet();
		}
	}

	void Tile::SetTileObjectImageFromImage(Image *selectedImage, bool isReference, int x, int y) {

		imageReferenceX_ = x;
		imageReferenceY_ = y;

		if (isReference) {
			hasImageReference_ = true;
		}
		else {
			hasImage_ = true;
			image_ = selectedImage;
		}
	}




	void Tile::SetObjectProperties(Tile *selectedObject, bool isReference) {

		if (selectedObject->GetHasColor() && selectedObject->GetHasImage())
		{
			hasImage_ = true;
			SetObjectImageColor(selectedObject->GetObjectImage());
			hasColor_ = true;
			chosenColor_ = selectedObject->chosenColor_;
		}
		else if (selectedObject->GetObjectImage())
		{
			hasImage_ = true;
			if (!isReference) {
				SetObjectImageColor(selectedObject->GetObjectImage());
				height_ = selectedObject->GetHeight();
				width_ = selectedObject->GetWidth();
			}
			else {
				//any image that is a ref is just passed as image  
				hasImageReference_ = true;
				image_ = selectedObject->GetObjectImage();
				height_ = 1;
				width_ = 1;
			}


		}
		else if (selectedObject->GetHasColor())
		{
			hasColor_ = true;
			chosenColor_ = selectedObject->chosenColor_;
		}

		return;

	}




	//This is used in tile page 
	//Put some color tintin intelligence into setting this objects properties.
	//So can add color if it exists. Or add image if it exists
	//This is used to set objects properties based on if the image has a color or a image
	//TODO: ADD in color and image together aswell just incase later
	void Tile::SetObjectImageColor(Image *image)
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


	void Tile::SetClickable(bool clickable) {
		clickable_ = clickable;
	}



	void Tile::SetColor(ALLEGRO_COLOR color) {
		hasColor_ = true;
		chosenColor_ = color;
	}
	void Tile::SetColorA(float a) {
		hasColor_ = true;
		chosenColor_.a = a;
	}
	void Tile::SetColorB(float b) {
		hasColor_ = true;
		chosenColor_.b = b;
	}
	void Tile::SetColorR(float r) {
		hasColor_ = true;
		chosenColor_.r = r;
	}
	void Tile::SetColorG(float g) {
		hasColor_ = true;
		chosenColor_.g = g;
	}
	void Tile::SetCurrentPosition(double x, double y) {
		currentPositionX_ = x;
		currentPositionY_ = y;
	}
	void Tile::SetCurrentPositionX(double x) {
		currentPositionX_ = x;
	}
	void Tile::SetCurrentPositionY(double y) {
		currentPositionY_ = y;
	}
	
	void Tile::SetImageSet(EnumDLL::IMAGESETS set) {
		imageSet_ = set;
	}

	void Tile::SetHasColor(bool hasColor)
	{
		hasColor_ = hasColor;
	}




	//-----------------------------------------------------------------------------------------------------

	//Draws



	//Draws the tiles collision properties
	//Inverts them if necassery
	void Tile::DrawObjectType(int xOffset, int yOffset, bool invert) {

		

		ALLEGRO_COLOR newColor;
		newColor.a = 1;
		newColor.r = invert ? !tileCollisionTypeColor_.r : tileCollisionTypeColor_.r;
		newColor.g = invert ? !tileCollisionTypeColor_.g : tileCollisionTypeColor_.g;
		newColor.b = invert ? !tileCollisionTypeColor_.b : tileCollisionTypeColor_.b;

		if (tileType_ == EnumDLL::TILETYPE::SOLIDTILE)
		{
			al_draw_rectangle(
				GetCurrentPositionX()*Constants::TileSize() + xOffset + (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				GetCurrentPositionX()*Constants::TileSize() + GetWidth()*Constants::TileSize() + xOffset - (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + GetHeight()*Constants::TileSize() + yOffset - (Constants::TileSize() / 5),
				newColor, 2
			);
		}
		else if (tileType_ == EnumDLL::TILETYPE::COLLISIONTOPTILE)
		{
			al_draw_line(
				GetCurrentPositionX()*Constants::TileSize() + xOffset + (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				GetCurrentPositionX()*Constants::TileSize() + GetWidth()*Constants::TileSize() + xOffset - (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				newColor, 2
			);
		}
		else if (tileType_ == EnumDLL::TILETYPE::COLLISIONLEFTTILE)
		{
			al_draw_line(
				GetCurrentPositionX()*Constants::TileSize() + xOffset + (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				GetCurrentPositionX()*Constants::TileSize() + xOffset + (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + GetHeight()*Constants::TileSize() + yOffset - (Constants::TileSize() / 5),
				newColor, 2
			);
		}
		else if (tileType_ == EnumDLL::TILETYPE::COLLISIONRIGHTTILE)
		{
			al_draw_line(
				GetCurrentPositionX()*Constants::TileSize() + GetWidth()*Constants::TileSize() + xOffset - (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				GetCurrentPositionX()*Constants::TileSize() + GetWidth()*Constants::TileSize() + xOffset - (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + GetHeight()*Constants::TileSize() + yOffset - (Constants::TileSize() / 5),
				newColor, 2
			);
		}
		else if (tileType_ == EnumDLL::TILETYPE::INVERTCOLLISIONCOLOR)
		{
			//reverse inversion tile 
			newColor.r = invert ? tileCollisionTypeColor_.r : !tileCollisionTypeColor_.r;
			newColor.g = invert ? tileCollisionTypeColor_.g : !tileCollisionTypeColor_.g;
			newColor.b = invert ? tileCollisionTypeColor_.b : !tileCollisionTypeColor_.b;
			al_draw_rectangle(
				GetCurrentPositionX()*Constants::TileSize() + xOffset + (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				GetCurrentPositionX()*Constants::TileSize() + GetWidth()*Constants::TileSize() + xOffset - (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + GetHeight()*Constants::TileSize() + yOffset - (Constants::TileSize() / 5),
				newColor, 2
			);
		}
	}





	//Draws the object...Uses the x and y offset from map to draw with displacement
	void Tile::DrawObject(int xOffset, int yOffset) {
		if (hasImageReference_) {
			return;
		}

		//if object has image and color draw tinting
		if (hasImage_ &&  hasColor_)
		{
			al_draw_tinted_scaled_bitmap(
				image_->GetImage(),
				chosenColor_,
				0, 0, image_->GetWidth()*Constants::TileSize(), image_->GetHeight()*Constants::TileSize(),
				currentPositionX_*Constants::TileSize() + xOffset,
				currentPositionY_*Constants::TileSize() + yOffset,
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
				currentPositionX_*Constants::TileSize() + xOffset,
				currentPositionY_*Constants::TileSize() + yOffset,
				image_->GetWidth()*Constants::TileSize(),
				image_->GetHeight()*Constants::TileSize(),
				0
			);
		}
		else
		{
			al_draw_filled_rectangle(
				currentPositionX_*Constants::TileSize() + xOffset,
				currentPositionY_*Constants::TileSize() + yOffset,
				currentPositionX_*Constants::TileSize() + width_*Constants::TileSize() + xOffset,
				currentPositionY_*Constants::TileSize() + height_*Constants::TileSize() + yOffset,
				chosenColor_
			);
		}
	};














	//-----------------------------------------------------------------------------------------------------

	//MISC

	//Detects If click intersects with the object selected
	bool Tile::ClickIntersects(int mouseX, int mouseY)
	{
		//Offset the mouse position to the actual coord as the mouseX and mouseY i read in a moded to be offset? by half the tile size for some reason
		mouseX = mouseX + (Constants::TileSize() / 2);
		mouseY = mouseY + (Constants::TileSize() / 2);

		if (mouseX >= (currentPositionX_*Constants::TileSize()) &&
			mouseX < ((currentPositionX_ + width_)*Constants::TileSize()) &&
			mouseY >= (currentPositionY_*Constants::TileSize()) &&
			mouseY < ((currentPositionY_ + height_)*Constants::TileSize()))
		{
			return true;
		}
		return false;

	};




	//set flag and set image to null
	void Tile::RemoveAllProperties() {
		tileCollisionTypeColor_ = al_map_rgb_f(0, 0, 0);
		hasImageReference_ = false;
		hasImage_ = false;
		hasColor_ = false;
		height_ = 1;
		width_ = 1;
		chosenColor_.r = 1;
		chosenColor_.g = 1;
		chosenColor_.b = 1;
		chosenColor_.a = 0;
		image_ = nullptr;
		tileType_ = EnumDLL::TILETYPE::EMPTYTILE;
		imageReferenceX_ = 0;
		imageReferenceY_ = 0;
	};

	//set flag and set image to null
	void Tile::RemoveImage() {
		hasImage_ = false;
		hasImageReference_ = false;
		//test this doesnt effect the actual object in imageloader memory dictionary
		image_ = nullptr;
	};
	//set flag and set color to white
	void Tile::RemoveColor() {
		hasColor_ = false;
		chosenColor_.r = 1;
		chosenColor_.g = 1;
		chosenColor_.b = 1;
		chosenColor_.a = 0;
	};
}
