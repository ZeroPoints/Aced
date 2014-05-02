#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <allegro5\allegro.h>
#include <vector>
#include "../MapEditor/menu.h"
#include <allegro5/allegro_primitives.h>

class MenuManager
{
    public:
        MenuManager(int menutype);

        void runMenu();
		void setMenu(int menunumber);
		int keyPress(ALLEGRO_EVENT ev);
		void menupdate();

		void editormenu();
		void gamemenu();

		std::vector<Menu> &getMenu()
		{
			return menu_;
		}

		void setCurrentSelection();

    private:
		int menutype_;
        std::vector<Menu> menu_;
		int menunumber_;
		ALLEGRO_EVENT ev_;
		int y_;
		int currentselection_;
		
};
#endif
