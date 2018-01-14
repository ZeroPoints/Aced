#include "AssetLibrary.h"



namespace AcedSharedDLL {
	 AssetLibrary::AssetLibrary()
	 {
		 std::shared_ptr<ImageLoader> loader(new ImageLoader());

		 imageDictionary_ = loader->GetImageSetDictionary();


		 //map_ = Map(&settings, display, &imageDictionary_);



		 auto test = 0;
		 /*imageDictionary_.push_back(ImageLoader::LoadCharacters());
		imageDictionary_.push_back(ImageLoader::LoadColors());
		imageDictionary_.push_back(ImageLoader::LoadObjectImages());
		imageDictionary_.push_back(ImageLoader::LoadPlayers());
		imageDictionary_.push_back(ImageLoader::LoadTiles());*/

		//map_ = Map();

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











}