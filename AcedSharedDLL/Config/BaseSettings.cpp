#include "BaseSettings.h"



namespace AcedSharedDLL {
	BaseSettings::BaseSettings() {

		font30_ = al_load_font("arial.ttf", Constants::TileSize(), 0);

		InitDefaultBaseSettings();


		pugi::xml_document xmlDoc;
		auto result = xmlDoc.load_file("Settings.config");
		pugi::xml_node xmlAllSettings = xmlDoc.child("allsettings");

		//What happens if file doesnt exist? create one?
		if (result.status == 0)
		{
			pugi::xml_node xmlBaseSettings = xmlAllSettings.child("basesettings");
			for (pugi::xml_node_iterator xmlPairIterator = xmlBaseSettings.children().begin(); xmlPairIterator != xmlBaseSettings.children().end(); xmlPairIterator++)
			{
				//Read pair from doco...

				auto key = xmlPairIterator->child("key");
				auto keyCode = (SETTINGCODES)key.attribute("code").as_int();
				auto valueList = xmlPairIterator->child("valuelist");

				SettingPair pair;
				pair.Code = keyCode;

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

				SetSettingValue(pair);
			}
		}
		else if (result.status >= 1)
		{
			////maps for new style together
			SetScreenWidth(800);
			SetScreenHeight(600);
			SetDisplayWidth(screenWidth_ / Constants::TileSize());
			SetDisplayHeight(screenHeight_ / Constants::TileSize());
			SetColorCollisionInvert(false);

			SaveSettings();
		}
	}



	BaseSettings::~BaseSettings() {

	}








	//Save all current setting changes back into doc
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
			bool isList = false;
			switch (settingIterator->second.TypeCode) {
			case SETTINGTYPES::BOOL:
				value = valueList.append_child("value");
				value.append_attribute("v").set_value(settingIterator->second.ValueBool);
				isList = false;
				break;
			case SETTINGTYPES::INT:
				value = valueList.append_child("value");
				value.append_attribute("v").set_value(settingIterator->second.ValueInt);
				isList = false;
				break;
			case SETTINGTYPES::STRING:
				value = valueList.append_child("value");
				value.append_attribute("v").set_value(settingIterator->second.ValueString.c_str());
				isList = false;
				break;
			case SETTINGTYPES::VECTORINT:
				isList = true;
				break;
			case SETTINGTYPES::VECTORSTRING:
				isList = true;
				break;
			}
		}
		xmlNewDoc.save_file("Settings.config");
	}














	//------------------------------------------------------------------------------SETS-------------------------------------------------------------------------------------------------------------//


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



	void BaseSettings::SetScreenHeight(int val) {
		screenHeight_ = val;
		SetDisplayHeight(val / Constants::TileSize());
		settingsMap_[SETTINGCODES::SCREENHEIGHT].ValueInt = val;
	};
	void BaseSettings::SetScreenWidth(int val) {
		screenWidth_ = val;
		SetDisplayWidth(val / Constants::TileSize());
		settingsMap_[SETTINGCODES::SCREENWIDTH].ValueInt = val;
	};
	void BaseSettings::SetDisplayHeight(int val) {
		displayHeight_ = val;
		settingsMap_[SETTINGCODES::DISPLAYHEIGHT].ValueInt = val;
	};
	void BaseSettings::SetDisplayWidth(int val) {
		displayWidth_ = val;
		settingsMap_[SETTINGCODES::DISPLAYWIDTH].ValueInt = val;
	};
	void BaseSettings::SetColorCollisionInvert(bool val) {
		collisionColorInverted_ = val;
		settingsMap_[SETTINGCODES::COLLISIONCOLORINVERTED].ValueBool = val;
	};




	//------------------------------------------------------------------------------GETS-------------------------------------------------------------------------------------------------------------//


	int BaseSettings::GetDisplayWidth() {
		return displayWidth_;
	};
	int BaseSettings::GetDisplayHeight() {
		return displayHeight_;
	};
	int BaseSettings::GetScreenWidth() {
		return screenWidth_;
	};
	int BaseSettings::GetScreenHeight() {
		return screenHeight_;
	};
	bool BaseSettings::GetColorCollisionInvert() {
		return collisionColorInverted_;
	};


	ALLEGRO_FONT* BaseSettings::GetFont30() {
		return font30_;
	};

	int BaseSettings::GetFontWidth(std::string text)
	{
		return al_get_text_width(font30_, text.c_str());
	};







	//------------------------------------------------------------------------------INITS-------------------------------------------------------------------------------------------------------------//



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




	//enum class SETTINGTYPES { NA, BOOL, STRING, INT, VECTORSTRING, VECTORINT };

	//enum class SETTINGCODES { NA, SCREENWIDTH, SCREENHEIGHT, DISPLAYWIDTH, DISPLAYHEIGHT, COLLISIONCOLORINVERTED };


}






