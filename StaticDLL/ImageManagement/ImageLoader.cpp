#include "ImageLoader.h"



namespace StaticDLL{
	ImageLoader::ImageLoader(){

		//LoadSystemImages();
		
		LoadTiles();

		LoadColors();

		LoadPlayers();


		LoadObjectImages();


		LoadEnemyImages();

	}






	//-----------------------------------------------------------------------------------------------------

	//Gets


	std::vector<ImageSet*> ImageLoader::GetImageSetDictionary()
	{
		return imageDictionary_;
	}



	//-----------------------------------------------------------------------------------------------------

	//Misc


	//Later for when i decide to add system images in to project
	//void ImageLoader::LoadSystemImages()
	//{
	//	pugi::xml_document xmlDoc;
	//	auto result = xmlDoc.load_file("..\\Images\\SystemImages.xml");
	//	std::vector<Image*> images;
	//	//What happens if file doesnt exist? create one?
	//	if(result.status == 0)
	//	{
	//		pugi::xml_node xmlImages = xmlDoc.child("images");
	//		for (pugi::xml_node_iterator it = xmlImages.children().begin(); it != xmlImages.children().end(); it++)
	//		{
	//			Image* tempImage = new Image(it->attribute("id").as_int(), it->attribute("file").value(), it->attribute("name").value());
	//			images.push_back(tempImage);
	//		}
	//	}
	//	else if(result.status == 1)
	//	{
	//		pugi::xml_document xmlNewDoc;	
	//		pugi::xml_node xmlTiles = xmlNewDoc.child("images");
	//		xmlNewDoc.save_file("..\\Images\\SystemImages.xml");
	//	}
	//	ImageSet* imageSet = new ImageSet(images, EnumDLL::IMAGESETS::SYSTEMIMAGESET);
	//	imageDictionary_.push_back(imageSet);
	//}




	void ImageLoader::LoadTiles()
	{
		pugi::xml_document xmlDoc;
		auto result = xmlDoc.load_file("..\\Images\\TileImageList.xml");
		std::vector<Image*> images;
		//What happens if file doesnt exist? create one?
		if (result.status == 0)
		{
			pugi::xml_node xmlImages = xmlDoc.child("tiles");
			for (pugi::xml_node_iterator it = xmlImages.children().begin(); it != xmlImages.children().end(); it++)
			{
				Image* tempImage = new Image(it->attribute("id").as_int(), it->attribute("file").value());
				images.push_back(tempImage);
			}
		}
		else if (result.status == 1)
		{
			pugi::xml_document xmlNewDoc;
			pugi::xml_node xmlTiles = xmlNewDoc.child("tiles");
			xmlNewDoc.save_file("..\\Images\\TileImageList.xml");
		}
		ImageSet* imageSet = new ImageSet(images, EnumDLL::IMAGESETS::TILEIMAGESET);
		imageDictionary_.push_back(imageSet);
	}





	void ImageLoader::LoadColors()
	{
		pugi::xml_document xmlDoc;
		auto result = xmlDoc.load_file("..\\Images\\TileColorList.xml");
		std::vector<Image*> images;
		//What happens if file doesnt exist? create one?
		if (result.status == 0)
		{
			pugi::xml_node xmlImages = xmlDoc.child("colors");
			int i = 0;
			for (pugi::xml_node_iterator it = xmlImages.children().begin(); it != xmlImages.children().end(); it++)
			{
				Image* tempImage;
				if (i == 0)
				{
					tempImage = new Image(it->attribute("id").as_int(), it->attribute("file").value());
					i++;
				}
				else
				{
					tempImage = new Image(it->attribute("id").as_int(), it->attribute("r").as_float(), it->attribute("g").as_float(), it->attribute("b").as_float());
				}
				images.push_back(tempImage);
			}
		}

		ImageSet* imageSet = new ImageSet(images, EnumDLL::IMAGESETS::TILECOLORSET);
		imageDictionary_.push_back(imageSet);
	}




	void ImageLoader::LoadPlayers()
	{
		pugi::xml_document xmlDoc;
		auto result = xmlDoc.load_file("..\\Images\\PlayersImageList.xml");
		std::vector<Image*> images;
		//What happens if file doesnt exist? create one?
		if (result.status == 0)
		{
			pugi::xml_node xmlImages = xmlDoc.child("player");
			for (pugi::xml_node_iterator it = xmlImages.children().begin(); it != xmlImages.children().end(); it++)
			{
				Image* tempImage = new Image(it->attribute("id").as_int(), it->attribute("file").value());
				images.push_back(tempImage);
			}
		}
		else if (result.status == 1)
		{
			pugi::xml_document xmlNewDoc;
			pugi::xml_node xmlTiles = xmlNewDoc.child("player");
			xmlNewDoc.save_file("..\\Images\\PlayersImageList.xml");
		}
		ImageSet* imageSet = new ImageSet(images, EnumDLL::IMAGESETS::PLAYERIMAGESET);
		imageDictionary_.push_back(imageSet);
	}









	void ImageLoader::LoadObjectImages()
	{
		pugi::xml_document xmlDoc;
		auto result = xmlDoc.load_file("..\\Images\\ObjectImageList.xml");
		std::vector<Image*> images;
		//What happens if file doesnt exist? create one?
		if (result.status == 0)
		{
			pugi::xml_node xmlImages = xmlDoc.child("tiles");
			for (pugi::xml_node_iterator it = xmlImages.children().begin(); it != xmlImages.children().end(); it++)
			{
				Image* tempImage = new Image(it->attribute("id").as_int(), it->attribute("file").value());
				images.push_back(tempImage);
			}
		}
		else if (result.status == 1)
		{
			pugi::xml_document xmlNewDoc;
			pugi::xml_node xmlTiles = xmlNewDoc.child("tiles");
			xmlNewDoc.save_file("..\\Images\\ObjectImageList.xml");
		}
		ImageSet* imageSet = new ImageSet(images, EnumDLL::IMAGESETS::OBJECTIMAGESET);
		imageDictionary_.push_back(imageSet);
	}




	void ImageLoader::LoadEnemyImages()
	{
		pugi::xml_document xmlDoc;
		auto result = xmlDoc.load_file("..\\Images\\EnemyImageList.xml");
		std::vector<Image*> images;
		//What happens if file doesnt exist? create one?
		if (result.status == 0)
		{
			pugi::xml_node xmlImages = xmlDoc.child("enemy");
			for (pugi::xml_node_iterator it = xmlImages.children().begin(); it != xmlImages.children().end(); it++)
			{
				Image* tempImage = new Image(it->attribute("id").as_int(), it->attribute("file").value());
				images.push_back(tempImage);
			}
		}
		else if (result.status == 1)
		{
			pugi::xml_document xmlNewDoc;
			pugi::xml_node xmlTiles = xmlNewDoc.child("enemy");
			xmlNewDoc.save_file("..\\Images\\EnemyImageList.xml");
		}
		ImageSet* imageSet = new ImageSet(images, EnumDLL::IMAGESETS::ENEMYIMAGESET);
		imageDictionary_.push_back(imageSet);
	}


}