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

			STATICDLL_API void SetMapHeight(int mapHeight){
				mapHeight_ = mapHeight;
			}


			STATICDLL_API void SetMapWidth(int mapWidth){
				mapWidth_ = mapWidth;
			}



			STATICDLL_API int GetMapWidth(){
				return mapWidth_;
			}
			STATICDLL_API int GetMapHeight(){
				return mapHeight_;
			}



		private:
			int mapWidth_, mapHeight_;



			int screenWidth, screenHeight_;




	};
}
#endif