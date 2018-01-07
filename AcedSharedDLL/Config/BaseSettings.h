#ifndef BASESETTINGS_H
#define BASESETTINGS_H


#define ALLEGRO_NO_MAGIC_MAIN

#include "../../OpenSource/pugixml/pugixml.hpp"
#include "../Static/Definitions.h"



#include <string>
#include <map>
#include <vector>


#ifdef ACEDSHAREDDLL_EXPORTS
   #define ACEDSHAREDDLL_API __declspec(dllexport)
#else
   #define ACEDSHAREDDLL_API __declspec(dllimport)
#endif



namespace AcedSharedDLL{
	//Settings for the project
	//Most will be loaded from a settinsg file

	struct SettingPair {
		SETTINGCODES Code;
		std::string Readable;
		std::string Comment;
		SETTINGTYPES TypeCode;
		std::string TypeReadable;
		std::vector<std::string> VectorValueString;
		std::string ValueString;
		std::vector<int> VectorValueInt;
		int ValueInt;
		bool ValueBool;
	};


	class BaseSettings
	{
		public:
			ACEDSHAREDDLL_API BaseSettings();


			//Save all current setting changes back into doc
			ACEDSHAREDDLL_API virtual void SaveSettings();


			ACEDSHAREDDLL_API void SetSettingValue(SettingPair pair);


			ACEDSHAREDDLL_API void SetScreenHeight(int screenHeight);
			ACEDSHAREDDLL_API void SetScreenWidth(int screenWidth);
			ACEDSHAREDDLL_API void SetDisplayHeight(int displayHeight);
			ACEDSHAREDDLL_API void SetDisplayWidth(int displayWidth);



			ACEDSHAREDDLL_API int GetDisplayWidth();
			ACEDSHAREDDLL_API int GetDisplayHeight();
			ACEDSHAREDDLL_API int GetScreenWidth();
			ACEDSHAREDDLL_API int GetScreenHeight();


			ACEDSHAREDDLL_API void InitDefaultBaseSettings();



			ACEDSHAREDDLL_API void SetColorCollisionInvert(bool invert);
			ACEDSHAREDDLL_API bool GetColorCollisionInvert();

		private:
			//Display values are for the screens resolution
			int displayWidth_, displayHeight_;

			int screenWidth_, screenHeight_;


			bool collisionColorInverted_;



			//key,value...
			std::map<SETTINGCODES, SettingPair> settingsMap_;





	};





}
#endif