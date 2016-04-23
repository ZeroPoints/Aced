#include "Image.h"



namespace StaticDLL{

	//SET DEFAULT COLOR FOR THESE TO WHITE
	//use al tinted draw all the time
	Image::Image(int id, const char *file){
		id_ = id;
		
		img_ = al_load_bitmap(file);


		width_ = al_get_bitmap_width(img_);
		height_ = al_get_bitmap_height(img_);
	}



	Image::Image(int id, const char *file, const char *name){
		id_ = id;
		

		name_ = (char*)malloc(strlen(name)+1);
		strcpy(name_, name);

		img_ = al_load_bitmap(file);

		width_ = al_get_bitmap_width(img_);
		height_ = al_get_bitmap_height(img_);
	}


	Image::Image(int id, const char *file, float r, float g, float b){
		id_ = id;
		
		img_ = al_load_bitmap(file);
		color_ = al_map_rgb_f(r,g,b);

		width_ = al_get_bitmap_width(img_);
		height_ = al_get_bitmap_height(img_);
	}
	

	Image::Image(int id, float r, float g, float b){
		id_ = id;
		
		color_ = al_map_rgb_f(r,g,b);

	}
}