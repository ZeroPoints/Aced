#include "Image.h"



namespace StaticDLL{
	Image::Image(int id, const char *file){
		id_ = id;
		
		img_ = al_load_bitmap(file);

		width_ = al_get_bitmap_width(img_);
		height_ = al_get_bitmap_height(img_);
	}
}