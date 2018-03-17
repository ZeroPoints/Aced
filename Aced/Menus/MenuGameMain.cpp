#include "MenuTemplates.h"





MenuGameMain::MenuGameMain(std::shared_ptr<Settings> &settings) : Menu((std::shared_ptr<AcedSharedDLL::BaseSettings>)settings) {

	SetMenuHeader(std::string("Game Main Menu"));
	SetId(AcedSharedDLL::STATES::EDITORMAINMENU);
	int widestItem = settings->GetFontWidth(GetMenuHeader());

	auto itemStoreNew = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreNew->SetId(AcedSharedDLL::STATES::NEW);
	itemStoreNew->SetMenuItemText(std::string("New Map"));
	if (widestItem < settings->GetFontWidth(itemStoreNew->GetMenuItemText())) {
		widestItem = settings->GetFontWidth(itemStoreNew->GetMenuItemText());
	}
	AddMenuItem(itemStoreNew);


	auto itemStoreLoad = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreLoad->SetId(AcedSharedDLL::STATES::LOAD);
	itemStoreLoad->SetMenuItemText(std::string("Load Map"));
	if (widestItem < settings->GetFontWidth(itemStoreLoad->GetMenuItemText())) {
		widestItem = settings->GetFontWidth(itemStoreLoad->GetMenuItemText());
	}
	AddMenuItem(itemStoreLoad);

	auto itemStoreEdit = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreEdit->SetId(AcedSharedDLL::STATES::EDITORMAINMENU);
	itemStoreEdit->SetMenuItemText(std::string("Edit Mode"));
	if (widestItem < settings->GetFontWidth(itemStoreEdit->GetMenuItemText())) {
		widestItem = settings->GetFontWidth(itemStoreEdit->GetMenuItemText());
	}
	AddMenuItem(itemStoreEdit);

	auto itemStoreOptions = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreOptions->SetId(AcedSharedDLL::STATES::OPTIONS);
	itemStoreOptions->SetMenuItemText(std::string("Options"));
	if (widestItem < settings->GetFontWidth(itemStoreOptions->GetMenuItemText())) {
		widestItem = settings->GetFontWidth(itemStoreOptions->GetMenuItemText());
	}
	AddMenuItem(itemStoreOptions);


	auto itemStoreQuit = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreQuit->SetId(AcedSharedDLL::STATES::QUIT);
	itemStoreQuit->SetMenuItemText(std::string("Quit"));
	if (widestItem < settings->GetFontWidth(itemStoreQuit->GetMenuItemText())) {
		widestItem = settings->GetFontWidth(itemStoreQuit->GetMenuItemText());
	}
	AddMenuItem(itemStoreQuit);

	widestItem += (AcedSharedDLL::Constants::TileSize() * 4);

	SetMenuX((settings->GetScreenWidth() / 2) - (widestItem / 2) - (AcedSharedDLL::Constants::TileSize() * 4));
	SetMenuY(100);

	SetMenuHeaderX((settings->GetScreenWidth() / 2) - (widestItem / 2) - (AcedSharedDLL::Constants::TileSize() * 4));
	SetMenuHeaderY(50 + AcedSharedDLL::Constants::TileSize());
	SetMenuHeaderHeight(50 - AcedSharedDLL::Constants::TileSize());

	int i = 0;
	int xloc = settings->GetScreenWidth() /2;
	int yloc = 100 + AcedSharedDLL::Constants::TileSize();
	int yspacing = AcedSharedDLL::Constants::TileSize()*2;

	auto menuSize = GetMenuItems().size();
	for (i = 0; i < menuSize; i++)
	{
		GetMenuItems()[i]->SetMenuItemX(xloc);
		GetMenuItems()[i]->SetMenuItemY(yloc);
		yloc = yloc + yspacing;
	}

	SetMenuWidth(settings->GetScreenWidth() - (2 * GetMenuX()));
	SetMenuHeaderWidth(settings->GetScreenWidth() - (2 * GetMenuX()));
	SetMenuHeight(yloc - GetMenuY());


	SetCurrentSelection();
}



