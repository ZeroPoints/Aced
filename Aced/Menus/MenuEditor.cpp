#include "MenuTemplates.h"






MenuEditor::MenuEditor(std::shared_ptr<Settings> &settings) : Menu((std::shared_ptr<AcedSharedDLL::BaseSettings>)settings) {

	SetMenuHeader(std::string("Editor Menu"));
	SetId(AcedSharedDLL::STATES::EDITORMAINMENU);


	auto itemStoreReturn = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreReturn->SetId(AcedSharedDLL::STATES::RETURN);
	itemStoreReturn->SetMenuItemText(std::string("Return"));
	AddMenuItem(itemStoreReturn);

	auto itemStoreNew = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreNew->SetId(AcedSharedDLL::STATES::NEW);
	itemStoreNew->SetMenuItemText(std::string("New Map"));
	AddMenuItem(itemStoreNew);

	auto itemStoreSave = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreSave->SetId(AcedSharedDLL::STATES::SAVE);
	itemStoreSave->SetMenuItemText(std::string("Save Map"));
	AddMenuItem(itemStoreSave);

	auto itemStoreLoad = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreLoad->SetId(AcedSharedDLL::STATES::LOAD);
	itemStoreLoad->SetMenuItemText(std::string("Load Map"));
	AddMenuItem(itemStoreLoad);

	auto itemStoreMapOptions = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreMapOptions->SetId(AcedSharedDLL::STATES::MAPOPTIONS);
	itemStoreMapOptions->SetMenuItemText(std::string("Map Options"));
	AddMenuItem(itemStoreMapOptions);

	auto itemStoreOptions = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreOptions->SetId(AcedSharedDLL::STATES::OPTIONS);
	itemStoreOptions->SetMenuItemText(std::string("Options"));
	AddMenuItem(itemStoreOptions);

	/*itemStore = new MenuItem;
	itemStore->SetId(STATES::ABOUT);
	itemStore->SetMenuItemText("About");
	AddMenuItem(itemStore);*/



	auto itemStoreQuit = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreQuit->SetId(AcedSharedDLL::STATES::MAINMENU);
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






