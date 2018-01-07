#ifndef IMAGELOADER_H
#define IMAGELOADER_H



#include <allegro5\allegro.h>
#include <vector>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes

#include "../AcedSharedDLL/ImageManagement/ImageSet.h"

#include "../OpenSource/pugixml/pugixml.hpp"




class ImageLoader
{
public:
	ImageLoader();






	//-----------------------------------------------------------------------------------------------------

	//Gets


	std::vector<AcedSharedDLL::ImageSet*> GetImageSetDictionary();





	//-----------------------------------------------------------------------------------------------------

	//Misc

	void LoadTiles();
	void LoadPlayers();
	void LoadInteractiveObjects();
	void LoadColors();
	void LoadSystemImages();
	void LoadObjectImages();
	void LoadEnemyImages();
	void LoadItemImages();





private:

	std::vector<AcedSharedDLL::ImageSet*> imageDictionary_;

};


#endif
