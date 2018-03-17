#include "BaseSettings.h"


/*
This DLLS namespace
*/
namespace AcedSharedDLL {


	/*
	Base Settings for this DLL to function.
	*/
	BaseSettings::BaseSettings() {

		//Font for entire project
		font30_ = al_load_font("arial.ttf", Constants::TileSize(), 0);

		//Helper function for settings defaults
		InitDefaultBaseSettings();


		//Load the real settings from config if it exists
		pugi::xml_document xmlDoc;
		auto result = xmlDoc.load_file("Settings.config");

		//If the file exists set the settings. Otherwise save the default settings to config file
		if (result.status == 0)
		{

			//Base node for All Settings DLL + Game.
			pugi::xml_node xmlAllSettings = xmlDoc.child("allsettings");

			//Base settings that are relevant to the DLL only
			pugi::xml_node xmlBaseSettings = xmlAllSettings.child("basesettings");

			//Set the key value properties
			for (pugi::xml_node_iterator xmlPairIterator = xmlBaseSettings.children().begin(); xmlPairIterator != xmlBaseSettings.children().end(); xmlPairIterator++)
			{
				auto key = xmlPairIterator->child("key");
				auto keyCode = (SETTINGCODES)key.attribute("code").as_int();
				auto valueList = xmlPairIterator->child("valuelist");

				//Init struct for settings
				SettingPair pair;
				pair.Code = keyCode;

				//Based on the type of value expected Get and set the value
				switch (settingsMap_[keyCode].TypeCode) {
				case SETTINGTYPES::INT:
					pair.ValueInt = valueList.child("value").attribute("v").as_int();
					SetSettingValue(pair);
					break;
				case SETTINGTYPES::BOOL:
					pair.ValueBool = valueList.child("value").attribute("v").as_bool();
					SetSettingValue(pair);
					break;
				case SETTINGTYPES::STRING:
					pair.ValueString = valueList.child("value").attribute("v").as_string();
					SetSettingValue(pair);
					break;
				case SETTINGTYPES::VECTORINT:
					//pair.VectorValueInt = valueList.child("value").attribute("v").as_string();
					//SetSettingValue(pair);
					//foreach int in list
					break;
				case SETTINGTYPES::VECTORSTRING:
					//pair.VectorValueString = valueList.child("value").attribute("v").as_string();
					//SetSettingValue(pair);
					//foreach string in list
					break;
				}

				//Save the value into the full settings list
				SetSettingValue(pair);
			}
		}
		else if (result.status >= 1)
		{
			//Save the current defaults into config file
			SaveSettings();
		}
	}


	/*
	Clean up descrutor for disposaal
	*/
	BaseSettings::~BaseSettings() {

	}












	//------------------------------------------------------------------------------GETS-------------------------------------------------------------------------------------------------------------//

	/*
	Gets the screens actual height in pixels
	*/
	int BaseSettings::GetScreenHeight() {
		return screenHeight_;
	};
	/*
	Gets the screens actual width in pixels
	*/
	int BaseSettings::GetScreenWidth() {
		return screenWidth_;
	};

	/*
	Gets the displays ratio? of sorts. This is usually screensize/tilesize
	*/
	int BaseSettings::GetDisplayWidth() {
		return displayWidth_;
	};
	/*
	Gets the displays ratio? of sorts. This is usually screensize/tilesize
	*/
	int BaseSettings::GetDisplayHeight() {
		return displayHeight_;
	};
	/*
	Gets flag whether the collision boxes are white or black
	True = White
	False = Black
	*/
	bool BaseSettings::GetColorCollisionInvert() {
		return collisionColorInverted_;
	};


	/*
	Gets the font for the project
	*/
	ALLEGRO_FONT* BaseSettings::GetFont30() {
		return font30_;
	};

	/*
	Gets the width of the text based on current selected font and the string supplied
	*/
	int BaseSettings::GetFontWidth(std::string text)
	{
		return al_get_text_width(font30_, text.c_str());
	};








	//------------------------------------------------------------------------------SETS-------------------------------------------------------------------------------------------------------------//

	/*
	Helper function for settings values using a pair struct that will call relevant function based on the id of variable being changed
	*/
	void BaseSettings::SetSettingValue(SettingPair pair) {
		switch (pair.Code) {
		case SETTINGCODES::SCREENHEIGHT:
			SetScreenHeight(pair.ValueInt);
			break;
		case SETTINGCODES::SCREENWIDTH:
			SetScreenWidth(pair.ValueInt);
			break;
		case SETTINGCODES::DISPLAYHEIGHT:
			SetDisplayHeight(pair.ValueInt);
			break;
		case SETTINGCODES::DISPLAYWIDTH:
			SetDisplayWidth(pair.ValueInt);
			break;
		case SETTINGCODES::COLLISIONCOLORINVERTED:
			SetColorCollisionInvert(pair.ValueBool);
			break;
		}
	}


	/*
	Sets the screens actual height in pixels
	*/
	void BaseSettings::SetScreenHeight(int val) {
		screenHeight_ = val;
		SetDisplayHeight(val / Constants::TileSize());
		settingsMap_[SETTINGCODES::SCREENHEIGHT].ValueInt = val;
	};

	/*
	Sets the screens actual width in pixels
	*/
	void BaseSettings::SetScreenWidth(int val) {
		screenWidth_ = val;
		SetDisplayWidth(val / Constants::TileSize());
		settingsMap_[SETTINGCODES::SCREENWIDTH].ValueInt = val;
	};

	/*
	Sets the displays ratio? of sorts. This is usually screensize/tilesize
	*/
	void BaseSettings::SetDisplayHeight(int val) {
		displayHeight_ = val;
		settingsMap_[SETTINGCODES::DISPLAYHEIGHT].ValueInt = val;
	};

	/*
	Sets the displays ratio? of sorts. This is usually screensize/tilesize
	*/
	void BaseSettings::SetDisplayWidth(int val) {
		displayWidth_ = val;
		settingsMap_[SETTINGCODES::DISPLAYWIDTH].ValueInt = val;
	};

	/*
	This is used for setting collision box color incase you place a black square and cant see the black collision box over them
	*/
	void BaseSettings::SetColorCollisionInvert(bool val) {
		collisionColorInverted_ = val;
		settingsMap_[SETTINGCODES::COLLISIONCOLORINVERTED].ValueBool = val;
	};





	//------------------------------------------------------------------------------MISC-------------------------------------------------------------------------------------------------------------//



	/*
	Initializes the settings map with some defaults as a seed incase we dont have settings else where
	*/
	void BaseSettings::InitDefaultBaseSettings() {

		SettingPair pair = {
			SETTINGCODES::SCREENWIDTH,
			std::string("Screen Width"),
			std::string("The Games Resolution"),
			SETTINGTYPES::INT,
			std::string("INT"),
			std::vector<std::string>(),
			std::string(),
			std::vector<int>(),
			800,
			false
		};

		settingsMap_.insert(std::pair<SETTINGCODES, SettingPair>(SETTINGCODES::SCREENWIDTH, pair));



		pair = {
			SETTINGCODES::SCREENHEIGHT,
			std::string("Screen Height"),
			std::string("The Games Resolution"),
			SETTINGTYPES::INT,
			std::string("INT"),
			std::vector<std::string>(),
			std::string(),
			std::vector<int>(),
			600,
			false
		};

		settingsMap_.insert(std::pair<SETTINGCODES, SettingPair>(SETTINGCODES::SCREENHEIGHT, pair));



		pair = {
			SETTINGCODES::DISPLAYWIDTH,
			std::string("Display Width"),
			std::string("Cant remember atm but its screen/tilesize(16)"),
			SETTINGTYPES::INT,
			std::string("INT"),
			std::vector<std::string>(),
			std::string(),
			std::vector<int>(),
			50,
			false
		};

		settingsMap_.insert(std::pair<SETTINGCODES, SettingPair>(SETTINGCODES::DISPLAYWIDTH, pair));



		pair = {
			SETTINGCODES::DISPLAYHEIGHT,
			std::string("Display Height"),
			std::string("Cant remember atm but its screen/tilesize(16)"),
			SETTINGTYPES::INT,
			std::string("INT"),
			std::vector<std::string>(),
			std::string(),
			std::vector<int>(),
			37,
			false
		};

		settingsMap_.insert(std::pair<SETTINGCODES, SettingPair>(SETTINGCODES::DISPLAYHEIGHT, pair));


		pair = {
			SETTINGCODES::COLLISIONCOLORINVERTED,
			std::string("Collision Color Inverted"),
			std::string("For the tile placement and collision boxes. Inverts the color so you can identify"),
			SETTINGTYPES::BOOL,
			std::string("BOOL"),
			std::vector<std::string>(),
			std::string(),
			std::vector<int>(),
			0,
			false
		};

		settingsMap_.insert(std::pair<SETTINGCODES, SettingPair>(SETTINGCODES::COLLISIONCOLORINVERTED, pair));

	}












	/*
	Saves all current settings into the config
	Current only saves base settings under all settings node
	TODO(MATT): Might need to configure gamesettings node in here aswell???
	*/
	void BaseSettings::SaveSettings() {
		pugi::xml_document xmlNewDoc;
		pugi::xml_node xmlAllSettings = xmlNewDoc.append_child("allsettings");
		pugi::xml_node xmlBaseSettings = xmlAllSettings.append_child("basesettings");
		for (auto settingIterator = settingsMap_.begin(); settingIterator != settingsMap_.end(); settingIterator++)
		{
			pugi::xml_node pair = xmlBaseSettings.append_child("pair");
			pair.append_attribute("group").set_value("map");
			pugi::xml_node key = pair.append_child("key");
			key.append_attribute("code").set_value(std::to_string((int)settingIterator->first).c_str());
			key.append_attribute("readable").set_value(settingIterator->second.Readable.c_str());
			key.append_attribute("comment").set_value(settingIterator->second.Comment.c_str());
			key.append_attribute("typecode").set_value((int)settingIterator->second.TypeCode);
			key.append_attribute("typereadable").set_value(settingIterator->second.TypeReadable.c_str());

			pugi::xml_node valueList = pair.append_child("valuelist");
			pugi::xml_node value;

			//Based on the type of attributes to be saved change the way we set the node values
			switch (settingIterator->second.TypeCode) {
			case SETTINGTYPES::BOOL:
				value = valueList.append_child("value");
				value.append_attribute("v").set_value(settingIterator->second.ValueBool);
				break;
			case SETTINGTYPES::INT:
				value = valueList.append_child("value");
				value.append_attribute("v").set_value(settingIterator->second.ValueInt);
				break;
			case SETTINGTYPES::STRING:
				value = valueList.append_child("value");
				value.append_attribute("v").set_value(settingIterator->second.ValueString.c_str());
				break;
			case SETTINGTYPES::VECTORINT:
				break;
			case SETTINGTYPES::VECTORSTRING:
				break;
			}
		}

		//Saves the xml tree to file
		xmlNewDoc.save_file("Settings.config");
	}








}






