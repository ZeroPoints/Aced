#ifndef STATETEMPLATES_H
#define STATETEMPLATES_H



#include <allegro5\allegro.h>
#include <vector>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include <allegro5\allegro_primitives.h>//shapes
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_physfs.h>

#include "../AcedSharedDLL/States/State.h"
#include "../Aced/Engine/Menus/MenuTemplates.h"
#include "../AcedSharedDLL/World/Map.h"

#include "../Aced/Engine/Settings/Settings.h"


//-------------------------------------------------Editor mode States-------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------

//This is the Main editing mode state whilst editing maps
class StateEditorMode : public AcedSharedDLL::State
{
public:

	 ~StateEditorMode()
	{
		//fprintf(stderr, "A StateEditorMode Destructed\n");
		delete editorOverLayController_;
	}

	 StateEditorMode(ALLEGRO_DISPLAY *display, Settings *settings, AcedSharedDLL::Map *currentMap, AcedSharedDLL::AssetLibrary *assetLibrary);
	////key press probs goes in update
	 void KeyPress();
	 void MouseActivity();
	 void EditorModeMouseActivity();
	 void Update();
	 void Draw();
	 void Resume();
	 void DragMap();
private:
	//This object isnt being Deleted at the moment
	AcedSharedDLL::EditorOverLayController *editorOverLayController_;

	std::pair<AcedSharedDLL::STATES, AcedSharedDLL::EditorItemBase*> selectedItemBase_;
};



//Main menu for edit app
class StateEditorMainMenu : public AcedSharedDLL::State
{
public:
	StateEditorMainMenu(ALLEGRO_DISPLAY *display, Settings *settings, AcedSharedDLL::Map *currentMap, AcedSharedDLL::AssetLibrary *assetLibrary);
	////key press probs goes in update
	 void KeyPress();
	 void Update();
	 void Draw();
	 void Resume();
private:
};





//Menu inside editor whilst editing
class StateEditorMenu : public AcedSharedDLL::State
{
public:
	StateEditorMenu(ALLEGRO_DISPLAY *display, Settings *settings, AcedSharedDLL::Map *currentMap, AcedSharedDLL::AssetLibrary *assetLibrary);
	////key press probs goes in update
	 void KeyPress();
	 void Update();
	 void Draw();
	 void Resume();
	 void CleanUp();
private:
};




//Map resizing and customisation options
class StateMapOptions : public AcedSharedDLL::State
{
public:
	StateMapOptions(ALLEGRO_DISPLAY *display, Settings *settings, AcedSharedDLL::Map *currentMap, AcedSharedDLL::AssetLibrary *assetLibrary);
	////key press probs goes in update
	 void KeyPress();
	 void Update();
	 void Draw();
private:
};









//-------------------------------------------------Shared mode States-------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------



//Application options menu
class StateOptions : public AcedSharedDLL::State
{
public:
	StateOptions(ALLEGRO_DISPLAY *display, Settings *settings, AcedSharedDLL::Map *currentMap, AcedSharedDLL::AssetLibrary *assetLibrary);
	////key press probs goes in update
	 void KeyPress();
	 void Update();
	 void Draw();
private:
};




//-------------------------------------------------Game mode States-------------------------------------------------
//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------



//Application game state for game play
class StateGameMode : public AcedSharedDLL::State
{
public:
	StateGameMode(ALLEGRO_DISPLAY *display, Settings *settings, AcedSharedDLL::Map *currentMap, AcedSharedDLL::AssetLibrary *assetLibrary);
	////key press probs goes in updateAcedSharedDLL::
	 void KeyPress();
	 void MouseActivity();
	 void Update();
	 void Draw();
	 void Resume();
private:
	std::vector<AcedSharedDLL::Player*> players_;
	AcedSharedDLL::Player* player1_;


};




//Application main menu
class StateGameMainMenu : public AcedSharedDLL::State
{
public:

	StateGameMainMenu(ALLEGRO_DISPLAY *display, Settings *settings, AcedSharedDLL::Map *currentMap, AcedSharedDLL::AssetLibrary *assetLibrary);


	////key press probs goes in update
	 void KeyPress();
	 void Update();
	 void Draw();
	 void Resume();
private:

};




#endif


