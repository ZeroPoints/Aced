#include "InteractiveObject.h"


namespace StaticDLL {

	InteractiveObject::InteractiveObject()
	{
		hasImageReference_ = false;
		hasImage_ = false;
	}


	InteractiveObject::~InteractiveObject()
	{
		//fprintf(stderr, "A InteractiveObject Destructed\n");
	}







	//-----------------------------------------------------------------------------------------------------

	//Gets






	Image *InteractiveObject::GetObjectImage()
	{
		return image_;
	}



	EnumDLL::IMAGESETS InteractiveObject::GetImageSet() {
		return imageSet_;
	}

	bool InteractiveObject::GetHasImage() {
		return hasImageReference_ || hasImage_;
	}

	bool InteractiveObject::GetHasImageReference() {
		return hasImageReference_;
	}

	double InteractiveObject::GetImageReferenceX() {
		return imageReferenceX_;
	}
	double InteractiveObject::GetImageReferenceY() {
		return imageReferenceY_;
	}






	//-----------------------------------------------------------------------------------------------------

	//Sets






	void InteractiveObject::SetImage(
		Image *selectedImage, bool isReference, int x, int y) {
		imageReferenceX_ = x;
		imageReferenceY_ = y;
		if (isReference) {
			hasImageReference_ = true;
			image_ = selectedImage;
		}
		else {
			hasImage_ = true;
			image_ = selectedImage;
		}
	}



	void InteractiveObject::SetObjectProperties(
		EditorItemBase *selectedObject, bool isReference, int x, int y) {
		SetImage(selectedObject->GetObjectImage(), isReference, x, y);
		SetImageSet(selectedObject->GetImageSet());
	}





	void InteractiveObject::SetImageSet(EnumDLL::IMAGESETS set) {
		imageSet_ = set;
	}





	//-----------------------------------------------------------------------------------------------------

	//Draws









	//Draws the object...Uses the x and y offset from map to draw with displacement
	void InteractiveObject::DrawObject(double currentPositionX, double currentPositionY, int xOffset, int yOffset) {
		if (hasImageReference_) {
			return;
		}

		if (hasImage_)
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
	};














	//-----------------------------------------------------------------------------------------------------

	//MISC


	void InteractiveObject::RemoveAllProperties() {
		hasImageReference_ = false;
		hasImage_ = false;
		image_ = nullptr;
		imageReferenceX_ = 0;
		imageReferenceY_ = 0;
	};

	//set flag and set image to null
	void InteractiveObject::RemoveImage() {
		hasImage_ = false;
		hasImageReference_ = false;
		//test this doesnt effect the actual object in imageloader memory dictionary
		image_ = nullptr;
	};
}
