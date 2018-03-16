#include "AssetLibrary.h"



namespace AcedSharedDLL {
	 AssetLibrary::AssetLibrary()
	{
	}



	 AssetLibrary::~AssetLibrary()
	 {
		 //fprintf(stderr, "A Image Destructed\n");
		 /*for (ImageSet* item : imageDictionary_)
		 {
			 delete item;
			 item = nullptr;
		 }*/
	 }



	
	 

	std::vector<std::shared_ptr<ImageSet>> &AssetLibrary::GetImageSetDictionary()
	{
		return imageDictionary_;
	}




	void AssetLibrary::SetImageSetDictionary(std::vector<std::shared_ptr<ImageSet>> &imageDictionary)
	{
		imageDictionary_ = imageDictionary;
	}









}