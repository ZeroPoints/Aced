#include "AssetLibrary.h"



namespace StaticDLL {
	 AssetLibrary::AssetLibrary()
	 {
		 ImageLoader loader = ImageLoader();

		 imageDictionary_ = loader.GetImageSetDictionary();


		 //map_ = Map(&settings, display, &imageDictionary_);



		 auto test = 0;
		 /*imageDictionary_.push_back(ImageLoader::LoadCharacters());
		imageDictionary_.push_back(ImageLoader::LoadColors());
		imageDictionary_.push_back(ImageLoader::LoadObjectImages());
		imageDictionary_.push_back(ImageLoader::LoadPlayers());
		imageDictionary_.push_back(ImageLoader::LoadTiles());*/

		//map_ = Map();

	}


	 

	std::vector<ImageSet*> &AssetLibrary::GetImageSetDictionary()
	{
		return imageDictionary_;
	}











}