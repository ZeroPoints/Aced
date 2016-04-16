#include "Image.h"



namespace StaticDLL{
	Image::Image(int id, const char *file){
		id_ = id;
		
		img_ = al_load_bitmap(file);


	}
}