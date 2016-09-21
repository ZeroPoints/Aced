#include "Character.h"

namespace StaticDLL {

	Character::Character(Settings *settings, Map *map)
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
		SetVelocityY(0.1);
		SetMaxVelocityY(1);
		SetAccelerationY(0.02);


		SetMoveSpeedDelta(0.1);
		SetMoveSpeed(30);
		SetJumpSpeed(12);

		font30_ = al_load_font("arial.ttf", 20, 0);



		SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING);



		fprintf(stderr, "An Character Created\n");
	}



	

	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//Sets



	void Character::SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES characterState)
	{
		characterYAxisState_ = characterState;
	}

	void Character::SetHealth(int hp)
	{
		health_ = hp;
	}



	void Character::SetCurrentPosition(double x, double y) {
		currentPositionX_ = x;
		currentPositionY_ = y;
	}
	void Character::SetColor(ALLEGRO_COLOR color) {
		chosenColor_ = color;
	}
	void Character::SetWidth(double val) {
		width_ = val;
	}
	void Character::SetHeight(double val) {
		height_ = val;
	}
	void Character::SetGravityY(double val) {
		gravityY_ = val;
	}
	void Character::SetVelocityY(double val) {
		velocityY_ = val;
	}
	void Character::SetMaxVelocityY(double val) {
		maxVelocityY_ = val;
	}
	void Character::SetAccelerationY(double val) {
		accelerationY_ = val;
	}
	void Character::SetMoveSpeedDelta(double val) {
		movespeedDelta_ = val;
	}
	void Character::SetMoveSpeed(double val) {
		movespeed_ = val;
	}
	void Character::SetJumpSpeed(double val) {
		jumpspeed_ = val;
	}

	void Character::SetCurrentPositionX(double val) {
		currentPositionX_ = val;
	}

	void Character::SetCurrentPositionY(double val) {
		currentPositionY_ = val;
	}


	void Character::SetPlayerFacingDirection(EnumDLL::CHARACTERFACINGDIRECTION direction)
	{
		faceDirection_ = direction;
	}

	
	void Character::SetObjectImageColor(Image *image)
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



	void Character::SetKeyRight(bool val) {
		KeyRight_ = val;
	}
	void Character::SetKeyLeft(bool val) {
		KeyLeft_ = val;
	}





	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//Gets





	EnumDLL::CHARACTERFACINGDIRECTION Character::GetPlayerFacingDirection()
	{
		return faceDirection_;
	}



	double Character::GetCurrentPositionX() {
		return currentPositionX_;
	};


	double Character::GetCurrentPositionY() {
		return currentPositionY_;
	};


	EnumDLL::CHARACTERYAXISSTATES Character::GetCharacterYAxisState()
	{
		return characterYAxisState_;
	}



	double Character::GetHealth()
	{
		return health_;
	}


	double Character::GetVelocityY() {
		return velocityY_;
	}
	double Character::GetMaxVelocityY() {
		return maxVelocityY_;
	}
	double Character::GetAccelerationY() {
		return accelerationY_;
	}



	double Character::GetJumpSpeed() {
		return jumpspeed_;
	}




	double Character::GetHeight() {
		return height_;
	}
	double Character::GetWidth() {
		return width_;
	}

	double Character::GetMoveSpeed() {
		return movespeed_;
	}
	double Character::GetMoveSpeedDelta() {
		return movespeedDelta_;
	}



	bool Character::GetKeyRight() {
		return KeyRight_;
	}
	bool Character::GetKeyLeft() {
		return KeyLeft_;
	}





	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//Misc


	void Character::AdjustHealth(int hp) {
		health_ = health_ + hp;
	}



	void Character::AdjustPlayerRotation()
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





	void Character::DrawObjectRotate() {
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






























	int Character::Keypress(ALLEGRO_EVENT *ev)
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





	void Character::Update()
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
	bool Character::CheckNextXPositionGoingLeft(float nextPosX, float nextPosY)
	{
		double height = GetHeight()*Constants::TileSize();

		//check if tile is going off bounds return false;
		if ((nextPosX) / Constants::TileSize() < 0) {
			return false;
		}

		for (int i = 0; i < height; i++)
		{
			Tile *tileFutureRight1 = nullptr;
			tileFutureRight1 = &map_->GetTiles()[(nextPosX) / Constants::TileSize()][(nextPosY + i) / Constants::TileSize()];
			if (tileFutureRight1->GetTileType() == EnumDLL::TILETYPE::SOLIDTILE || tileFutureRight1->GetTileType() == EnumDLL::TILETYPE::COLLISIONRIGHTTILE)
			{
				return false;
			}
		}
		return true;
	}
	bool Character::CheckNextXPositionGoingRight(float nextPosX, float nextPosY)
	{
		double height = GetHeight()*Constants::TileSize();

		//check if tile is going off bounds return false;
		if ((nextPosX) / Constants::TileSize() + GetWidth() > map_->GetMapWidth()) {
			return false;
		}

		for (int i = 0; i < height; i++)
		{
			Tile *tileFuture = nullptr;
			tileFuture = &map_->GetTiles()[(nextPosX) / Constants::TileSize() + GetWidth()][(nextPosY + i) / Constants::TileSize()];
			if (tileFuture->GetTileType() == EnumDLL::TILETYPE::SOLIDTILE || tileFuture->GetTileType() == EnumDLL::TILETYPE::COLLISIONLEFTTILE)
			{
				return false;
			}
		}
		return true;
	}




	//this is moving in Y direction
	bool Character::CheckNextYPositionFalling(float nextPosX, float nextPosY)
	{
		double width = GetWidth()*Constants::TileSize();
		//check if tile is going off bounds return false;
		if ((nextPosY) / Constants::TileSize() + GetHeight() >= map_->GetMapHeight()) {
			SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERONGROUND);
			SetVelocityY(0.1);
			//set no moving
			return false;
		}
		for (int i = 0; i < width; i++)
		{
			Tile *tileFuture = nullptr;
			tileFuture = &map_->GetTiles()[(nextPosX + i) / Constants::TileSize()][(nextPosY) / Constants::TileSize() + GetHeight()];
			if (tileFuture->GetTileType() == EnumDLL::TILETYPE::SOLIDTILE || tileFuture->GetTileType() == EnumDLL::TILETYPE::COLLISIONTOPTILE)
			{
				SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERONGROUND);
				SetVelocityY(0.1);
				return false;
			}
		}
		return true;
	}

	//this is moving in Y direction
	bool Character::CheckNextYPositionJumping(float nextPosX, float nextPosY)
	{
		double width = GetWidth()*Constants::TileSize();
		//check if tile is going off bounds return false;
		if ((nextPosY) / Constants::TileSize() < 0) {
			SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING);
			SetVelocityY(0.1);
			//set no moving
			return false;
		}
		for (int i = 0; i < width; i++)
		{
			Tile *tileFuture = nullptr;
			tileFuture = &map_->GetTiles()[(nextPosX + i) / Constants::TileSize()][(nextPosY) / Constants::TileSize()];
			if (tileFuture->GetTileType() == EnumDLL::TILETYPE::SOLIDTILE)
			{
				SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING);
				SetVelocityY(0.1);
				return false;
			}
		}
		return true;
	}


	void Character::CollisionMovingLeft()
	{
		SetPlayerFacingDirection(EnumDLL::CHARACTERFACINGDIRECTION::CHARACTERLEFT);
		for (int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosX = GetCurrentPositionX()*Constants::TileSize() - GetMoveSpeedDelta();

			if (CheckNextXPositionGoingLeft(nextPosX, GetCurrentPositionY()*Constants::TileSize()))
			{
				AdjustPlayerRotation();


				SetCurrentPositionX(nextPosX / Constants::TileSize());
				
			}
		}
	}




	void Character::CollisionMovingRight()
	{
		SetPlayerFacingDirection(EnumDLL::CHARACTERFACINGDIRECTION::CHARACTERRIGHT);
		for (int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosX = GetCurrentPositionX()*Constants::TileSize() + GetMoveSpeedDelta();

			if (CheckNextXPositionGoingRight(nextPosX, GetCurrentPositionY()*Constants::TileSize()))
			{
				AdjustPlayerRotation();
				SetCurrentPositionX(nextPosX / Constants::TileSize());
				

			}
		}
	}




	void Character::Falling()
	{
		for (int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosY = GetCurrentPositionY()*Constants::TileSize() + GetVelocityY();
			if (CheckNextYPositionFalling(GetCurrentPositionX()*Constants::TileSize(), nextPosY))
			{
				SetCurrentPositionY(nextPosY / Constants::TileSize());
				
			}
		}
		//Every tick update the fall speed
		if (GetVelocityY() + GetAccelerationY() <= GetMaxVelocityY())
		{
			SetVelocityY(GetVelocityY() + GetAccelerationY());
		}
	}







	void Character::Jumping()
	{
		for (int i = 0; i < GetJumpSpeed(); i++)
		{
			float nextPosY = GetCurrentPositionY()*Constants::TileSize() + GetVelocityY();
			if (CheckNextYPositionJumping(GetCurrentPositionX()*Constants::TileSize(), nextPosY))
			{
				SetCurrentPositionY(nextPosY / Constants::TileSize());
			}
		}
		//Every tick update the fall speed
		if (GetVelocityY() + GetAccelerationY() <= 0)
		{
			SetVelocityY(GetVelocityY() + GetAccelerationY());
		}
		else
		{
			SetVelocityY(0.1);
			SetCharacterYAxisState(EnumDLL::CHARACTERYAXISSTATES::CHARACTERFALLING);
		}
	}









	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//------------
	//------------
	//------------






}