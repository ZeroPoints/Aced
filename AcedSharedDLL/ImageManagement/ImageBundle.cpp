#include "ImageBundle.h"



namespace AcedSharedDLL {

	ImageBundle::ImageBundle(int id) {
		id_ = id;

	}





	ImageBundle::~ImageBundle()
	{
		/*for (ImageStateGroup* item : imageStateGroupDictionary_)
		{
			delete item;
			item = nullptr;
		}*/
	}



	//-----------------------------------------------------------------------------------------------------

	//Gets

	std::vector<std::shared_ptr<ImageStateGroup>> &ImageBundle::GetImageStateGroupDictionary()
	{
		return imageStateGroupDictionary_;
	}



	int ImageBundle::GetId()
	{
		return id_;
	}

	ITEMTYPES ImageBundle::GetItemType() {
		return itemType_;
	}

	OBJECTTYPES ImageBundle::GetObjectType() {
		return objectType_;
	}




	//-----------------------------------------------------------------------------------------------------

	//Sets

	void ImageBundle::SetImageStateGroupDictionary(std::vector<std::shared_ptr<ImageStateGroup>> &imageStateGroupDict)
	{
		imageStateGroupDictionary_ = imageStateGroupDict;
	}



	void ImageBundle::SetId(int id)
	{
		id_ = id;
	}




	void ImageBundle::SetItemType(ITEMTYPES set) {
		itemType_ = set;
	}

	void ImageBundle::SetObjectType(OBJECTTYPES set) {
		objectType_ = set;
	}



}