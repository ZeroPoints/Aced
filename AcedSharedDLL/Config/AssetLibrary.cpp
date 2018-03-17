#include "AssetLibrary.h"



/*
This DLLS namespace
*/
namespace AcedSharedDLL {

	/*
	Asset library for sounds and graphics
	*/
	AssetLibrary::AssetLibrary()
	{
	}

	/*
	Destroy assetlibrary and clean up assets from memory
	*/
	AssetLibrary::~AssetLibrary()
	{
		fprintf(stderr, "An AssetLibrary Disposed\n");
	}







	/*
	------------------------------------------------------------------------GETS------------------------------------------------------------------------
	*/

	/*
	Gets the full image set dictionary to access images

	TODO(Matt): Check if i really need to return the full imaage set dicitonary. And not pass in a variable to find the dictionary required and return just the imageset/imagebundle required
	*/
	std::vector<std::shared_ptr<ImageSet>> &AssetLibrary::GetImageSetDictionary()
	{
		return imageDictionary_;
	}






	/*
	------------------------------------------------------------------------SETS------------------------------------------------------------------------
	*/




	/*
	Sets the image dictionary so it can be used through out the project
	*/
	void AssetLibrary::SetImageSetDictionary(std::vector<std::shared_ptr<ImageSet>> &imageDictionary)
	{
		imageDictionary_ = imageDictionary;
	}







	/*
	------------------------------------------------------------------------MISC------------------------------------------------------------------------
	*/



}