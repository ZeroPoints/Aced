#ifndef SETTINGS_H
#define SETTINGS_H


#define ALLEGRO_NO_MAGIC_MAIN

#include "../OpenSource/pugixml/pugixml.hpp"
#include "Definitions.h"


#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL{
	//Settings for the project
	//Most will be loaded from a settinsg file
	class Settings
	{
		public:
			STATICDLL_API Settings();


			//Save all current setting changes back into doc
			STATICDLL_API void SaveSettings();




			STATICDLL_API void SetDisplayHeight(int displayHeight){
				displayHeight_ = displayHeight;
			}


			STATICDLL_API void SetScreenHeight(int screenHeight){
				screenHeight_ = screenHeight;
				displayHeight_ = screenHeight_/Constants::TileSize;
			}
			STATICDLL_API void SetScreenWidth(int screenWidth){
				screenWidth_ = screenWidth;
				displayWidth_ = screenWidth_/Constants::TileSize;
			}



			STATICDLL_API void SetDisplayWidth(int displayWidth){
				displayWidth_ = displayWidth;
			}



			STATICDLL_API int GetDisplayWidth(){
				return displayWidth_;
			}
			STATICDLL_API int GetDisplayHeight(){
				return displayHeight_;
			}

			STATICDLL_API int GetScreenWidth(){
				return screenWidth_;
			}
			STATICDLL_API int GetScreenHeight(){
				return screenHeight_;
			}



			STATICDLL_API void SetColorCollisionInvert(bool invert){
				collisionColorInverted_ = invert;
			}
			STATICDLL_API bool GetColorCollisionInvert(){
				return collisionColorInverted_;
			}

		private:
			//Display values are for the screens resolution
			int displayWidth_, displayHeight_;

			int screenWidth_, screenHeight_;


			bool collisionColorInverted_;






	};
}
#endif