#ifndef IMAGE_H
#define IMAGE_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <vector>
#include "../Static/Definitions.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include <allegro5\allegro_image.h>//images



#ifdef ACEDSHAREDDLL_EXPORTS
   #define ACEDSHAREDDLL_API __declspec(dllexport)
#else
   #define ACEDSHAREDDLL_API __declspec(dllimport)
#endif



namespace AcedSharedDLL{

	class Image
	{
		public:





			ACEDSHAREDDLL_API Image(int id, const std::string &file);
			ACEDSHAREDDLL_API Image(int id, const std::string &file, const std::string &name);
			ACEDSHAREDDLL_API Image(int id, const std::string &file, float r, float g, float b);
			ACEDSHAREDDLL_API Image(int id, float r, float g, float b);
			ACEDSHAREDDLL_API Image(int id, const std::string &file, double width, double height);


			ACEDSHAREDDLL_API ~Image();








			//-----------------------------------------------------------------------------------------------------

			//Gets



			ACEDSHAREDDLL_API std::string GetName();
			ACEDSHAREDDLL_API std::string GetFile();


			ACEDSHAREDDLL_API ALLEGRO_COLOR GetColor();
			ACEDSHAREDDLL_API ALLEGRO_BITMAP *GetImage();
			ACEDSHAREDDLL_API double GetWidth();
			ACEDSHAREDDLL_API double GetImageWidth();
			ACEDSHAREDDLL_API double GetHeight();
			ACEDSHAREDDLL_API double GetImageHeight();

			//Need a Key for look up Maybe
			ACEDSHAREDDLL_API int GetId();
			





			//-----------------------------------------------------------------------------------------------------

			//Sets





		private:

			int id_;


			//this is the images width
			double imgWidth_;
			//this is the tile width
			double width_;

			//this is the images height
			double imgHeight_;
			//this is the tile height
			double height_;

			std::string file_;
			std::string name_;



			//This color isnt used as an image its used as a type that loads from file
			ALLEGRO_COLOR color_;


			ALLEGRO_BITMAP *img_;
	};
}
#endif
