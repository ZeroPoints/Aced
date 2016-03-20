#ifndef SETTINGS_H
#define SETTINGS_H


#define ALLEGRO_NO_MAGIC_MAIN



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

			STATICDLL_API void SetDisplayHeight(int displayHeight){
				displayHeight_ = displayHeight;
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



		private:
			//Display values are for the screens resolution
			int displayWidth_, displayHeight_;







	};
}
#endif