#include "Image.h"



namespace AcedSharedDLL{

	//SET DEFAULT COLOR FOR THESE TO WHITE
	//use al tinted draw all the time
	Image::Image(int id, const std::string &file){
		id_ = id;
		
		file_ = std::move(file_);

		img_ = al_load_bitmap(file.c_str());

		imgWidth_ = al_get_bitmap_width(img_);
		imgHeight_ = al_get_bitmap_height(img_);

		width_ = imgWidth_/AcedSharedDLL::Constants::TileSize();
		height_ = imgHeight_/AcedSharedDLL::Constants::TileSize();
	}



	Image::Image(int id, const std::string &file, const std::string &name){
		id_ = id;
		

		name_ = std::move(name);
		file_ = std::move(file_);

		img_ = al_load_bitmap(file.c_str());
		
		width_ = 1;
		height_ = 1;
		imgWidth_ = al_get_bitmap_width(img_);
		imgHeight_ = al_get_bitmap_height(img_);
	}


	Image::Image(int id, const std::string &file, float r, float g, float b){
		id_ = id;
		
		img_ = al_load_bitmap(file.c_str());
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


	Image::Image(int id, const std::string &file, double width, double height){
		id_ = id;
		
		img_ = al_load_bitmap(file.c_str());


		imgWidth_ = al_get_bitmap_width(img_);
		imgHeight_ = al_get_bitmap_height(img_);


		width_ = width;
		height_ = height;

	}



	Image::~Image()
	{
		//fprintf(stderr, "A Image Destructed\n");
		//al_destroy_bitmap(img_);
	}



	//-----------------------------------------------------------------------------------------------------

	//Gets



	std::string Image::GetName()
	{
		return name_;
	}
	std::string Image::GetFile()
	{
		return file_;
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



	//-----------------------------------------------------------------------------------------------------

	//Sets





}