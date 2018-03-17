#ifndef ASSETLIBRARY_H
#define ASSETLIBRARY_H


/*
No Magic for using allegro in a dll
Cant remember exactly reasoning
*/
#define ALLEGRO_NO_MAGIC_MAIN

/*
Open Source Headers
*/
#include "../../OpenSource/pugixml/pugixml.hpp"

/*
Aced Shared Internal Headers
*/
#include "../Static/Definitions.h"
#include "../ImageManagement/ImageSet.h"

/*
C++ Headers
*/
#include <memory>
#include <vector>

/*
DLL  Exports
*/
#ifdef ACEDSHAREDDLL_EXPORTS
#define ACEDSHAREDDLL_API __declspec(dllexport)
#else
#define ACEDSHAREDDLL_API __declspec(dllimport)
#endif


/*
This DLLS namespace
*/
namespace AcedSharedDLL {

	/*
	Library containing assets for this DLL
	*/
	class AssetLibrary
	{
	public:

		/*
		Asset library for sounds and graphics
		*/
		ACEDSHAREDDLL_API AssetLibrary();

		/*
		Destroy assetlibrary and clean up assets from memory
		*/
		ACEDSHAREDDLL_API ~AssetLibrary();



		/*
		------------------------------------------------------------------------GETS------------------------------------------------------------------------
		*/

		/*
		Gets the full image set dictionary to access images

		TODO(Matt): Check if i really need to return the full imaage set dicitonary. And not pass in a variable to find the dictionary required and return just the imageset/imagebundle required
		*/
		ACEDSHAREDDLL_API std::vector<std::shared_ptr<ImageSet>> &GetImageSetDictionary();




		/*
		------------------------------------------------------------------------SETS------------------------------------------------------------------------
		*/




		/*
		Sets the image dictionary so it can be used through out the project
		*/
		ACEDSHAREDDLL_API void SetImageSetDictionary(std::vector<std::shared_ptr<ImageSet>> &imageDictionary);





		/*
		------------------------------------------------------------------------MISC------------------------------------------------------------------------
		*/




	private:

		//Container for the image dictionary
		std::vector<std::shared_ptr<ImageSet>> imageDictionary_;


	};
}
#endif