#include "MenuTemplates.h"



MenuMapOptions::MenuMapOptions(std::shared_ptr<Settings> &settings, std::shared_ptr<AcedSharedDLL::Map> &currentMap) : Menu((std::shared_ptr<AcedSharedDLL::BaseSettings>)settings) {
	SetMap(currentMap);
	SetFont(al_load_font("arial.ttf", 30, 0));

	SetMenuHeader(std::string("Map Options"));
	SetId(AcedSharedDLL::STATES::EDITORMAPOPTIONS);


	auto itemStoreCurrentWidth = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreCurrentWidth->SetMenuItemText(std::string("Current Width:"));

	//might need to delete this tempval char array? mmm looks to be in stack so should die when method finishs....
	char tempVal[10];
	sprintf_s(tempVal, "%i", GetMap()->GetMapWidth());

	itemStoreCurrentWidth->InitMenuItemProperty(al_ustr_new(tempVal));
	itemStoreCurrentWidth->SetMenuItemTargetable(false);
	AddMenuItem(itemStoreCurrentWidth);





	auto itemStoreNewWidth = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreNewWidth->InitMenuItemProperty(al_ustr_new(""));
	itemStoreNewWidth->SetOptionId(AcedSharedDLL::OPTIONTYPES::WIDTHOPTION);
	itemStoreNewWidth->SetMenuItemText(std::string("New Width:"));
	AddMenuItem(itemStoreNewWidth);




	auto itemStoreCurrentHeight = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreCurrentHeight->SetMenuItemText(std::string("Current Height:"));

	sprintf_s(tempVal, "%i", GetMap()->GetMapHeight());

	itemStoreCurrentHeight->InitMenuItemProperty(al_ustr_new(tempVal));
	itemStoreCurrentHeight->SetMenuItemTargetable(false);
	AddMenuItem(itemStoreCurrentHeight);






	auto itemStoreNewHeight = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreNewHeight->InitMenuItemProperty(al_ustr_new(""));
	itemStoreNewHeight->SetOptionId(AcedSharedDLL::OPTIONTYPES::HEIGHTOPTION);
	itemStoreNewHeight->SetMenuItemText(std::string("New Height:"));
	AddMenuItem(itemStoreNewHeight);




	auto itemStoreSave = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreSave->SetId(AcedSharedDLL::STATES::SAVE);
	itemStoreSave->SetMenuItemText(std::string("Save"));
	AddMenuItem(itemStoreSave);

	auto itemStoreReturn = std::shared_ptr<AcedSharedDLL::MenuItem>(new AcedSharedDLL::MenuItem());
	itemStoreReturn->SetId(AcedSharedDLL::STATES::RETURN);
	itemStoreReturn->SetMenuItemText(std::string("Return"));
	AddMenuItem(itemStoreReturn);



	SetMenuX(200);
	SetMenuY(100);
	SetMenuWidth(400);
	SetMenuHeight(400);

	SetMenuHeaderX(200);
	SetMenuHeaderY(50);
	SetMenuHeaderWidth(400);
	SetMenuHeaderHeight(50);

	int i = 0;
	int xloc = 355;
	int yloc = 110;
	int yspacing = 50;
	for (i = 0; i < GetMenuItems().size(); i++)
	{
		GetMenuItems()[i]->SetMenuItemX(xloc);
		GetMenuItems()[i]->SetMenuItemPropertyX(400 + 100);
		GetMenuItems()[i]->SetMenuItemY(yloc);
		yloc = yloc + yspacing;
	}
	SetMenuHeight(yloc - GetMenuY());

	SetCurrentSelection();
}

