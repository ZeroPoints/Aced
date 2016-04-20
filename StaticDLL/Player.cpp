#include "player.h"
#include "map.h"

namespace StaticDLL{

	Player::Player(Settings *settings, Map *map)
	{
		settings_ = settings;
		map_ = map;
		score_ = 0;
		lives_ = 1;
		KeyLeft_ = false;
		KeyRight_ = false;
		KeySpace_ = false;
		SetCurrentPosition(map_->GetMapXOffset()/Constants::TileSize+1,map_->GetMapYOffset()/Constants::TileSize+1);
		SetColor(al_map_rgb_f(1,1,1));
		SetWidth(0.8);
		SetHeight(0.8);

		SetGravityY(-9.8);
		SetVelocityY(0.1);
		SetMaxVelocityY(1);
		SetAccelerationY(0.02);


		SetMoveSpeedDelta(0.1);
		SetMoveSpeed(30);
		SetJumpSpeed(12);




		SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING);
	}


	void Player::AdjustLives(int num)
	{
		lives_ = lives_ + num;
	}
	



	int Player::Keypress(ALLEGRO_EVENT *ev)
	{
		int val = -2;
		if(ev->type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev->keyboard.keycode)
			{		
				case ALLEGRO_KEY_SPACE:
					if(GetCharacterYAxisState() == EnumDLL::CHARACTERYAXISSTATES::CHARACTERONGROUND)
					{
						SetVelocityY(-0.5);
						SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERJUMPING);
						val = 1;
					}
					break;
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
		if(ev->type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev->keyboard.keycode)
			{		
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





	void Player::Update()
	{
		if(KeyRight_)
		{
			CollisionMovingRight();
		}
		else if(KeyLeft_)
		{
			CollisionMovingLeft();
		}


		//Characters forever in a state of falling?
		if(GetCharacterYAxisState() == EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING || 
			GetCharacterYAxisState() == EnumDLL::CHARACTERYAXISSTATES::CHARACTERONGROUND)
		{
			Falling();
		}
		else if(GetCharacterYAxisState() == EnumDLL::CHARACTERYAXISSTATES::CHARACTERJUMPING)
		{
			Jumping();
		}

	}




	//this is moving in X direction
	bool Player::CheckNextXPositionGoingLeft(float nextPosX, float nextPosY)
	{
		double height = GetHeight()*Constants::TileSize;

		//check if tile is going off bounds return false;
		if((nextPosX - map_->GetMapXOffset())/Constants::TileSize < 0){
			return false;
		}

		for(int i = 0; i < height; i++)
		{
			Tile *tileFutureRight1 = nullptr;
			tileFutureRight1 = &map_->GetTiles()[(nextPosX - map_->GetMapXOffset())/Constants::TileSize][(nextPosY + i - map_->GetMapYOffset())/Constants::TileSize];
			if(tileFutureRight1->GetTileType() == EnumDLL::TILETYPE::SOLIDTILE || tileFutureRight1->GetTileType() == EnumDLL::TILETYPE::COLLISIONRIGHTTILE)
			{
				return false;
			}
		}
		return true;
	}
	bool Player::CheckNextXPositionGoingRight(float nextPosX, float nextPosY)
	{
		double height = GetHeight()*Constants::TileSize;

		//check if tile is going off bounds return false;
		if((nextPosX - map_->GetMapXOffset())/Constants::TileSize + GetWidth() > map_->GetMapWidth()){
			return false;
		}

		for(int i = 0; i < height; i++)
		{
			Tile *tileFuture = nullptr;
			tileFuture = &map_->GetTiles()[(nextPosX - map_->GetMapXOffset())/Constants::TileSize + GetWidth()][(nextPosY + i - map_->GetMapYOffset())/Constants::TileSize];
			if(tileFuture->GetTileType() == EnumDLL::TILETYPE::SOLIDTILE || tileFuture->GetTileType() == EnumDLL::TILETYPE::COLLISIONLEFTTILE)
			{
				return false;
			}
		}
		return true;
	}




	//this is moving in Y direction
	bool Player::CheckNextYPositionFalling(float nextPosX, float nextPosY)
	{
		double width = GetWidth()*Constants::TileSize;
		//check if tile is going off bounds return false;
		if((nextPosY - map_->GetMapYOffset())/Constants::TileSize + GetHeight() >= map_->GetMapHeight()){
			SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERONGROUND);
			SetVelocityY(0.1);
			//set no moving
			return false;
		}
		for(int i = 0; i < width; i++)
		{
			Tile *tileFuture = nullptr;
			tileFuture = &map_->GetTiles()[(nextPosX + i - map_->GetMapXOffset())/Constants::TileSize][(nextPosY - map_->GetMapYOffset())/Constants::TileSize + GetHeight()];
			if(tileFuture->GetTileType() == EnumDLL::TILETYPE::SOLIDTILE || tileFuture->GetTileType() == EnumDLL::TILETYPE::COLLISIONTOPTILE)
			{
				SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERONGROUND);
				SetVelocityY(0.1);
				return false;
			}
		}
		return true;
	}

	//this is moving in Y direction
	bool Player::CheckNextYPositionJumping(float nextPosX, float nextPosY)
	{
		double width = GetWidth()*Constants::TileSize;
		//check if tile is going off bounds return false;
		if((nextPosY - map_->GetMapYOffset())/Constants::TileSize < 0){
			SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING);
			SetVelocityY(0.1);
			//set no moving
			return false;
		}
		for(int i = 0; i < width; i++)
		{
			Tile *tileFuture = nullptr;
			tileFuture = &map_->GetTiles()[(nextPosX + i - map_->GetMapXOffset())/Constants::TileSize][(nextPosY - map_->GetMapYOffset())/Constants::TileSize];
			if(tileFuture->GetTileType() == EnumDLL::TILETYPE::SOLIDTILE)
			{
				SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING);
				SetVelocityY(0.1);
				return false;
			}
		}
		return true;
	}


	void Player::CollisionMovingLeft()
	{
		for(int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosX = GetCurrentPositionX()*Constants::TileSize - GetMoveSpeedDelta();
			if(CheckNextXPositionGoingLeft(nextPosX, GetCurrentPositionY()*Constants::TileSize))
			{
				if(map_->GetMapXOffset() >= 0 || nextPosX >= settings_->GetScreenWidth()/2)
				{
					SetCurrentPositionX(nextPosX/Constants::TileSize);
				}
				else
				{
					map_->SetMapXOffset(map_->GetMapXOffset() + GetMoveSpeedDelta());
				}
			}
		}
	}




	void Player::CollisionMovingRight()
	{
		for(int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosX = GetCurrentPositionX()*Constants::TileSize + GetMoveSpeedDelta();
			if(CheckNextXPositionGoingRight(nextPosX, GetCurrentPositionY()*Constants::TileSize))
			{
				if(map_->GetMapWidth()*20 + map_->GetMapXOffset() - settings_->GetScreenWidth() <= 0 || nextPosX <= settings_->GetScreenWidth()/2)
				{
					SetCurrentPositionX(nextPosX/Constants::TileSize);
				}
				else
				{
					map_->SetMapXOffset(map_->GetMapXOffset() - GetMoveSpeedDelta());
				}
			}
		}
	}




	void Player::Falling()
	{
		for(int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosY = GetCurrentPositionY()*Constants::TileSize + GetVelocityY();
			if(CheckNextYPositionFalling(GetCurrentPositionX()*Constants::TileSize, nextPosY))
			{
				if(map_->GetMapHeight()*20 + map_->GetMapYOffset() - settings_->GetScreenHeight() <= 0 || nextPosY <= settings_->GetScreenHeight()/2)
				{
					SetCurrentPositionY(nextPosY/Constants::TileSize);
				}
				else
				{
					map_->SetMapYOffset(map_->GetMapYOffset() - GetVelocityY());
				}
			}
		}
		//Every tick update the fall speed
		if(GetVelocityY() + GetAccelerationY() <= GetMaxVelocityY())
		{
			SetVelocityY(GetVelocityY() + GetAccelerationY());
		}
	}

	





	void Player::Jumping()
	{
		for(int i = 0; i < GetJumpSpeed(); i++)
		{
			float nextPosY = GetCurrentPositionY()*Constants::TileSize + GetVelocityY();
			if(CheckNextYPositionJumping(GetCurrentPositionX()*Constants::TileSize, nextPosY))
			{
				if(map_->GetMapYOffset() >= 0 || nextPosY >= settings_->GetScreenHeight()/2)
				{
					SetCurrentPositionY(nextPosY/Constants::TileSize);
				}
				else
				{
					map_->SetMapYOffset(map_->GetMapYOffset() - GetVelocityY());
				}
			}
		}
		//Every tick update the fall speed
		if(GetVelocityY() + GetAccelerationY() <= 0)
		{
			SetVelocityY(GetVelocityY() + GetAccelerationY());
		}
		else
		{
			SetVelocityY(0.1);
			SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING);
		}
	}
}