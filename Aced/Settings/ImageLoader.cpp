

#include "ImageLoader.h"



ImageLoader::ImageLoader(){

	//LoadSystemImages();
		
	LoadTiles();

	LoadColors();

	LoadPlayers();


	LoadObjectImages();


	LoadEnemyImages();


	LoadItemImages();
}






//-----------------------------------------------------------------------------------------------------

//Gets


std::vector<std::shared_ptr<AcedSharedDLL::ImageSet>> &ImageLoader::GetImageSetDictionary()
{
	return imageDictionary_;
}



//-----------------------------------------------------------------------------------------------------

//Misc
//
//
////////Later for when i decide to add system images in to project
//void ImageLoader::LoadSystemImages()
//{
//	pugi::xml_document xmlDoc;
//	auto result = xmlDoc.load_file("..\\Images\\SystemImages.xml");
//	std::vector<std::shared_ptr<AcedSharedDLL::Image>> images;
//	//What happens if file doesnt exist? create one?
//	if(result.status == 0)
//	{
//		pugi::xml_node xmlImages = xmlDoc.child("images");
//		for (pugi::xml_node_iterator it = xmlImages.children().begin(); it != xmlImages.children().end(); it++)
//		{
//			std::shared_ptr<AcedSharedDLL::Image> tempImage = std::shared_ptr<AcedSharedDLL::Image>(new AcedSharedDLL::Image(it->attribute("id").as_int(), it->attribute("file").value(), it->attribute("name").value()));
//			images.push_back(tempImage);
//		}
//	}
//	else if(result.status == 1)
//	{
//		pugi::xml_document xmlNewDoc;	
//		pugi::xml_node xmlTiles = xmlNewDoc.child("images");
//		xmlNewDoc.save_file("..\\Images\\SystemImages.xml");
//	}
//	std::shared_ptr<AcedSharedDLL::ImageSet> imageSet = std::shared_ptr<AcedSharedDLL::ImageSet>(new AcedSharedDLL::ImageSet(images, AcedSharedDLL::IMAGESETS::SYSTEMIMAGESET));
//	imageDictionary_.push_back(imageSet);
//}
//



void ImageLoader::LoadTiles()
{
	pugi::xml_document xmlDoc;

	auto result = xmlDoc.load_file("..\\Images\\TileImageList.xml");
	//What happens if file doesnt exist? create one?

	std::vector<std::shared_ptr<AcedSharedDLL::ImageBundle>> imageBundleList;


	if (result.status == 0)
	{
		pugi::xml_node xmlImageSet = xmlDoc.child("ImageSet");
		for (pugi::xml_node_iterator xmlImageBundleIterator = xmlImageSet.children().begin(); xmlImageBundleIterator != xmlImageSet.children().end(); xmlImageBundleIterator++)
		{
			std::shared_ptr<AcedSharedDLL::ImageBundle> imageBundle(new AcedSharedDLL::ImageBundle(xmlImageBundleIterator->attribute("id").as_int()));
			std::vector<std::shared_ptr<AcedSharedDLL::ImageStateGroup>> imageStateGroupList;
			for (pugi::xml_node_iterator xmlImageStateGroupIterator = xmlImageBundleIterator->children().begin(); xmlImageStateGroupIterator != xmlImageBundleIterator->children().end(); xmlImageStateGroupIterator++)
			{
				std::shared_ptr<AcedSharedDLL::ImageStateGroup> imageStateGroup(new AcedSharedDLL::ImageStateGroup(xmlImageStateGroupIterator->attribute("id").as_int()));
				std::vector<std::shared_ptr<AcedSharedDLL::Image>> images;
				for (pugi::xml_node_iterator xmlImagesIterator = xmlImageStateGroupIterator->children().begin(); xmlImagesIterator != xmlImageStateGroupIterator->children().end(); xmlImagesIterator++)
				{
					std::shared_ptr<AcedSharedDLL::Image> tempImage(new AcedSharedDLL::Image(xmlImagesIterator->attribute("id").as_int(), xmlImagesIterator->attribute("file").value()));
					images.push_back(tempImage);
				}
				imageStateGroup->SetImageDictionary(images);
				imageStateGroupList.push_back(imageStateGroup);
			}
			imageBundle->SetImageStateGroupDictionary(imageStateGroupList);
			imageBundleList.push_back(imageBundle);
		}
	}
	else if (result.status == 1)
	{
		pugi::xml_document xmlNewDoc;
		pugi::xml_node xmlTiles = xmlNewDoc.child("ImageSet");
		xmlNewDoc.save_file("..\\Images\\TileImageList.xml");
	}


	std::shared_ptr<AcedSharedDLL::ImageSet> imageSet(new AcedSharedDLL::ImageSet(imageBundleList, AcedSharedDLL::IMAGESETS::TILEIMAGESET));
	imageDictionary_.push_back(imageSet);
}





void ImageLoader::LoadColors()
{
	pugi::xml_document xmlDoc;
	auto result = xmlDoc.load_file("..\\Images\\TileColorList.xml");
	std::vector<std::shared_ptr<AcedSharedDLL::ImageStateGroup>> imageGroupList;

	//What happens if file doesnt exist? create one?
	if (result.status == 0)
	{
		pugi::xml_node xmlImages = xmlDoc.child("colors");
		int i = 0;
		for (pugi::xml_node_iterator it = xmlImages.children().begin(); it != xmlImages.children().end(); it++)
		{
			std::shared_ptr<AcedSharedDLL::ImageStateGroup> imageStateGroup = std::shared_ptr<AcedSharedDLL::ImageStateGroup>(new AcedSharedDLL::ImageStateGroup(it->attribute("id").as_int()));
			std::vector<std::shared_ptr<AcedSharedDLL::Image>> images;
			std::shared_ptr<AcedSharedDLL::Image> tempImage;
			if (i == 0)
			{
				tempImage = std::shared_ptr<AcedSharedDLL::Image>(new AcedSharedDLL::Image(it->attribute("id").as_int(), it->attribute("file").value()));
				i++;
			}
			else
			{
				tempImage = std::shared_ptr<AcedSharedDLL::Image>(new AcedSharedDLL::Image(it->attribute("id").as_int(), it->attribute("r").as_float(), it->attribute("g").as_float(), it->attribute("b").as_float()));
			}
			images.push_back(tempImage);
			//sort out if this is pointer or new instance...
			imageStateGroup->SetImageDictionary(images);

			imageGroupList.push_back(imageStateGroup);
		}

	}

	std::shared_ptr<AcedSharedDLL::ImageBundle> imageBundle = std::shared_ptr<AcedSharedDLL::ImageBundle>(new AcedSharedDLL::ImageBundle(0));
	imageBundle->SetImageStateGroupDictionary(imageGroupList);

	std::vector<std::shared_ptr<AcedSharedDLL::ImageBundle>> imageBundleList;
	imageBundleList.push_back(imageBundle);

	std::shared_ptr<AcedSharedDLL::ImageSet> imageSet = std::shared_ptr<AcedSharedDLL::ImageSet>(new AcedSharedDLL::ImageSet(imageBundleList, AcedSharedDLL::IMAGESETS::TILECOLORSET));
	imageDictionary_.push_back(imageSet);

}




void ImageLoader::LoadPlayers()
{
	pugi::xml_document xmlDoc;
	auto result = xmlDoc.load_file("..\\Images\\PlayersImageList.xml");
	std::vector<std::shared_ptr<AcedSharedDLL::ImageBundle>> imageBundleList;
	//What happens if file doesnt exist? create one?
	if (result.status == 0)
	{
		pugi::xml_node xmlImageSet = xmlDoc.child("ImageSet");
		for (pugi::xml_node_iterator xmlImageBundleIterator = xmlImageSet.children().begin(); xmlImageBundleIterator != xmlImageSet.children().end(); xmlImageBundleIterator++)
		{
			std::shared_ptr<AcedSharedDLL::ImageBundle> imageBundle( new AcedSharedDLL::ImageBundle(xmlImageBundleIterator->attribute("id").as_int()));
			std::vector<std::shared_ptr<AcedSharedDLL::ImageStateGroup>> imageStateGroupList;
			for (pugi::xml_node_iterator xmlImageStateGroupIterator = xmlImageBundleIterator->children().begin(); xmlImageStateGroupIterator != xmlImageBundleIterator->children().end(); xmlImageStateGroupIterator++)
			{
				std::shared_ptr<AcedSharedDLL::ImageStateGroup> imageStateGroup( new AcedSharedDLL::ImageStateGroup(xmlImageStateGroupIterator->attribute("id").as_int()));
				std::vector<std::shared_ptr<AcedSharedDLL::Image>> images;
				for (pugi::xml_node_iterator xmlImagesIterator = xmlImageStateGroupIterator->children().begin(); xmlImagesIterator != xmlImageStateGroupIterator->children().end(); xmlImagesIterator++)
				{
					std::shared_ptr<AcedSharedDLL::Image> tempImage(new AcedSharedDLL::Image(xmlImagesIterator->attribute("id").as_int(), xmlImagesIterator->attribute("file").value()));
					images.push_back(tempImage);
				}
				imageStateGroup->SetImageDictionary(images);
				imageStateGroupList.push_back(imageStateGroup);
			}
			imageBundle->SetImageStateGroupDictionary(imageStateGroupList);
			imageBundleList.push_back(imageBundle);
		}
	}
	else if (result.status == 1)
	{
		pugi::xml_document xmlNewDoc;
		pugi::xml_node xmlTiles = xmlNewDoc.child("player");
		xmlNewDoc.save_file("..\\Images\\PlayersImageList.xml");
	}


	std::shared_ptr<AcedSharedDLL::ImageSet> imageSet(new AcedSharedDLL::ImageSet(imageBundleList, AcedSharedDLL::IMAGESETS::PLAYERIMAGESET));
	imageDictionary_.push_back(imageSet);
}









void ImageLoader::LoadObjectImages()
{
	pugi::xml_document xmlDoc;
	auto result = xmlDoc.load_file("..\\Images\\ObjectImageList.xml");
	std::vector<std::shared_ptr<AcedSharedDLL::ImageBundle>> imageBundleList;
	//What happens if file doesnt exist? create one?
	if (result.status == 0)
	{
		pugi::xml_node xmlImageSet = xmlDoc.child("ImageSet");
		for (pugi::xml_node_iterator xmlImageBundleIterator = xmlImageSet.children().begin(); xmlImageBundleIterator != xmlImageSet.children().end(); xmlImageBundleIterator++)
		{
			std::shared_ptr<AcedSharedDLL::ImageBundle> imageBundle(new AcedSharedDLL::ImageBundle(xmlImageBundleIterator->attribute("id").as_int()));
			imageBundle->SetObjectType((AcedSharedDLL::OBJECTTYPES)xmlImageBundleIterator->attribute("objecttype").as_int());
			std::vector<std::shared_ptr<AcedSharedDLL::ImageStateGroup>> imageStateGroupList;
			for (pugi::xml_node_iterator xmlImageStateGroupIterator = xmlImageBundleIterator->children().begin(); xmlImageStateGroupIterator != xmlImageBundleIterator->children().end(); xmlImageStateGroupIterator++)
			{
				std::shared_ptr<AcedSharedDLL::ImageStateGroup> imageStateGroup(new AcedSharedDLL::ImageStateGroup(xmlImageStateGroupIterator->attribute("id").as_int()));
				std::vector<std::shared_ptr<AcedSharedDLL::Image>> images;
				for (pugi::xml_node_iterator xmlImagesIterator = xmlImageStateGroupIterator->children().begin(); xmlImagesIterator != xmlImageStateGroupIterator->children().end(); xmlImagesIterator++)
				{
					std::shared_ptr<AcedSharedDLL::Image> tempImage(new AcedSharedDLL::Image(xmlImagesIterator->attribute("id").as_int(), xmlImagesIterator->attribute("file").value()));
					images.push_back(tempImage);
				}
				imageStateGroup->SetImageDictionary(images);
				imageStateGroupList.push_back(imageStateGroup);
			}
			imageBundle->SetImageStateGroupDictionary(imageStateGroupList);
			imageBundleList.push_back(imageBundle);
		}
	}
	else if (result.status == 1)
	{
		pugi::xml_document xmlNewDoc;
		pugi::xml_node xmlTiles = xmlNewDoc.child("object");
		xmlNewDoc.save_file("..\\Images\\ObjectImageList.xml");
	}

	std::shared_ptr<AcedSharedDLL::ImageSet> imageSet(new AcedSharedDLL::ImageSet(imageBundleList, AcedSharedDLL::IMAGESETS::OBJECTIMAGESET));
	imageDictionary_.push_back(imageSet);
}




void ImageLoader::LoadEnemyImages()
{
	pugi::xml_document xmlDoc;
	auto result = xmlDoc.load_file("..\\Images\\EnemyImageList.xml");
	std::vector<std::shared_ptr<AcedSharedDLL::ImageBundle>> imageBundleList;
	//What happens if file doesnt exist? create one?
	if (result.status == 0)
	{
		pugi::xml_node xmlImageSet = xmlDoc.child("ImageSet");
		for (pugi::xml_node_iterator xmlImageBundleIterator = xmlImageSet.children().begin(); xmlImageBundleIterator != xmlImageSet.children().end(); xmlImageBundleIterator++)
		{
			std::shared_ptr<AcedSharedDLL::ImageBundle> imageBundle(new AcedSharedDLL::ImageBundle(xmlImageBundleIterator->attribute("id").as_int()));
			std::vector<std::shared_ptr<AcedSharedDLL::ImageStateGroup>> imageStateGroupList;
			for (pugi::xml_node_iterator xmlImageStateGroupIterator = xmlImageBundleIterator->children().begin(); xmlImageStateGroupIterator != xmlImageBundleIterator->children().end(); xmlImageStateGroupIterator++)
			{
				std::shared_ptr<AcedSharedDLL::ImageStateGroup> imageStateGroup(new AcedSharedDLL::ImageStateGroup(xmlImageStateGroupIterator->attribute("id").as_int()));
				std::vector<std::shared_ptr<AcedSharedDLL::Image>> images;
				for (pugi::xml_node_iterator xmlImagesIterator = xmlImageStateGroupIterator->children().begin(); xmlImagesIterator != xmlImageStateGroupIterator->children().end(); xmlImagesIterator++)
				{
					std::shared_ptr<AcedSharedDLL::Image> tempImage(new AcedSharedDLL::Image(xmlImagesIterator->attribute("id").as_int(), xmlImagesIterator->attribute("file").value()));
					images.push_back(tempImage);
				}
				imageStateGroup->SetImageDictionary(images);
				imageStateGroupList.push_back(imageStateGroup);
			}
			imageBundle->SetImageStateGroupDictionary(imageStateGroupList);
			imageBundleList.push_back(imageBundle);
		}
	}
	else if (result.status == 1)
	{
		pugi::xml_document xmlNewDoc;
		pugi::xml_node xmlTiles = xmlNewDoc.child("enemy");
		xmlNewDoc.save_file("..\\Images\\EnemyImageList.xml");
	}


	std::shared_ptr<AcedSharedDLL::ImageSet> imageSet(new AcedSharedDLL::ImageSet(imageBundleList, AcedSharedDLL::IMAGESETS::ENEMYIMAGESET));
	imageDictionary_.push_back(imageSet);
}





void ImageLoader::LoadItemImages()
{
	pugi::xml_document xmlDoc;
	auto result = xmlDoc.load_file("..\\Images\\ItemImageList.xml");
	std::vector<std::shared_ptr<AcedSharedDLL::ImageBundle>> imageBundleList;
	//What happens if file doesnt exist? create one?
	if (result.status == 0)
	{
		pugi::xml_node xmlImageSet = xmlDoc.child("ImageSet");
		for (pugi::xml_node_iterator xmlImageBundleIterator = xmlImageSet.children().begin(); xmlImageBundleIterator != xmlImageSet.children().end(); xmlImageBundleIterator++)
		{
			std::shared_ptr<AcedSharedDLL::ImageBundle> imageBundle( new AcedSharedDLL::ImageBundle(xmlImageBundleIterator->attribute("id").as_int()));
			imageBundle->SetItemType((AcedSharedDLL::ITEMTYPES)xmlImageBundleIterator->attribute("itemtype").as_int());
			std::vector<std::shared_ptr<AcedSharedDLL::ImageStateGroup>> imageStateGroupList;
			for (pugi::xml_node_iterator xmlImageStateGroupIterator = xmlImageBundleIterator->children().begin(); xmlImageStateGroupIterator != xmlImageBundleIterator->children().end(); xmlImageStateGroupIterator++)
			{
				std::shared_ptr<AcedSharedDLL::ImageStateGroup> imageStateGroup(new AcedSharedDLL::ImageStateGroup(xmlImageStateGroupIterator->attribute("id").as_int()));
				std::vector<std::shared_ptr<AcedSharedDLL::Image>> images;
				for (pugi::xml_node_iterator xmlImagesIterator = xmlImageStateGroupIterator->children().begin(); xmlImagesIterator != xmlImageStateGroupIterator->children().end(); xmlImagesIterator++)
				{
					std::shared_ptr<AcedSharedDLL::Image> tempImage(new AcedSharedDLL::Image(xmlImagesIterator->attribute("id").as_int(), xmlImagesIterator->attribute("file").value()));
					images.push_back(tempImage);
				}
				imageStateGroup->SetImageDictionary(images);
				imageStateGroupList.push_back(imageStateGroup);
			}
			imageBundle->SetImageStateGroupDictionary(imageStateGroupList);
			imageBundleList.push_back(imageBundle);
		}
	}
	else if (result.status == 1)
	{
		pugi::xml_document xmlNewDoc;
		pugi::xml_node xmlTiles = xmlNewDoc.child("item");
		xmlNewDoc.save_file("..\\Images\\ItemImageList.xml");
	}



	std::shared_ptr<AcedSharedDLL::ImageSet> imageSet(new AcedSharedDLL::ImageSet(imageBundleList, AcedSharedDLL::IMAGESETS::ITEMIMAGESET));
	imageDictionary_.push_back(imageSet);
}





