#include "Image.h"



namespace StaticDLL{

	//SET DEFAULT COLOR FOR THESE TO WHITE
	//use al tinted draw all the time
	Image::Image(int id, const char *file){
		id_ = id;
		
		img_ = al_load_bitmap(file);

		imgWidth_ = al_get_bitmap_width(img_);
		imgHeight_ = al_get_bitmap_height(img_);

		width_ = imgWidth_/StaticDLL::Constants::TileSize();
		height_ = imgHeight_/StaticDLL::Constants::TileSize();
	}



	Image::Image(int id, const char *file, const char *name){
		id_ = id;
		

		name_ = (char*)malloc(strlen(name)+1);
		strcpy(name_, name);

		img_ = al_load_bitmap(file);
		
		width_ = 1;
		height_ = 1;
		imgWidth_ = al_get_bitmap_width(img_);
		imgHeight_ = al_get_bitmap_height(img_);
	}


	Image::Image(int id, const char *file, float r, float g, float b){
		id_ = id;
		
		img_ = al_load_bitmap(file);
		color_ = al_map_rgb_f(r,g,b);
		
		width_ = 1;
		height_ = 1;
		imgWidth_ = al_get_bitmap_width(img_);
		imgHeight_ = al_get_bitmap_height(img_);
	}
	

	Image::Image(int id, float r, float g, float b){
		id_ = id;
		
		color_ = al_map_rgb_f(r,g,b);
		
		width_ = 1;
		height_ = 1;
	}


	Image::Image(int id, const char *file, double width, double height){
		id_ = id;
		
		img_ = al_load_bitmap(file);


		imgWidth_ = al_get_bitmap_width(img_);
		imgHeight_ = al_get_bitmap_height(img_);


		width_ = width;
		height_ = height;

	}



	Image::~Image()
	{
		//fprintf(stderr, "A Image Destructed\n");
		al_destroy_bitmap(img_);
	}



	//-----------------------------------------------------------------------------------------------------

	//Gets



	char *Image::GetName()
	{
		return name_;
	}


	ALLEGRO_COLOR Image::GetColor()
	{
		return color_;
	}
	ALLEGRO_BITMAP *Image::GetImage()
	{
		return img_;
	}
	double Image::GetWidth()
	{
		return width_;
	}
	double Image::GetImageWidth()
	{
		return imgWidth_;
	}
	double Image::GetHeight()
	{
		return height_;
	}
	double Image::GetImageHeight()
	{
		return imgHeight_;
	}

	//Need a Key for look up Maybe
	int Image::GetId()
	{
		return id_;
	}


}