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



#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL{

	class Image
	{
		public:
			STATICDLL_API Image(int id, const char *file);
			STATICDLL_API Image(int id, const char *file, const char *name);
			STATICDLL_API Image(int id, const char *file, float r, float g, float b);
			STATICDLL_API Image(int id, float r, float g, float b);
			STATICDLL_API Image(int id, const char *file, double width, double height);


			STATICDLL_API ~Image();





			//-----------------------------------------------------------------------------------------------------

			//Gets



			STATICDLL_API char *GetName();


			STATICDLL_API ALLEGRO_COLOR GetColor();
			STATICDLL_API ALLEGRO_BITMAP *GetImage();
			STATICDLL_API double GetWidth();
			STATICDLL_API double GetImageWidth();
			STATICDLL_API double GetHeight();
			STATICDLL_API double GetImageHeight();

			//Need a Key for look up Maybe
			STATICDLL_API int GetId();
			
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


			char *name_;



			//This color isnt used as an image its used as a type that loads from file
			ALLEGRO_COLOR color_;


			ALLEGRO_BITMAP *img_;
	};
}
#endif
