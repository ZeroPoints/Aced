#include "ImageSet.h"



namespace StaticDLL{
	ImageSet::ImageSet(std::vector<Image*> images, EnumDLL::IMAGESETS id){

		imageDictionary_ = images;

		id_ = id;
		

	}



	std::vector<Image*> ImageSet::GetImageDictionary()
	{
		return imageDictionary_;
	}

	EnumDLL::IMAGESETS ImageSet::GetImageSetId()
	{
		return id_;
	}
}