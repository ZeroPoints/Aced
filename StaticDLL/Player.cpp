#include "player.h"

namespace StaticDLL{

	Player::Player()
	{
		score_ = 0;
		lives_ = 1;
		KeyLeft_ = false;
		KeyRight_ = false;
		KeySpace_ = false;
	}


	void Player::AdjustLives(int num)
	{
		lives_ = lives_ + num;
	}
	



	int Player::PlayerKeypress(ALLEGRO_EVENT ev)
	{
		ev_ = ev;
		int val = -2;
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

}