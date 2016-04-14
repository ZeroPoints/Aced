#include "player.h"
#include "map.h"

namespace StaticDLL{

	Player::Player()
	{
		score_ = 0;
		lives_ = 1;
		KeyLeft_ = false;
		KeyRight_ = false;
		KeySpace_ = false;
		SetCurrentPosition(10,10);
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





	void Player::Update(Map *map)
	{
		if(KeyRight_)
		{
			CollisionMovingRight(map);
		}
		else if(KeyLeft_)
		{
			CollisionMovingLeft(map);
		}


		//Characters forever in a state of falling?
		if(GetCharacterYAxisState() == EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING || 
			GetCharacterYAxisState() == EnumDLL::CHARACTERYAXISSTATES::CHARACTERONGROUND)
		{
			Falling(map);
		}
		else if(GetCharacterYAxisState() == EnumDLL::CHARACTERYAXISSTATES::CHARACTERJUMPING)
		{
			Jumping(map);
		}

	}




	//this is moving in X direction
	bool Player::CheckNextXPositionGoingLeft(Map* map, float nextPosX, float nextPosY)
	{
		double height = GetHeight()*Constants::TileSize;

		//check if tile is going off bounds return false;
		if((nextPosX - map->GetMapXOffset())/Constants::TileSize < 0){
			return false;
		}

		for(int i = 0; i < height; i++)
		{
			Tile *tileFutureRight1 = nullptr;
			tileFutureRight1 = &map->GetTiles()[(nextPosX - map->GetMapXOffset())/Constants::TileSize][(nextPosY + i - map->GetMapYOffset())/Constants::TileSize];
			if(tileFutureRight1->GetTileType() == EnumDLL::TILETYPE::SOLIDTILE || tileFutureRight1->GetTileType() == EnumDLL::TILETYPE::COLLISIONRIGHTTILE)
			{
				return false;
			}
		}
		return true;
	}
	bool Player::CheckNextXPositionGoingRight(Map* map, float nextPosX, float nextPosY)
	{
		double height = GetHeight()*Constants::TileSize;

		//check if tile is going off bounds return false;
		if((nextPosX - map->GetMapXOffset())/Constants::TileSize + GetWidth() > map->GetMapWidth()){
			return false;
		}

		for(int i = 0; i < height; i++)
		{
			Tile *tileFuture = nullptr;
			tileFuture = &map->GetTiles()[(nextPosX - map->GetMapXOffset())/Constants::TileSize + GetWidth()][(nextPosY + i - map->GetMapYOffset())/Constants::TileSize];
			if(tileFuture->GetTileType() == EnumDLL::TILETYPE::SOLIDTILE || tileFuture->GetTileType() == EnumDLL::TILETYPE::COLLISIONLEFTTILE)
			{
				return false;
			}
		}
		return true;
	}




	//this is moving in Y direction
	bool Player::CheckNextYPositionFalling(Map* map, float nextPosX, float nextPosY)
	{
		double width = GetWidth()*Constants::TileSize;
		//check if tile is going off bounds return false;
		if((nextPosY - map->GetMapYOffset())/Constants::TileSize + GetHeight() > map->GetMapHeight()){
			SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERONGROUND);
			SetVelocityY(0.1);
			//set no moving
			return false;
		}
		for(int i = 0; i < width; i++)
		{
			Tile *tileFuture = nullptr;
			tileFuture = &map->GetTiles()[(nextPosX + i - map->GetMapXOffset())/Constants::TileSize][(nextPosY - map->GetMapYOffset())/Constants::TileSize + GetHeight()];
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
	bool Player::CheckNextYPositionJumping(Map* map, float nextPosX, float nextPosY)
	{
		double width = GetWidth()*Constants::TileSize;
		//check if tile is going off bounds return false;
		if((nextPosY - map->GetMapYOffset())/Constants::TileSize < 0){
			SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING);
			SetVelocityY(0.1);
			//set no moving
			return false;
		}
		for(int i = 0; i < width; i++)
		{
			Tile *tileFuture = nullptr;
			tileFuture = &map->GetTiles()[(nextPosX + i - map->GetMapXOffset())/Constants::TileSize][(nextPosY - map->GetMapYOffset())/Constants::TileSize];
			if(tileFuture->GetTileType() == EnumDLL::TILETYPE::SOLIDTILE)
			{
				SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING);
				SetVelocityY(0.1);
				return false;
			}
		}
		return true;
	}


	void Player::CollisionMovingLeft(Map* map)
	{
		for(int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosX = GetCurrentPositionX()*Constants::TileSize - GetMoveSpeedDelta();
			if(CheckNextXPositionGoingLeft(map, nextPosX, GetCurrentPositionY()*Constants::TileSize))
			{
				SetCurrentPositionX(nextPosX/Constants::TileSize);
			}
		}
	}




	void Player::CollisionMovingRight(Map* map)
	{
		for(int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosX = GetCurrentPositionX()*Constants::TileSize + GetMoveSpeedDelta();
			if(CheckNextXPositionGoingRight(map, nextPosX, GetCurrentPositionY()*Constants::TileSize))
			{
				SetCurrentPositionX(nextPosX/Constants::TileSize);
			}
		}
	}




	void Player::Falling(Map* map)
	{
		for(int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosY = GetCurrentPositionY()*Constants::TileSize + GetVelocityY();
			if(CheckNextYPositionFalling(map, GetCurrentPositionX()*Constants::TileSize, nextPosY))
			{
				SetCurrentPositionY(nextPosY/Constants::TileSize);
			}
		}
		//Every tick update the fall speed
		if(GetVelocityY() + GetAccelerationY() <= GetMaxVelocityY())
		{
			SetVelocityY(GetVelocityY() + GetAccelerationY());
		}
	}

	





	void Player::Jumping(Map* map)
	{
		for(int i = 0; i < GetJumpSpeed(); i++)
		{
			float nextPosY = GetCurrentPositionY()*Constants::TileSize + GetVelocityY();
			if(CheckNextYPositionJumping(map, GetCurrentPositionX()*Constants::TileSize, nextPosY))
			{
				SetCurrentPositionY(nextPosY/Constants::TileSize);
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