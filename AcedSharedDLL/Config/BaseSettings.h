#ifndef BASESETTINGS_H
#define BASESETTINGS_H


/*
No Magic for using allegro in a dll
Cant remember exactly reasoning
*/
#define ALLEGRO_NO_MAGIC_MAIN

/*
Open Source Headers
*/
#include "../../OpenSource/pugixml/pugixml.hpp"

/*
Aced Shared Internal Headers
*/
#include "../Static/Definitions.h"

/*
Allegro Headers
*/
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/*
C++ Headers
*/
#include <string>
#include <map>
#include <vector>
#include <memory>

/*
DLL  Exports
*/
#ifdef ACEDSHAREDDLL_EXPORTS
#define ACEDSHAREDDLL_API __declspec(dllexport)
#else
#define ACEDSHAREDDLL_API __declspec(dllimport)
#endif


/*
This DLLS namespace
*/
namespace AcedSharedDLL {

	/*
	Settings Key Value Pair Objects.
	Used for storing settings
	TODO(Matt): Maybe use templates or I dunno? This is hacky but works for now
	*/
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


	/*
	Container for settings for the entirety of the DLL
	*/
	class BaseSettings
	{
	public:

		/*
		Base Settings for this DLL to function.
		*/
		ACEDSHAREDDLL_API BaseSettings();

		/*
		Clean up descrutor for disposaal
		*/
		ACEDSHAREDDLL_API ~BaseSettings();



		//------------------------------------------------------------------------------GETS-------------------------------------------------------------------------------------------------------------//


		/*
		Gets flag whether the collision boxes are white or black
		True = White
		False = Black
		*/
		ACEDSHAREDDLL_API bool GetColorCollisionInvert();

		/*
		Gets the displays ratio? of sorts. This is usually screensize/tilesize
		*/
		ACEDSHAREDDLL_API int GetDisplayWidth();

		/*
		Gets the displays ratio? of sorts. This is usually screensize/tilesize
		*/
		ACEDSHAREDDLL_API int GetDisplayHeight();
		/*
		Gets the screens actual width in pixels
		*/
		ACEDSHAREDDLL_API int GetScreenWidth();
		/*
		Gets the screens actual height in pixels
		*/
		ACEDSHAREDDLL_API int GetScreenHeight();

		/*
		Gets the width of the text based on current selected font and the string supplied
		*/
		ACEDSHAREDDLL_API int GetFontWidth(std::string text);

		/*
		Gets the font for the project
		*/
		ACEDSHAREDDLL_API ALLEGRO_FONT* GetFont30();




		//------------------------------------------------------------------------------SETS-------------------------------------------------------------------------------------------------------------//

		/*
		Helper function for settings values using a pair struct that will call relevant function based on the id of variable being changed
		*/
		ACEDSHAREDDLL_API void SetSettingValue(SettingPair pair);

		/*
		Sets the screens actual height in pixels
		*/
		ACEDSHAREDDLL_API void SetScreenHeight(int screenHeight);

		/*
		Sets the screens actual width in pixels
		*/
		ACEDSHAREDDLL_API void SetScreenWidth(int screenWidth);

		/*
		Sets the displays ratio? of sorts. This is usually screensize/tilesize
		*/
		ACEDSHAREDDLL_API void SetDisplayHeight(int displayHeight);

		/*
		Sets the displays ratio? of sorts. This is usually screensize/tilesize
		*/
		ACEDSHAREDDLL_API void SetDisplayWidth(int displayWidth);


		/*
		This is used for setting collision box color incase you place a black square and cant see the black collision box over them
		*/
		ACEDSHAREDDLL_API void SetColorCollisionInvert(bool invert);



		//------------------------------------------------------------------------------MISC-------------------------------------------------------------------------------------------------------------//



		/*
		Initializes the settings map with some defaults as a seed incase we dont have settings else where
		*/
		ACEDSHAREDDLL_API void InitDefaultBaseSettings();


		/*
		Saves all current settings into the config
		Current only saves base settings under all settings node
		TODO(MATT): Might need to configure gamesettings node in here aswell???
		*/
		ACEDSHAREDDLL_API virtual void SaveSettings();




	private:

		//Display values are for the screens resolution
		int displayWidth_;
		int displayHeight_;

		//Screen size for the window
		int screenWidth_;
		int screenHeight_;

		//Inverts the tile collision color
		bool collisionColorInverted_;



		//Settings map for the dll to use
		std::map<SETTINGCODES, SettingPair> settingsMap_;

		//Font for the dll
		ALLEGRO_FONT* font30_;



	};





}
#endif