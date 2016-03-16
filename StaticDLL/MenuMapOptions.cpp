#include "MenuTemplates.h"
#include "Menu.h"
#include "MenuItem.h"
#include "Map.h"

using namespace std;


namespace StaticDLL{

	
	MenuMapOptions::MenuMapOptions(Settings *settings, Map *currentMap){
		SetSettings(settings);
		SetMap(currentMap);
		InitMenu();
	}


	void MenuMapOptions::InitMenu(){
		SetFont(al_load_font("arial.ttf", 30, 0));

		SetMenuHeader("Map Options");
		SetId(EnumDLL::STATES::EDITORMAPOPTIONS);
		



		MenuItem* itemStore = new MenuItem;
		itemStore->SetMenuItemText("Current Width:");


		//might need to delete this tempval char array? mmm looks to be in stack so should die when method finishs....
		char tempVal[10];
		sprintf_s(tempVal, "%i", GetMap()->GetMapWidth());


		itemStore->InitMenuItemProperty(al_ustr_new(tempVal));
		itemStore->SetMenuItemTargetable(false);
		AddMenuItem(itemStore);





		itemStore = new MenuItem;
		itemStore->InitMenuItemProperty(al_ustr_new(""));
		itemStore->SetOptionId(EnumDLL::OPTIONTYPES::WIDTHOPTION);
		itemStore->SetMenuItemText("New Width:");
		AddMenuItem(itemStore);




		itemStore = new MenuItem;
		itemStore->SetMenuItemText("Current Height:");

		sprintf_s(tempVal, "%i", GetMap()->GetMapHeight());

		itemStore->InitMenuItemProperty(al_ustr_new(tempVal));
		itemStore->SetMenuItemTargetable(false);
		AddMenuItem(itemStore);






		itemStore = new MenuItem;
		itemStore->InitMenuItemProperty(al_ustr_new(""));
		itemStore->SetOptionId(EnumDLL::OPTIONTYPES::HEIGHTOPTION);
		itemStore->SetMenuItemText("New Height:");
		AddMenuItem(itemStore);




		itemStore = new MenuItem;
		itemStore->SetId(EnumDLL::STATES::SAVE);
		itemStore->SetMenuItemText("Save");
		AddMenuItem(itemStore);
		
		itemStore = new MenuItem;
		itemStore->SetId(EnumDLL::STATES::RETURN);
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
		for(i = 0; i < GetMenuItems().size(); i++)
		{
			GetMenuItems()[i]->SetMenuItemX(xloc);
			GetMenuItems()[i]->SetMenuItemPropertyX(400+100);
			GetMenuItems()[i]->SetMenuItemY(yloc);
			yloc = yloc + yspacing;
		}
		SetMenuHeight(yloc-GetMenuY());

		SetCurrentSelection();
	}




}