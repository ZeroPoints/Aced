#ifndef MENUTEMPLATES_H
#define MENUTEMPLATES_H


#include <vector>
#include <allegro5\allegro.h>
#include <allegro5/allegro_primitives.h>
#include <algorithm>



#include "../AcedSharedDLL/Menu/Menu.h"
#include "../AcedSharedDLL/Menu/MenuItem.h"
#include "../AcedSharedDLL/Static/Definitions.h"


#include "../Settings/Settings.h"




//-------------------------------------------------Editor mode Menus-------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------


//This is the Main editing mode menu
class MenuEditorMain : public AcedSharedDLL::Menu
{
public:
	MenuEditorMain(Settings *settings);
private:
};
//This is the in editing esc(menu) 
class MenuEditor : public AcedSharedDLL::Menu
{
public:
	MenuEditor(Settings *settings);
private:
};

//This is the map options menu
class MenuMapOptions : public AcedSharedDLL::Menu
{
public:
	MenuMapOptions(Settings *settings, AcedSharedDLL::Map *currentMap);

private:

};





//-------------------------------------------------Shared mode Menus-------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------


//This is the menu options for generic settings
class MenuOptions : public AcedSharedDLL::Menu
{
public:
	MenuOptions(Settings *settings, AcedSharedDLL::Map *currentMap);

private:

};


//-------------------------------------------------Game mode Menus-------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------



//This is the Main menu in gameplay
class MenuGameMain : public AcedSharedDLL::Menu
{
public:
	MenuGameMain(Settings *settings);
private:
};

#endif
