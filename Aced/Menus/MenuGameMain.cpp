#include "MenuTemplates.h"





MenuGameMain::MenuGameMain(std::shared_ptr<Settings> &settings) : Menu((std::shared_ptr<AcedSharedDLL::BaseSettings>)settings) {
	SetFont(al_load_font("arial.ttf", 30, 0));

	SetMenuHeader(std::string("Game Main Menu"));
	SetId(AcedSharedDLL::STATES::EDITORMAINMENU);

	auto itemStoreNew = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreNew->SetId(AcedSharedDLL::STATES::NEW);
	itemStoreNew->SetMenuItemText(std::string("New Map"));
	AddMenuItem(itemStoreNew);

	auto itemStoreLoad = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreLoad->SetId(AcedSharedDLL::STATES::LOAD);
	itemStoreLoad->SetMenuItemText(std::string("Load Map"));
	AddMenuItem(itemStoreLoad);

	auto itemStoreEdit = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreEdit->SetId(AcedSharedDLL::STATES::EDITORMAINMENU);
	itemStoreEdit->SetMenuItemText(std::string("Edit Mode"));
	AddMenuItem(itemStoreEdit);

	auto itemStoreOptions = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreOptions->SetId(AcedSharedDLL::STATES::OPTIONS);
	itemStoreOptions->SetMenuItemText(std::string("Options"));
	AddMenuItem(itemStoreOptions);


	auto itemStoreQuit = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreQuit->SetId(AcedSharedDLL::STATES::QUIT);
	itemStoreQuit->SetMenuItemText(std::string("Quit"));
	AddMenuItem(itemStoreQuit);


	SetMenuX(300);
	SetMenuY(100);
	SetMenuWidth(250);
	SetMenuHeight(400);

	SetMenuHeaderX(300);
	SetMenuHeaderY(50);
	SetMenuHeaderWidth(250);
	SetMenuHeaderHeight(50);

	int i = 0;
	int xloc = 425;
	int yloc = 110;
	int yspacing = 50;


	auto menuSize = GetMenuItems().size();
	for (i = 0; i < menuSize; i++)
	{
		//printf("%i\n",yloc);
		GetMenuItems()[i]->SetMenuItemX(xloc);
		GetMenuItems()[i]->SetMenuItemY(yloc);
		yloc = yloc + yspacing;
	}
	SetMenuHeight(yloc - GetMenuY());

	SetCurrentSelection();
}



