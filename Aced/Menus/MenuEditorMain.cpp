#include "MenuTemplates.h"




MenuEditorMain::MenuEditorMain(std::shared_ptr<Settings> &settings) : Menu((std::shared_ptr<AcedSharedDLL::BaseSettings>)settings) {

	SetMenuHeader(std::string("Editor Menu"));
	SetId(AcedSharedDLL::STATES::EDITORMAINMENU);

	auto itemStoreNew = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreNew->SetId(AcedSharedDLL::STATES::NEW);
	itemStoreNew->SetMenuItemText(std::string("New Map"));
	AddMenuItem(itemStoreNew);

	auto itemStoreLoad = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreLoad->SetId(AcedSharedDLL::STATES::LOAD);
	itemStoreLoad->SetMenuItemText(std::string("Load Map"));
	AddMenuItem(itemStoreLoad);

	auto itemStoreOptions = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreOptions->SetId(AcedSharedDLL::STATES::OPTIONS);
	itemStoreOptions->SetMenuItemText(std::string("Options"));
	AddMenuItem(itemStoreOptions);

	/*itemStore = new MenuItem;
	itemStore->SetId(STATES::ABOUT);
	itemStore->SetMenuItemText("About");
	AddMenuItem(itemStore);*/

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
	for (i = 0; i < GetMenuItems().size(); i++)
	{
		//printf("%i\n",yloc);
		GetMenuItems()[i]->SetMenuItemX(xloc);
		GetMenuItems()[i]->SetMenuItemY(yloc);
		yloc = yloc + yspacing;
	}
	SetMenuHeight(yloc - GetMenuY());

	SetCurrentSelection();
}

