#include "Settings.h"



namespace StaticDLL{
	Settings::Settings(){
		pugi::xml_document xmlDoc;
		auto result = xmlDoc.load_file("..\\Settings.config");
		//What happens if file doesnt exist? create one?
		if(result.status == 0)
		{
			pugi::xml_node xmlSettings = xmlDoc.child("settings");
			screenWidth_ = xmlSettings.attribute("screenwidth").as_int();
			screenHeight_ = xmlSettings.attribute("screenheight").as_int();
			displayWidth_ = screenWidth_/Constants::TileSize;
			displayHeight_ = screenHeight_/Constants::TileSize;
		}
		else if(result.status == 1)
		{
			//if result = 1 then file needs to be created
			screenWidth_ = 800;
			screenHeight_ = 600;
			displayWidth_ = screenWidth_/Constants::TileSize;
			displayHeight_ = screenHeight_/Constants::TileSize;



			pugi::xml_document xmlNewDoc;	
			pugi::xml_node xmlSettings = xmlNewDoc.append_child("settings");
			xmlSettings.append_attribute("screenwidth").set_value(screenWidth_);
			xmlSettings.append_attribute("screenheight").set_value(screenHeight_);
			xmlNewDoc.save_file("..\\Settings.config");


		}
		else
		{
			//dunno if result can get other value???? max?
			screenWidth_ = 800;
			screenHeight_ = 600;
			displayWidth_ = screenWidth_/Constants::TileSize;
			displayHeight_ = screenHeight_/Constants::TileSize;
		}
		
	}


	//Save all current setting changes back into doc
	void Settings::SaveSettings(){
		pugi::xml_document xmlDoc;
		auto result = xmlDoc.load_file("..\\Settings.config");
		pugi::xml_node xmlSettings = xmlDoc.child("settings");
		xmlSettings.attribute("screenwidth").set_value(screenWidth_);
		xmlSettings.attribute("screenheight").set_value(screenHeight_);
		xmlDoc.save_file("..\\Settings.config");
	}
}