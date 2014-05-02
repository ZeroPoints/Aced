#include "player.h"

Player::Player()
{
	score_ = 0;
	lives_ = 1;
	createPlayersCharacter();
	KeyLeft_ = false;
	KeyRight_ = false;
	KeySpace_ = false;
}

void Player::setLives(int num)
{
	lives_ = num;
}

void Player::deductlives(int num)
{
	lives_ = lives_ - num;
}
void Player::deductlives()
{
	lives_ = lives_--;
}

void Player::addlives(int num)
{
	lives_ = lives_ + num;
}
void Player::addlives()
{
	lives_ = lives_++;
}
void Player::createPlayersCharacter()
{
	character_ = new Character();
}



int Player::playerkeypress(ALLEGRO_EVENT ev)
{
	ev_ = ev;
	int val = -2                                                                                                                            ;
	if(ev_.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch(ev.keyboard.keycode)
		{			
			


			case ALLEGRO_KEY_RIGHT://choose later....
				KeyRight_ = true;
				break;
			case ALLEGRO_KEY_LEFT://choose later....
				KeyLeft_ = true;
				break;
			//case ALLEGRO_KEY_SPACE://choose later....
			//	KeySpace_ = true;
			//	break;
		}
	}
	if(ev_.type == ALLEGRO_EVENT_KEY_UP)
	{
		switch(ev.keyboard.keycode)
		{		
			case ALLEGRO_KEY_ESCAPE:						
				////load menu
				val = -1;
				KeyRight_ = false;
				KeyLeft_ = false;
				break;
			case ALLEGRO_KEY_RIGHT://choose later....
				KeyRight_ = false;
				break;
			case ALLEGRO_KEY_LEFT://choose later....
				KeyLeft_ = false;
				break;
			//case ALLEGRO_KEY_SPACE://choose later....
			//	KeySpace_ = false;
			//	break;
		}				
	}
	return val;
}

void Player::playerupdate()
{
	//sooo update position every60th second
	if(KeyLeft_ == true)
	{
		//modify to offset
		character_->CharacterMoveX(-1);
	}
	if(KeyRight_ == true)
	{
		character_->CharacterMoveX(1);
	}
}

void Player::drawPlayer()
{
	character_->drawCharacter();
}

void Player::passMap(Map mymap)
{
	maps_ = mymap;
}