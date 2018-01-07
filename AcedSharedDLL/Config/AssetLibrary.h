#ifndef ASSETLIBRARY_H
#define ASSETLIBRARY_H


#define ALLEGRO_NO_MAGIC_MAIN

#include "../../OpenSource/pugixml/pugixml.hpp"
#include "../Static/Definitions.h"
//#include "../LivingEntity/Character.h"
//#include "../World/Map.h"
#include "../ImageManagement/ImageLoader.h"
//#include "../Config/Settings.h"


#ifdef ACEDSHAREDDLL_EXPORTS
#define ACEDSHAREDDLL_API __declspec(dllexport)
#else
#define ACEDSHAREDDLL_API __declspec(dllimport)
#endif



namespace AcedSharedDLL {
	class AssetLibrary
	{
	public:
		ACEDSHAREDDLL_API AssetLibrary();

		ACEDSHAREDDLL_API ~AssetLibrary();



		ACEDSHAREDDLL_API std::vector<ImageSet*> &GetImageSetDictionary();




		//ACEDSHAREDDLL_API Map GetMap() {
		//	return map_;
		//}



		//ACEDSHAREDDLL_API std::vector<Character*> GetEnemyList();


	private:

		//Map map_;

		std::vector<ImageSet*> imageDictionary_;

		//std::vector<Character*> enemyList_;




	};
}
#endif