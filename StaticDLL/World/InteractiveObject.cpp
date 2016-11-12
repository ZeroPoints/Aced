#include "InteractiveObject.h"


namespace StaticDLL {

	InteractiveObject::InteractiveObject()
	{
		hasImageReference_ = false;
		hasImage_ = false;
		objectType_ = OBJECTTYPES::NA;
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



	StaticDLL::IMAGESETS InteractiveObject::GetImageSet() {
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




	OBJECTTYPES InteractiveObject::GetObjectType() {
		return objectType_;
	}

	ITEMTYPES InteractiveObject::GetItemType() {
		return itemType_;
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
			objectType_ = selectedImage->GetObjectType();
		}
		else {
			hasImage_ = true;
			image_ = selectedImage;
			objectType_ = selectedImage->GetObjectType();
		}
	}



	void InteractiveObject::SetObjectProperties(
		EditorItemBase *selectedObject, bool isReference, int x, int y) {
		SetImage(selectedObject->GetObjectImage(), isReference, x, y);
		SetImageSet(selectedObject->GetImageSet());
	}





	void InteractiveObject::SetImageSet(StaticDLL::IMAGESETS set) {
		imageSet_ = set;
	}

	void InteractiveObject::SetObjectType(OBJECTTYPES set) {
		objectType_ = set;
	}


	void InteractiveObject::SetItemType(ITEMTYPES set) {
		itemType_ = set;
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



	//returns false  if interaction user can walk over object
	bool InteractiveObject::CollisionInteraction(std::vector<Item*> &itemList) {

		switch (objectType_)
		{
		case StaticDLL::OBJECTTYPES::DOOR:
			//if door and holding a key walk throguh the door
			/*for (int i = 0; i < itemList.size(); i++)
			{
				if (itemList[i]->GetItemType() == ITEMTYPES::KEY)
				{
					return false;
				}
			}*/
			return true;
			break;

		default:
			break;
		}


		//return true
		return false;
	}

}
