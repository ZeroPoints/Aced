#ifndef CHARACTER_H
#define CHARACTER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts


///////////////////make an items class
class Character
{
	

	public:
        Character();

		//sets
        void CharacterMoveX(int direction);
		void CharacterMoveY(int valuey);


		void setMoveSpeed(int valSpeed);
		void setHealth(int valHealth);
		void takeDamage(int valdmghealth);
		void heal(int valheal);
		void setjumpheight(int valjump);

		//gets
		int getMoveSpeed()
		{
			return movespeed_;
		}

		void drawCharacter();
		//health,x,y,movespeed,fallspeed,jumpspeed?,

    private:
		int health_;
		int x_;
		int futurex_;
		int y_;
		int futurey_;
		int movespeed_;
		int jumpheight_;
		int jumpspeed_;
		int fallspeed_;
		int characterstate_; //normal,falling,jumping.
		int defaultmovespeed_;
		
};
#endif