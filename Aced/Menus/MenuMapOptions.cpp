#include "MenuTemplates.h"



MenuMapOptions::MenuMapOptions(std::shared_ptr<Settings> &settings, std::shared_ptr<AcedSharedDLL::Map> &currentMap) : Menu((std::shared_ptr<AcedSharedDLL::BaseSettings>)settings) {
	SetMap(currentMap);

	SetMenuHeader(std::string("Map Options"));
	SetId(AcedSharedDLL::STATES::EDITORMAPOPTIONS);
	int widestItem = settings->GetFontWidth(GetMenuHeader());

	auto itemStoreCurrentWidth = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreCurrentWidth->SetMenuItemText(std::string("Current Width:"));

	//might need to delete this tempval char array? mmm looks to be in stack so should die when method finishs....
	std::string tempVal;
	tempVal = std::to_string(GetMap()->GetMapWidth());

	itemStoreCurrentWidth->InitMenuItemProperty(tempVal);
	itemStoreCurrentWidth->SetMenuItemTargetable(false);
	if (widestItem < settings->GetFontWidth(itemStoreCurrentWidth->GetMenuItemText())) {
		widestItem = settings->GetFontWidth(itemStoreCurrentWidth->GetMenuItemText());
	}
	AddMenuItem(itemStoreCurrentWidth);





	auto itemStoreNewWidth = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreNewWidth->InitMenuItemProperty("");
	itemStoreNewWidth->SetOptionId(AcedSharedDLL::OPTIONTYPES::WIDTHOPTION);
	itemStoreNewWidth->SetMenuItemText(std::string("New Width:"));
	if (widestItem < settings->GetFontWidth(itemStoreNewWidth->GetMenuItemText())) {
		widestItem = settings->GetFontWidth(itemStoreNewWidth->GetMenuItemText());
	}
	AddMenuItem(itemStoreNewWidth);




	auto itemStoreCurrentHeight = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreCurrentHeight->SetMenuItemText(std::string("Current Height:"));

	tempVal = std::to_string(GetMap()->GetMapHeight());

	itemStoreCurrentHeight->InitMenuItemProperty(tempVal);
	itemStoreCurrentHeight->SetMenuItemTargetable(false);
	if (widestItem < settings->GetFontWidth(itemStoreCurrentHeight->GetMenuItemText())) {
		widestItem = settings->GetFontWidth(itemStoreCurrentHeight->GetMenuItemText());
	}
	AddMenuItem(itemStoreCurrentHeight);






	auto itemStoreNewHeight = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreNewHeight->InitMenuItemProperty("");
	itemStoreNewHeight->SetOptionId(AcedSharedDLL::OPTIONTYPES::HEIGHTOPTION);
	itemStoreNewHeight->SetMenuItemText(std::string("New Height:"));
	if (widestItem < settings->GetFontWidth(itemStoreNewHeight->GetMenuItemText())) {
		widestItem = settings->GetFontWidth(itemStoreNewHeight->GetMenuItemText());
	}
	AddMenuItem(itemStoreNewHeight);




	auto itemStoreSave = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreSave->SetId(AcedSharedDLL::STATES::SAVE);
	itemStoreSave->SetMenuItemText(std::string("Save"));
	if (widestItem < settings->GetFontWidth(itemStoreSave->GetMenuItemText())) {
		widestItem = settings->GetFontWidth(itemStoreSave->GetMenuItemText());
	}
	AddMenuItem(itemStoreSave);

	auto itemStoreReturn = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreReturn->SetId(AcedSharedDLL::STATES::RETURN);
	itemStoreReturn->SetMenuItemText(std::string("Return"));
	if (widestItem < settings->GetFontWidth(itemStoreReturn->GetMenuItemText())) {
		widestItem = settings->GetFontWidth(itemStoreReturn->GetMenuItemText());
	}
	AddMenuItem(itemStoreReturn);

	widestItem += (AcedSharedDLL::Constants::TileSize() * 4);

	SetMenuX((settings->GetScreenWidth() / 2) - (widestItem / 2) - (AcedSharedDLL::Constants::TileSize() * 4));
	SetMenuY(100);

	SetMenuHeaderX((settings->GetScreenWidth() / 2) - (widestItem / 2) - (AcedSharedDLL::Constants::TileSize() * 4));
	SetMenuHeaderY(50 + AcedSharedDLL::Constants::TileSize());
	SetMenuHeaderHeight(50 - AcedSharedDLL::Constants::TileSize());

	int i = 0;
	int xloc = settings->GetScreenWidth() / 2;
	int yloc = 100 + AcedSharedDLL::Constants::TileSize();
	int yspacing = AcedSharedDLL::Constants::TileSize() * 2;

	auto menuSize = GetMenuItems().size();
	for (i = 0; i < menuSize; i++)
	{
		GetMenuItems()[i]->SetMenuItemX(xloc);
		GetMenuItems()[i]->SetMenuItemPropertyX(xloc + (settings->GetFontWidth(GetMenuItems()[i]->GetMenuItemText()) / 2) + (AcedSharedDLL::Constants::TileSize() * 1));
		GetMenuItems()[i]->SetMenuItemY(yloc);
		yloc = yloc + yspacing;
	}

	SetMenuWidth(settings->GetScreenWidth() - (2 * GetMenuX()));
	SetMenuHeaderWidth(settings->GetScreenWidth() - (2 * GetMenuX()));
	SetMenuHeight(yloc - GetMenuY());

	SetCurrentSelection();
}

