#include "character.h"

Character::Character()
{
	characterstate_ = 0;
	health_ = 1;
	x_ = 10;//get this from loading map so pass it in?
	futurex_ = x_;
	y_ = 10;//get this from loading map so pass it in?
	futurey_ = y_;
	defaultmovespeed_ = 5;
	movespeed_ = defaultmovespeed_;
	fallspeed_ = 5;
	jumpspeed_ = 5;
	jumpheight_ = 5;
}

void Character::CharacterMoveX(int direction)
{
	futurex_ = x_ + (movespeed_*direction);
	//validation that its a valid move...void collisioncheck(x,y)?
	x_ = futurex_; //if true//else do a lesser value so your char can move closer to wall object/?

}

void Character::CharacterMoveY(int valuey)
{
	futurey_ = y_ + valuey;
	//validation that its a valid move...void collisioncheck(x,y)?
	y_ = futurey_; //if true//else do a lesser value so your char can move closer to wall object/?

}

void Character::drawCharacter()
{
	al_draw_filled_rectangle(x_, y_, x_ + 20, y_ + 20, al_map_rgb_f(1,1,1));//6
}

void Character::heal(int valheal)
{
	health_ = health_ + valheal;
}

void Character::setHealth(int valhealth)
{
	health_ = valhealth;
}

void Character::takeDamage(int valdmghealth)
{
	health_ = health_ - valdmghealth;
}

void Character::setjumpheight(int valjumpheight)
{
	jumpheight_ = valjumpheight;
}