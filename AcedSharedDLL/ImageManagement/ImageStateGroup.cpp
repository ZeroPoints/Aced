#include "ImageStateGroup.h"



namespace AcedSharedDLL {

	ImageStateGroup::ImageStateGroup(int id) {
		id_ = id;
	}





	ImageStateGroup::~ImageStateGroup()
	{
		/*for (Image* item : imageDictionary_)
		{
			delete item;
			item = nullptr;
		}*/
	}



	//-----------------------------------------------------------------------------------------------------

	//Gets

	std::vector<std::shared_ptr<Image>> &ImageStateGroup::GetImageDictionary()
	{
		return imageDictionary_;
	}



	int ImageStateGroup::GetId()
	{
		return id_;
	}


	//-----------------------------------------------------------------------------------------------------

	//Sets

	void ImageStateGroup::SetImageDictionary(std::vector<std::shared_ptr<Image>> &imageDict)
	{
		imageDictionary_ = imageDict;
	}




	void ImageStateGroup::SetId(int id)
	{
		id_ = id;
	}

}