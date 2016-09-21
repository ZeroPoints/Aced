#ifndef ASSETLIBRARY_H
#define ASSETLIBRARY_H


#define ALLEGRO_NO_MAGIC_MAIN

#include "../../OpenSource/pugixml/pugixml.hpp"
#include "../Static/Definitions.h"
//#include "../LivingEntity/Character.h"
//#include "../World/Map.h"
#include "../ImageManagement/ImageLoader.h"
//#include "../Config/Settings.h"




#ifdef STATICDLL_EXPORTS
#define STATICDLL_API __declspec(dllexport)
#else
#define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL {
	class AssetLibrary
	{
	public:
		STATICDLL_API AssetLibrary();




		STATICDLL_API std::vector<ImageSet*> &GetImageSetDictionary();




		//STATICDLL_API Map GetMap() {
		//	return map_;
		//}



		//STATICDLL_API std::vector<Character*> GetEnemyList();


	private:

		//Map map_;

		std::vector<ImageSet*> imageDictionary_;

		//std::vector<Character*> enemyList_;




	};
}
#endif