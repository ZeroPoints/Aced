#include "MenuTemplates.h"



MenuOptions::MenuOptions(Settings *settings, AcedSharedDLL::Map *currentMap) : Menu(settings) {
	
	SetMap(currentMap);
	SetFont(al_load_font("arial.ttf", 30, 0));

	SetMenuHeader("Options");
	SetId(AcedSharedDLL::STATES::EDITOROPTIONS);




	AcedSharedDLL::MenuItem* itemStore = new AcedSharedDLL::MenuItem;
	itemStore->SetMenuItemText("Current Width:");


	//might need to delete this tempval char array? mmm looks to be in stack so should die when method finishs....
	char tempVal[10];
	sprintf_s(tempVal, "%i", GetSettings()->GetScreenWidth());


	itemStore->InitMenuItemProperty(al_ustr_new(tempVal));
	itemStore->SetMenuItemTargetable(false);
	AddMenuItem(itemStore);





	itemStore = new AcedSharedDLL::MenuItem;
	itemStore->InitMenuItemProperty(al_ustr_new(""));
	itemStore->SetOptionId(AcedSharedDLL::OPTIONTYPES::WIDTHOPTION);
	itemStore->SetMenuItemText("New Width:");
	AddMenuItem(itemStore);




	itemStore = new AcedSharedDLL::MenuItem;
	itemStore->SetMenuItemText("Current Height:");

	sprintf_s(tempVal, "%i", GetSettings()->GetScreenHeight());

	itemStore->InitMenuItemProperty(al_ustr_new(tempVal));
	itemStore->SetMenuItemTargetable(false);
	AddMenuItem(itemStore);






	itemStore = new AcedSharedDLL::MenuItem;
	itemStore->InitMenuItemProperty(al_ustr_new(""));
	itemStore->SetOptionId(AcedSharedDLL::OPTIONTYPES::HEIGHTOPTION);
	itemStore->SetMenuItemText("New Height:");
	AddMenuItem(itemStore);




	itemStore = new AcedSharedDLL::MenuItem;
	itemStore->SetId(AcedSharedDLL::STATES::SAVE);
	itemStore->SetMenuItemText("Save");
	AddMenuItem(itemStore);

	itemStore = new AcedSharedDLL::MenuItem;
	itemStore->SetId(AcedSharedDLL::STATES::RETURN);
	itemStore->SetMenuItemText("Return");
	AddMenuItem(itemStore);



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





