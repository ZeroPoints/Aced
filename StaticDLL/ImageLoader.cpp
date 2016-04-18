#include "ImageLoader.h"



namespace StaticDLL{
	ImageLoader::ImageLoader(){

		
		LoadTiles();


		LoadPlayers();

	}




	void ImageLoader::LoadTiles()
	{
		pugi::xml_document xmlDoc;
		auto result = xmlDoc.load_file("..\\Images\\TileImageList.xml");
		std::vector<Image*> images;
		//What happens if file doesnt exist? create one?
		if(result.status == 0)
		{
			pugi::xml_node xmlImages = xmlDoc.child("tiles");
			for (pugi::xml_node_iterator it = xmlImages.children().begin(); it != xmlImages.children().end(); it++)
			{
				Image* tempImage = new Image(it->attribute("id").as_int(), it->attribute("file").value());
				images.push_back(tempImage);
			}
		}
		else if(result.status == 1)
		{
			pugi::xml_document xmlNewDoc;	
			pugi::xml_node xmlTiles = xmlNewDoc.child("tiles");
			xmlNewDoc.save_file("..\\Images\\TileImageList.xml");
		}
		ImageSet* imageSet = new ImageSet(images, EnumDLL::IMAGESETS::TILEIMAGESET);
		imageDictionary_.push_back(imageSet);
	}






	void ImageLoader::LoadPlayers()
	{
		pugi::xml_document xmlDoc;
		auto result = xmlDoc.load_file("..\\Images\\PlayersImageList.xml");
		std::vector<Image*> images;
		//What happens if file doesnt exist? create one?
		if(result.status == 0)
		{
			pugi::xml_node xmlImages = xmlDoc.child("player");
			for (pugi::xml_node_iterator it = xmlImages.children().begin(); it != xmlImages.children().end(); it++)
			{
				Image* tempImage = new Image(it->attribute("id").as_int(), it->attribute("file").value());
				images.push_back(tempImage);
			}
		}
		else if(result.status == 1)
		{
			pugi::xml_document xmlNewDoc;	
			pugi::xml_node xmlTiles = xmlNewDoc.child("player");
			xmlNewDoc.save_file("..\\Images\\PlayersImageList.xml");
		}
		ImageSet* imageSet = new ImageSet(images, EnumDLL::IMAGESETS::PLAYERIMAGESET);
		imageDictionary_.push_back(imageSet);
	}
}