#include "ImageSet.h"



namespace AcedSharedDLL{
	ImageSet::ImageSet(std::vector<ImageBundle*> imageBundle, AcedSharedDLL::IMAGESETS id){

		imageBundleDictionary_ = imageBundle;

		id_ = id;
		

	}



	ImageSet::~ImageSet()
	{
		for (ImageBundle* item : imageBundleDictionary_)
		{
			delete item;
			item = nullptr;
		}
	}


	//-----------------------------------------------------------------------------------------------------

	//Gets


	std::vector<ImageBundle*> ImageSet::GetImageBundleDictionary()
	{
		return imageBundleDictionary_;
	}

	AcedSharedDLL::IMAGESETS ImageSet::GetImageSetId()
	{
		return id_;
	}





	//-----------------------------------------------------------------------------------------------------

	//Sets


	void ImageSet::SetImageSetId(AcedSharedDLL::IMAGESETS id) {
		id_ = id;
	}

	void ImageSet::SetImageBundleDictionary(std::vector<ImageBundle*> imageBundleDictionary)
	{
		imageBundleDictionary_ = imageBundleDictionary;
	}


}