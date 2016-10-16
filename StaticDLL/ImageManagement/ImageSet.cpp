#include "ImageSet.h"



namespace StaticDLL{
	ImageSet::ImageSet(std::vector<Image*> images, EnumDLL::IMAGESETS id){

		imageDictionary_ = images;

		id_ = id;
		

	}



	ImageSet::~ImageSet()
	{
		//fprintf(stderr, "A ImageSet Destructed\n");
		for (Image* item : imageDictionary_)
		{
			delete item;
			item = nullptr;
		}
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