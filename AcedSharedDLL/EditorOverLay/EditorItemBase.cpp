#include "EditorItemBase.h"


namespace AcedSharedDLL {

	EditorItemBase::EditorItemBase()
	{
		tileCollisionTypeColor_ = al_map_rgb_f(0, 0, 0);
		hasImageReference_ = false;
		hasImage_ = false;
		hasColor_ = false;
		height_ = 1;
		width_ = 1;
	}


	EditorItemBase::~EditorItemBase()
	{
		//fprintf(stderr, "A EditorItemBase Destructed\n");

	}







	//-----------------------------------------------------------------------------------------------------

	//Gets





	TILETYPE EditorItemBase::GetTileType()
	{
		return tileType_;
	}
	double EditorItemBase::GetCurrentPositionY() {
		return currentPositionY_;
	}
	double EditorItemBase::GetCurrentPositionX() {
		return currentPositionX_;
	}
	double EditorItemBase::GetWidth() {
		return width_;
	}

	double EditorItemBase::GetHeight() {
		return height_;
	}
	bool EditorItemBase::GetHasColor()
	{
		return hasColor_;
	}

	std::shared_ptr<ImageBundle> &EditorItemBase::GetImageBundle()
	{
		return imageBundle_;
	}
	bool EditorItemBase::GetHasImage()
	{
		return hasImage_;
	}


	ALLEGRO_COLOR EditorItemBase::GetColor() {
		return chosenColor_;
	}

	AcedSharedDLL::IMAGESETS EditorItemBase::GetImageSet() {
		return imageSet_;
	}

	bool EditorItemBase::GetHasImageOrReference() {
		return hasImageReference_ || hasImage_;
	}

	bool EditorItemBase::GetHasImageReference() {
		return hasImageReference_;
	}

	double EditorItemBase::GetImageReferenceX() {
		return imageReferenceX_;
	}
	double EditorItemBase::GetImageReferenceY() {
		return imageReferenceY_;
	}






	//-----------------------------------------------------------------------------------------------------

	//Sets




	void EditorItemBase::SetTileType(TILETYPE tileType)
	{
		tileType_ = tileType;
	}

	//Set Collision Type
	void EditorItemBase::SetTileTypeProperties(std::shared_ptr<EditorItemBase> &selectedTile)
	{
		tileType_ = selectedTile->GetTileType();
	}



	void EditorItemBase::SetWidth(double x) {
		width_ = x;
	}

	void EditorItemBase::SetHeight(double y) {
		height_ = y;
	}


	void EditorItemBase::SetHasImageReference(bool reference) {
		hasImageReference_ = reference;
	}





	//Seperate all Setting property types for setting tiles to a value
	void EditorItemBase::SetItemBase(std::shared_ptr<EditorItemBase> &itemBase) {


	}



	void EditorItemBase::SetImageBundle(std::shared_ptr<ImageBundle> &imageBundle) {
		imageBundle_ = imageBundle;
		hasImage_ = true;
		width_ = imageBundle->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetWidth();
		height_ = imageBundle->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetHeight();
	}








	void EditorItemBase::SetColor(ALLEGRO_COLOR color) {
		hasColor_ = true;
		chosenColor_ = color;
	}
	void EditorItemBase::SetColorA(float a) {
		hasColor_ = true;
		chosenColor_.a = a;
	}
	void EditorItemBase::SetColorB(float b) {
		hasColor_ = true;
		chosenColor_.b = b;
	}
	void EditorItemBase::SetColorR(float r) {
		hasColor_ = true;
		chosenColor_.r = r;
	}
	void EditorItemBase::SetColorG(float g) {
		hasColor_ = true;
		chosenColor_.g = g;
	}
	void EditorItemBase::SetCurrentPosition(double x, double y) {
		currentPositionX_ = x;
		currentPositionY_ = y;

		imageReferenceX_ = x;
		imageReferenceY_ = y;
	}
	void EditorItemBase::SetCurrentPositionX(double x) {
		currentPositionX_ = x;
		imageReferenceX_ = x;
	}
	void EditorItemBase::SetCurrentPositionY(double y) {
		currentPositionY_ = y;
		imageReferenceY_ = y;
	}

	void EditorItemBase::SetImageSet(AcedSharedDLL::IMAGESETS set) {
		imageSet_ = set;
	}

	void EditorItemBase::SetHasColor(bool hasColor)
	{
		hasColor_ = hasColor;
	}




	//-----------------------------------------------------------------------------------------------------

	//Draws



	//Draws the tiles collision properties
	//Inverts them if necassery
	void EditorItemBase::DrawObjectType(int xOffset, int yOffset, bool invert) {



		ALLEGRO_COLOR newColor;
		newColor.a = 1;
		newColor.r = invert ? !tileCollisionTypeColor_.r : tileCollisionTypeColor_.r;
		newColor.g = invert ? !tileCollisionTypeColor_.g : tileCollisionTypeColor_.g;
		newColor.b = invert ? !tileCollisionTypeColor_.b : tileCollisionTypeColor_.b;

		if (tileType_ == TILETYPE::SOLIDTILE)
		{
			al_draw_rectangle(
				GetCurrentPositionX()*Constants::TileSize() + xOffset + (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				GetCurrentPositionX()*Constants::TileSize() + GetWidth()*Constants::TileSize() + xOffset - (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + GetHeight()*Constants::TileSize() + yOffset - (Constants::TileSize() / 5),
				newColor, 2
			);
		}
		else if (tileType_ == TILETYPE::COLLISIONTOPTILE)
		{
			al_draw_line(
				GetCurrentPositionX()*Constants::TileSize() + xOffset + (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				GetCurrentPositionX()*Constants::TileSize() + GetWidth()*Constants::TileSize() + xOffset - (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				newColor, 2
			);
		}
		else if (tileType_ == TILETYPE::COLLISIONLEFTTILE)
		{
			al_draw_line(
				GetCurrentPositionX()*Constants::TileSize() + xOffset + (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				GetCurrentPositionX()*Constants::TileSize() + xOffset + (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + GetHeight()*Constants::TileSize() + yOffset - (Constants::TileSize() / 5),
				newColor, 2
			);
		}
		else if (tileType_ == TILETYPE::COLLISIONRIGHTTILE)
		{
			al_draw_line(
				GetCurrentPositionX()*Constants::TileSize() + GetWidth()*Constants::TileSize() + xOffset - (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				GetCurrentPositionX()*Constants::TileSize() + GetWidth()*Constants::TileSize() + xOffset - (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + GetHeight()*Constants::TileSize() + yOffset - (Constants::TileSize() / 5),
				newColor, 2
			);
		}
	}





	//Draws the object...Uses the x and y offset from map to draw with displacement
	void EditorItemBase::DrawObject(int xOffset, int yOffset) {
		if (hasImageReference_) {
			return;
		}

		//if object has image and color draw tinting
		if (hasImage_ &&  hasColor_)
		{
			al_draw_tinted_scaled_bitmap(
				imageBundle_->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetImage(),
				chosenColor_,
				0, 0, 
				imageBundle_->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetWidth()*Constants::TileSize(), 
				imageBundle_->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetHeight()*Constants::TileSize(),
				currentPositionX_*Constants::TileSize() + xOffset,
				currentPositionY_*Constants::TileSize() + yOffset,
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
				currentPositionX_*Constants::TileSize() + xOffset,
				currentPositionY_*Constants::TileSize() + yOffset,
				imageBundle_->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetWidth()*Constants::TileSize(),
				imageBundle_->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetHeight()*Constants::TileSize(),
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
	bool EditorItemBase::ClickIntersects(int mouseX, int mouseY)
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
	void EditorItemBase::RemoveAllProperties() {
		hasImageReference_ = false;
		hasImage_ = false;
		hasColor_ = false;
		height_ = 1;
		width_ = 1;
		chosenColor_.r = 1;
		chosenColor_.g = 1;
		chosenColor_.b = 1;
		chosenColor_.a = 0;
		imageBundle_ = nullptr;
		tileType_ = TILETYPE::EMPTYTILE;
		imageReferenceX_ = 0;
		imageReferenceY_ = 0;
	};

	//set flag and set image to null
	void EditorItemBase::RemoveImage() {
		hasImage_ = false;
		hasImageReference_ = false;
		//test this doesnt effect the actual object in imageloader memory dictionary
		imageBundle_ = nullptr;
	};
	//set flag and set color to white
	void EditorItemBase::RemoveColor() {
		hasColor_ = false;
		chosenColor_.r = 1;
		chosenColor_.g = 1;
		chosenColor_.b = 1;
		chosenColor_.a = 0;
	};
}
