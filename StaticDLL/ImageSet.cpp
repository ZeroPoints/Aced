#include "ImageSet.h"



namespace StaticDLL{
	ImageSet::ImageSet(std::vector<Image*> images, EnumDLL::IMAGESETS id){

		imageDictionary_ = images;

		id_ = id;
		

	}



}