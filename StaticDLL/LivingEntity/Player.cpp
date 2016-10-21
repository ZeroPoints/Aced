#include "player.h"

namespace StaticDLL {

	Player::Player(Settings *settings, Map *map)
	{

		hasText_ = false;
		movespeed_ = 0;
		currentRotation_ = 0;
		hasImage_ = false;
		hasColor_ = false;
		hasImageReference_ = false;

		settings_ = settings;
		map_ = map;
		KeyLeft_ = false;
		KeyRight_ = false;
		KeySpace_ = false;
		SetCurrentPosition(map_->GetMapWidth() / Constants::TileSize() + 1, map_->GetMapHeight() / Constants::TileSize() + 1);
		SetColor(al_map_rgb_f(1, 1, 1));
		SetWidth(0.8);
		SetHeight(0.8);

		SetGravityY(-9.8);
		SetVelocityY(0.125);
		SetMaxVelocityY(1);
		SetAccelerationY(0.03125);


		SetMoveSpeedDelta(0.125);
		SetMoveSpeed(30);
		SetJumpSpeed(12);
		font30_ = al_load_font("arial.ttf", 20, 0);




		SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING);



	}





	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//Sets



	void Player::SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES characterState)
	{
		characterYAxisState_ = characterState;
	}

	void Player::SetHealth(int hp)
	{
		health_ = hp;
	}



	void Player::SetCurrentPosition(double x, double y) {
		currentPositionX_ = x;
		currentPositionY_ = y;
	}
	void Player::SetColor(ALLEGRO_COLOR color) {
		chosenColor_ = color;
	}
	void Player::SetWidth(double val) {
		width_ = val;
	}
	void Player::SetHeight(double val) {
		height_ = val;
	}
	void Player::SetGravityY(double val) {
		gravityY_ = val;
	}
	void Player::SetVelocityY(double val) {
		velocityY_ = val;
	}
	void Player::SetMaxVelocityY(double val) {
		maxVelocityY_ = val;
	}
	void Player::SetAccelerationY(double val) {
		accelerationY_ = val;
	}
	void Player::SetMoveSpeedDelta(double val) {
		movespeedDelta_ = val;
	}
	void Player::SetMoveSpeed(double val) {
		movespeed_ = val;
	}
	void Player::SetJumpSpeed(double val) {
		jumpspeed_ = val;
	}

	void Player::SetCurrentPositionX(double val) {
		currentPositionX_ = val;
	}

	void Player::SetCurrentPositionY(double val) {
		currentPositionY_ = val;
	}


	void Player::SetPlayerFacingDirection(EnumDLL::CHARACTERFACINGDIRECTION direction)
	{
		faceDirection_ = direction;
	}


	void Player::SetObjectImageColor(Image *image)
	{
		if (image->GetImage() != nullptr)
		{
			hasImage_ = true;
			image_ = image;
			height_ = image->GetHeight();
			width_ = image->GetWidth();
		}
		else
		{
			hasColor_ = true;
			chosenColor_ = image->GetColor();
		}
	}



	void Player::SetKeyRight(bool val) {
		KeyRight_ = val;
	}
	void Player::SetKeyLeft(bool val) {
		KeyLeft_ = val;
	}





	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//Gets





	EnumDLL::CHARACTERFACINGDIRECTION Player::GetPlayerFacingDirection()
	{
		return faceDirection_;
	}



	double Player::GetCurrentPositionX() {
		return currentPositionX_;
	};


	double Player::GetCurrentPositionY() {
		return currentPositionY_;
	};


	EnumDLL::CHARACTERYAXISSTATES Player::GetCharacterYAxisState()
	{
		return characterYAxisState_;
	}



	double Player::GetHealth()
	{
		return health_;
	}


	double Player::GetVelocityY() {
		return velocityY_;
	}
	double Player::GetMaxVelocityY() {
		return maxVelocityY_;
	}
	double Player::GetAccelerationY() {
		return accelerationY_;
	}



	double Player::GetJumpSpeed() {
		return jumpspeed_;
	}




	double Player::GetHeight() {
		return height_;
	}
	double Player::GetWidth() {
		return width_;
	}

	double Player::GetMoveSpeed() {
		return movespeed_;
	}
	double Player::GetMoveSpeedDelta() {
		return movespeedDelta_;
	}



	bool Player::GetKeyRight() {
		return KeyRight_;
	}
	bool Player::GetKeyLeft() {
		return KeyLeft_;
	}





	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//Misc


	void Player::AdjustHealth(int hp) {
		health_ = health_ + hp;
	}



	void Player::AdjustPlayerRotation()
	{
		if (EnumDLL::CHARACTERFACINGDIRECTION::CHARACTERLEFT == faceDirection_)
		{
			currentRotation_ = currentRotation_ - 0.005;
		}
		else
		{
			currentRotation_ = currentRotation_ + 0.005;
		}
	}





	void Player::DrawObjectRotate() {
		//0.8




		if (hasImage_ &&  hasColor_)
		{
			al_draw_tinted_scaled_rotated_bitmap(
				image_->GetImage(),
				chosenColor_,
				image_->GetImageWidth() / 2.0,
				image_->GetImageHeight() / 2.0,
				(currentPositionX_ + width_ / 2)*Constants::TileSize() + map_->GetMapXOffset(),
				(currentPositionY_ + height_ / 2)*Constants::TileSize() + map_->GetMapYOffset(),
				width_*Constants::TileSize() / (image_->GetImageWidth()*1.0),
				height_*Constants::TileSize() / (image_->GetImageHeight()*1.0),
				currentRotation_,
				0
			);
		}
		else if (hasImage_)
		{
			al_draw_scaled_rotated_bitmap(
				image_->GetImage(),
				image_->GetImageWidth() / 2.0,
				image_->GetImageHeight() / 2.0,
				(currentPositionX_ + width_ / 2)*Constants::TileSize() + map_->GetMapXOffset(),
				(currentPositionY_ + height_ / 2)*Constants::TileSize() + map_->GetMapYOffset(),
				width_*Constants::TileSize() / (image_->GetImageWidth()*1.0),
				height_*Constants::TileSize() / (image_->GetImageHeight()*1.0),
				currentRotation_,
				0
			);
		}
	};






























	int Player::Keypress(ALLEGRO_EVENT *ev)
	{
		int val = -2;
		if (ev->type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev->keyboard.keycode)
			{
			case ALLEGRO_KEY_SPACE:
				if (GetCharacterYAxisState() == EnumDLL::CHARACTERYAXISSTATES::CHARACTERONGROUND)
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
		if (ev->type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev->keyboard.keycode)
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
		if (KeyRight_)
		{
			CollisionMovingRight();
		}
		else if (KeyLeft_)
		{
			CollisionMovingLeft();
		}


		//Characters forever in a state of falling?
		if (GetCharacterYAxisState() == EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING ||
			GetCharacterYAxisState() == EnumDLL::CHARACTERYAXISSTATES::CHARACTERONGROUND)
		{
			Falling();
		}
		else if (GetCharacterYAxisState() == EnumDLL::CHARACTERYAXISSTATES::CHARACTERJUMPING)
		{
			Jumping();
		}

	}




	//this is moving in X direction
	bool Player::CheckNextXPositionGoingLeft(float nextPosX, float nextPosY)
	{
		double height = GetHeight()*Constants::TileSize();

		//check if tile is going off bounds return false;
		if ((nextPosX) / Constants::TileSize() < 0) {
			return false;
		}

		for (int i = 0; i < height; i++)
		{
			Cell *cellFuture = &map_->GetCellMap()[(nextPosX) / Constants::TileSize()][(nextPosY + i) / Constants::TileSize()];
			if (cellFuture->GetTileType() == EnumDLL::TILETYPE::SOLIDTILE || cellFuture->GetTileType() == EnumDLL::TILETYPE::COLLISIONRIGHTTILE)
			{
				return false;
			}
		}
		return true;
	}
	bool Player::CheckNextXPositionGoingRight(float nextPosX, float nextPosY)
	{
		double height = GetHeight()*Constants::TileSize();

		//check if tile is going off bounds return false;
		if ((nextPosX) / Constants::TileSize() + GetWidth() > map_->GetMapWidth()) {
			return false;
		}

		for (int i = 0; i < height; i++)
		{
			Cell *cellFuture = &map_->GetCellMap()[(nextPosX) / Constants::TileSize() + GetWidth()][(nextPosY + i) / Constants::TileSize()];
			if (cellFuture->GetTileType() == EnumDLL::TILETYPE::SOLIDTILE || cellFuture->GetTileType() == EnumDLL::TILETYPE::COLLISIONLEFTTILE)
			{
				return false;
			}
		}
		return true;
	}




	//this is moving in Y direction
	bool Player::CheckNextYPositionFalling(float nextPosX, float nextPosY)
	{
		double width = GetWidth()*Constants::TileSize();
		//check if tile is going off bounds return false;
		if ((nextPosY) / Constants::TileSize() + GetHeight() >= map_->GetMapHeight()) {
			SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERONGROUND);
			SetVelocityY(0.125);
			//set no moving
			return false;
		}
		for (int i = 0; i < width; i++)
		{
			Cell *cellFuture = &map_->GetCellMap()[(nextPosX + i) / Constants::TileSize()][(nextPosY) / Constants::TileSize() + GetHeight()];
			if (cellFuture->GetTileType() == EnumDLL::TILETYPE::SOLIDTILE || cellFuture->GetTileType() == EnumDLL::TILETYPE::COLLISIONTOPTILE)
			{
				SetCurrentPositionY(cellFuture->GetCurrentPositionY() - GetHeight());
				SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERONGROUND);
				SetVelocityY(0.125);
				return false;
			}
		}
		return true;
	}

	//this is moving in Y direction
	bool Player::CheckNextYPositionJumping(float nextPosX, float nextPosY)
	{
		double width = GetWidth()*Constants::TileSize();
		//check if tile is going off bounds return false;
		if ((nextPosY) / Constants::TileSize() < 0) {
			SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING);
			SetVelocityY(0.125);
			//set no moving
			return false;
		}
		for (int i = 0; i < width; i++)
		{
			Cell *cellFuture = &map_->GetCellMap()[(nextPosX + i) / Constants::TileSize()][(nextPosY) / Constants::TileSize()];
			if (cellFuture->GetTileType() == EnumDLL::TILETYPE::SOLIDTILE)
			{
				SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING);
				SetVelocityY(0.125);
				return false;
			}
		}
		return true;
	}


	void Player::CollisionMovingLeft()
	{
		SetPlayerFacingDirection(EnumDLL::CHARACTERFACINGDIRECTION::CHARACTERLEFT);
		for (int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosX = GetCurrentPositionX()*Constants::TileSize() - GetMoveSpeedDelta();
			if (CheckNextXPositionGoingLeft(nextPosX, GetCurrentPositionY()*Constants::TileSize()))
			{
				AdjustPlayerRotation();

				SetCurrentPositionX(nextPosX / Constants::TileSize());
				if (map_->GetMapXOffset() >= 0 || nextPosX + map_->GetMapXOffset() >= settings_->GetScreenWidth() / 2)
				{
				}
				else
				{
					map_->SetMapMoveXDelta(GetMoveSpeedDelta());
					map_->SetMapXOffset(map_->GetMapXOffset() + GetMoveSpeedDelta());
				}
			}
		}
	}




	void Player::CollisionMovingRight()
	{
		SetPlayerFacingDirection(EnumDLL::CHARACTERFACINGDIRECTION::CHARACTERRIGHT);
		for (int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosX = GetCurrentPositionX()*Constants::TileSize() + GetMoveSpeedDelta();
			if (CheckNextXPositionGoingRight(nextPosX, GetCurrentPositionY()*Constants::TileSize()))
			{
				AdjustPlayerRotation();
				SetCurrentPositionX(nextPosX / Constants::TileSize());
				if (map_->GetMapWidth() * Constants::TileSize() + map_->GetMapXOffset() - settings_->GetScreenWidth() <= 0 || nextPosX <= settings_->GetScreenWidth() / 2)
				{

				}
				else
				{
					map_->SetMapMoveXDelta(- GetMoveSpeedDelta());
					map_->SetMapXOffset(map_->GetMapXOffset() - GetMoveSpeedDelta());
				}
			}
			else
			{
				AdjustPlayerRotation();

			}
			//If im going right but am as close as movespeed delta as possible do another check and fudge closer
		}
	}




	void Player::Falling()
	{
		for (int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosY = GetCurrentPositionY()*Constants::TileSize() + GetVelocityY();
			if (CheckNextYPositionFalling(GetCurrentPositionX()*Constants::TileSize(), nextPosY))
			{
				SetCurrentPositionY(nextPosY / Constants::TileSize());
				if (map_->GetMapHeight() * Constants::TileSize() + map_->GetMapYOffset() - settings_->GetScreenHeight() <= 0 || nextPosY <= settings_->GetScreenHeight() / 2)
				{
				}
				else
				{
					map_->SetMapMoveYDelta(- GetVelocityY());
					map_->SetMapYOffset(map_->GetMapYOffset() - GetVelocityY());
				}
			}
			else {
				break;
			}
		}
		//Every tick update the fall speed
		if (GetVelocityY() + GetAccelerationY() <= GetMaxVelocityY() && GetCharacterYAxisState() != EnumDLL::CHARACTERYAXISSTATES::CHARACTERONGROUND)
		{
			SetVelocityY(GetVelocityY() + GetAccelerationY());
		}
	}







	void Player::Jumping()
	{
		for (int i = 0; i < GetJumpSpeed(); i++)
		{
			float nextPosY = GetCurrentPositionY()*Constants::TileSize() + GetVelocityY();
			if (CheckNextYPositionJumping(GetCurrentPositionX()*Constants::TileSize(), nextPosY))
			{
				SetCurrentPositionY(nextPosY / Constants::TileSize());
				if (map_->GetMapYOffset() >= 0 || nextPosY >= settings_->GetScreenHeight() / 2 - map_->GetMapYOffset())
				{
				}
				else
				{
					map_->SetMapMoveYDelta(- GetVelocityY());
					map_->SetMapYOffset(map_->GetMapYOffset() - GetVelocityY());
				}
			}
		}
		//Every tick update the fall speed
		if (GetVelocityY() + GetAccelerationY() <= 0)
		{
			SetVelocityY(GetVelocityY() + GetAccelerationY());
		}
		else
		{
			SetVelocityY(0.125);
			SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING);
		}
	}
}














