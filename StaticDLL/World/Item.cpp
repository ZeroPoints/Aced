#include "Item.h"


namespace StaticDLL {

	Item::Item()
	{
		hasImageReference_ = false;
		hasImage_ = false;
		itemType_ = ITEMTYPES::NA;
	}


	Item::~Item()
	{
		//fprintf(stderr, "A InteractiveObject Destructed\n");
	}







	//-----------------------------------------------------------------------------------------------------

	//Gets






	Image *Item::GetObjectImage()
	{
		return image_;
	}



	StaticDLL::IMAGESETS Item::GetImageSet() {
		return imageSet_;
	}


	bool Item::GetHasImage() {
		return hasImageReference_ || hasImage_;
	}

	bool Item::GetHasImageReference() {
		return hasImageReference_;
	}

	double Item::GetImageReferenceX() {
		return imageReferenceX_;
	}
	double Item::GetImageReferenceY() {
		return imageReferenceY_;
	}





	double Item::GetPosX() {
		return currentPositionX_;
	}


	double Item::GetPosY() {
		return currentPositionY_;
	}

	ITEMTYPES Item::GetItemType() {
		return itemType_;
	}

	OBJECTTYPES Item::GetObjectType() {
		return objectType_;
	}


	//-----------------------------------------------------------------------------------------------------

	//Sets






	void Item::SetImage(
		Image *selectedImage, bool isReference, int x, int y) {
		imageReferenceX_ = x;
		imageReferenceY_ = y;
		if (isReference) {
			hasImageReference_ = true;
			image_ = selectedImage;
			itemType_ = selectedImage->GetItemType();
		}
		else {
			hasImage_ = true;
			image_ = selectedImage;
			itemType_ = selectedImage->GetItemType();
		}
	}



	void Item::SetObjectProperties(
		EditorItemBase *selectedObject, bool isReference, int x, int y) {
		SetImage(selectedObject->GetObjectImage(), isReference, x, y);
		SetImageSet(selectedObject->GetImageSet());
	}





	void Item::SetImageSet(StaticDLL::IMAGESETS set) {
		imageSet_ = set;
	}



	void Item::SetPosX(double x) {
		currentPositionX_ = x;
	}

	void Item::SetPosY(double y) {
		currentPositionY_ = y;
	}

	void Item::SetItemType(ITEMTYPES set) {
		itemType_ = set;
	}

	void Item::SetObjectType(OBJECTTYPES set) {
		objectType_ = set;
	}







	//-----------------------------------------------------------------------------------------------------

	//Draws









	//Draws the object...Uses the x and y offset from map to draw with displacement
	void Item::DrawObject(int xOffset, int yOffset) {
		if (hasImageReference_) {
			return;
		}

		if (hasImage_)
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
	};














	//-----------------------------------------------------------------------------------------------------

	//MISC


	void Item::RemoveAllProperties() {
		hasImageReference_ = false;
		hasImage_ = false;
		image_ = nullptr;
		imageReferenceX_ = 0;
		imageReferenceY_ = 0;
	};

	//set flag and set image to null
	void Item::RemoveImage() {
		hasImage_ = false;
		hasImageReference_ = false;
		//test this doesnt effect the actual object in imageloader memory dictionary
		image_ = nullptr;
	};
}
