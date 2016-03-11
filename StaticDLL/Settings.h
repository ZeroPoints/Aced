#ifndef SETTINGS_H
#define SETTINGS_H


#define ALLEGRO_NO_MAGIC_MAIN



#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL{
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
			int displayWidth_, displayHeight_;







	};
}
#endif