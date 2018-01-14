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
	MenuEditorMain(std::shared_ptr<Settings> &settings);
private:
};
//This is the in editing esc(menu) 
class MenuEditor : public AcedSharedDLL::Menu
{
public:
	MenuEditor(std::shared_ptr<Settings> &settings);
private:
};

//This is the map options menu
class MenuMapOptions : public AcedSharedDLL::Menu
{
public:
	MenuMapOptions(std::shared_ptr<Settings> &settings, std::shared_ptr<AcedSharedDLL::Map> &currentMap);

private:

};





//-------------------------------------------------Shared mode Menus-------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------


//This is the menu options for generic settings
class MenuOptions : public AcedSharedDLL::Menu
{
public:
	MenuOptions(std::shared_ptr<Settings> &settings, std::shared_ptr<AcedSharedDLL::Map> &currentMap);

private:

};


//-------------------------------------------------Game mode Menus-------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------



//This is the Main menu in gameplay
class MenuGameMain : public AcedSharedDLL::Menu
{
public:
	MenuGameMain(std::shared_ptr<Settings> &settings);
private:
};

#endif
