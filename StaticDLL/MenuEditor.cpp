#include "MenuTemplates.h"
#include "Menu.h"
#include "MenuItem.h"



namespace StaticDLL{


	MenuEditor::MenuEditor(Settings *settings){
		SetSettings(settings);
		InitMenu();
	}



	void MenuEditor::InitMenu(){
		SetFont(al_load_font("arial.ttf", 30, 0));

		SetMenuHeader("Editor Menu");
		SetId(EnumDLL::STATES::EDITORMAINMENU);
		
		MenuItem* itemStore = new MenuItem;
		itemStore->SetId(EnumDLL::STATES::NEW);
		itemStore->SetMenuItemText("New Map");
		AddMenuItem(itemStore);

		itemStore = new MenuItem;
		itemStore->SetId(EnumDLL::STATES::SAVE);
		itemStore->SetMenuItemText("Save Map");
		AddMenuItem(itemStore);

		itemStore = new MenuItem;
		itemStore->SetId(EnumDLL::STATES::LOAD);
		itemStore->SetMenuItemText("Load Map");
		AddMenuItem(itemStore);

		itemStore = new MenuItem;
		itemStore->SetId(EnumDLL::STATES::MAPOPTIONS);
		itemStore->SetMenuItemText("Map Options");
		AddMenuItem(itemStore);

		itemStore = new MenuItem;
		itemStore->SetId(EnumDLL::STATES::OPTIONS);
		itemStore->SetMenuItemText("Options");
		AddMenuItem(itemStore);

		itemStore = new MenuItem;
		itemStore->SetId(EnumDLL::STATES::ABOUT);
		itemStore->SetMenuItemText("About");
		AddMenuItem(itemStore);
		
		itemStore = new MenuItem;
		itemStore->SetId(EnumDLL::STATES::RETURN);
		itemStore->SetMenuItemText("Return");
		AddMenuItem(itemStore);

		itemStore = new MenuItem;
		itemStore->SetId(EnumDLL::STATES::MAINMENU);
		itemStore->SetMenuItemText("Quit");
		AddMenuItem(itemStore);


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
		for(i = 0; i < GetMenuItems().size(); i++)
		{
			//printf("%i\n",yloc);
			GetMenuItems()[i]->SetMenuItemX(xloc);
			GetMenuItems()[i]->SetMenuItemY(yloc);
			yloc = yloc + yspacing;
		}
		SetMenuHeight(yloc-GetMenuY());

		SetCurrentSelection();
	}




}