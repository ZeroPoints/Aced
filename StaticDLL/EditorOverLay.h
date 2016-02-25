#ifndef EDITOROVERLAY_H
#define EDITOROVERLAY_H


#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <vector>
#include "tile.h"
#include "Settings.h"
#include "ObjectBase.h"
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes



#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL{
	class EditorOverLay
	{
		public:

			STATICDLL_API EditorOverLay(Settings *settings);



			STATICDLL_API void SetTop(int top)
			{
				top_ = top;
			}





			STATICDLL_API void PreCalc();
			



			STATICDLL_API void Update();




			STATICDLL_API void OnBottomArrowClick();




			STATICDLL_API void Draw();



			STATICDLL_API void DrawBottomArrow();




		private:




			int arrowLocationX_, arrowLocationY_; 

			int arrowLocationWidth_, arrowLocationHeight_; 



			ObjectBase *arrow_;




			int top_;




			//The border of the entire Map
			int width_;
			//The border of the entire Map
			int height_;

			



			bool playerplaced_;
			int playerStartX_;//players starting position
			int playerStartY_;

			ALLEGRO_FONT *font30_;

			Settings *settings_;
	};
}
#endif
