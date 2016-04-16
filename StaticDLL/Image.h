#ifndef IMAGE_H
#define IMAGE_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <vector>
#include "Settings.h"
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


			STATICDLL_API ~Image()
			{
				//al_destroy_bitmap(img_);
			};



			STATICDLL_API ALLEGRO_BITMAP *GetImage()
			{
				return img_;
			};


			//Need a Key for look up Maybe
			STATICDLL_API int GetId()
			{
				return id_;
			};
			
		private:

			int id_;

			ALLEGRO_BITMAP *img_;
	};
}
#endif
