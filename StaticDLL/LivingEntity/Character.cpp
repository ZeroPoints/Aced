#include "Character.h"

namespace StaticDLL {

	Character::Character(Settings *settings, int mapWidth, int mapHeight, std::vector<std::vector<Cell>> *cellMap)
	{
		hasText_ = false;
		movespeed_ = 0;
		currentRotation_ = 0;
		hasImage_ = false;
		hasColor_ = false;
		hasImageReference_ = false;
		aiEnabled_ = true;

		mapWidth_ = mapWidth;
		mapHeight_ = mapHeight;

		cellMap_ = cellMap;


		settings_ = settings;
		KeyLeft_ = false;
		KeyRight_ = false;
		KeySpace_ = false;
		SetCurrentPosition(mapWidth_ / Constants::TileSize() + 1, mapHeight_ / Constants::TileSize() + 1);
		SetColor(al_map_rgb_f(1, 1, 1));
		SetWidth(0.8);
		SetHeight(0.8);

		SetGravityY(-9.8);
		SetVelocityY(0.125);
		SetMaxVelocityY(1);
		SetAccelerationY(0.03125);


		SetMoveSpeedDelta(0.0625);
		SetMoveSpeed(30);
		SetJumpSpeed(12);

		font30_ = al_load_font("arial.ttf", Constants::TileSize(), 0);



		SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERFALLING);



	}




	Character::~Character() {
		//fprintf(stderr, "An Character Destructed\n");
	}





	

	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//Sets



	void Character::SetCharacterYAxisState(CHARACTERYAXISSTATES characterState)
	{
		characterYAxisState_ = characterState;
	}

	void Character::SetHealth(int hp)
	{
		health_ = hp;
	}



	void Character::SetCurrentPosition(float x, float y) {
		currentPositionX_ = x;
		currentPositionY_ = y;
	}
	void Character::SetColor(ALLEGRO_COLOR color) {
		chosenColor_ = color;
	}
	void Character::SetWidth(float val) {
		width_ = val;
	}
	void Character::SetHeight(float val) {
		height_ = val;
	}
	void Character::SetGravityY(float val) {
		gravityY_ = val;
	}
	void Character::SetVelocityY(float val) {
		velocityY_ = val;
	}
	void Character::SetMaxVelocityY(float val) {
		maxVelocityY_ = val;
	}
	void Character::SetAccelerationY(float val) {
		accelerationY_ = val;
	}
	void Character::SetMoveSpeedDelta(float val) {
		movespeedDelta_ = val;
	}
	void Character::SetMoveSpeed(float val) {
		movespeed_ = val;
	}
	void Character::SetJumpSpeed(float val) {
		jumpspeed_ = val;
	}

	void Character::SetCurrentPositionX(float val) {
		currentPositionX_ = val;
	}

	void Character::SetCurrentPositionY(float val) {
		currentPositionY_ = val;
	}


	void Character::SetPlayerFacingDirection(CHARACTERFACINGDIRECTION direction)
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
		KeyLeft_ = !val;
	}
	void Character::SetKeyLeft(bool val) {
		KeyLeft_ = val;
		KeyRight_ = !val;
	}


	void Character::SetAIEnabled(bool val) {
		aiEnabled_ = val;
	}
	void Character::SetImageSet(StaticDLL::IMAGESETS imageSet) {
		imageSet_ = imageSet;
	}


	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//Gets





	CHARACTERFACINGDIRECTION Character::GetPlayerFacingDirection()
	{
		return faceDirection_;
	}



	float Character::GetCurrentPositionX() {
		return currentPositionX_;
	};


	float Character::GetCurrentPositionY() {
		return currentPositionY_;
	};


	CHARACTERYAXISSTATES Character::GetCharacterYAxisState()
	{
		return characterYAxisState_;
	}



	float Character::GetHealth()
	{
		return health_;
	}


	float Character::GetVelocityY() {
		return velocityY_;
	}
	float Character::GetMaxVelocityY() {
		return maxVelocityY_;
	}
	float Character::GetAccelerationY() {
		return accelerationY_;
	}



	float Character::GetJumpSpeed() {
		return jumpspeed_;
	}




	float Character::GetHeight() {
		return height_;
	}
	float Character::GetWidth() {
		return width_;
	}

	float Character::GetMoveSpeed() {
		return movespeed_;
	}
	float Character::GetMoveSpeedDelta() {
		return movespeedDelta_;
	}



	bool Character::GetKeyRight() {
		return KeyRight_;
	}
	bool Character::GetKeyLeft() {
		return KeyLeft_;
	}

	bool Character::GetHasImage() {
		return hasImage_;
	}

	Image *Character::GetObjectImage()
	{
		return image_;
	}
	StaticDLL::IMAGESETS Character::GetImageSet() {
		return imageSet_;
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//Misc


	void Character::AdjustHealth(int hp) {
		health_ = health_ + hp;
	}



	void Character::AdjustPlayerRotation()
	{
		if (CHARACTERFACINGDIRECTION::CHARACTERLEFT == faceDirection_)
		{
			currentRotation_ = currentRotation_ - 0.005;
		}
		else
		{
			currentRotation_ = currentRotation_ + 0.005;
		}
	}





	void Character::DrawObjectRotate(float mapXOffset, float mapYOffset) {
		//0.8


		

		if (hasImage_ &&  hasColor_)
		{
			al_draw_tinted_scaled_rotated_bitmap(
				image_->GetImage(),
				chosenColor_,
				image_->GetImageWidth() / 2.0,
				image_->GetImageHeight() / 2.0,
				(currentPositionX_ + width_ / 2)*Constants::TileSize() + mapXOffset,
				(currentPositionY_ + height_ / 2)*Constants::TileSize() + mapYOffset,
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
				(currentPositionX_ + width_ / 2)*Constants::TileSize() + mapXOffset,
				(currentPositionY_ + height_ / 2)*Constants::TileSize() + mapYOffset,
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
				if (GetCharacterYAxisState() == CHARACTERYAXISSTATES::CHARACTERONGROUND)
				{
					SetVelocityY(-0.5);
					SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERJUMPING);
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
		//Ai module for character
		if (aiEnabled_) {
			if (GetCurrentPositionX() - GetMoveSpeedDelta() <= 0) {
				SetKeyRight(true);
				SetKeyLeft(false);
			}
			else if (GetCurrentPositionX() + GetWidth() + GetMoveSpeedDelta() >= mapWidth_) {
				SetKeyLeft(true);
				SetKeyRight(false);
			}




			if (KeyRight_)
			{
				CollisionMovingRight();
			}
			else if (KeyLeft_)
			{
				CollisionMovingLeft();
			}


			//Characters forever in a state of falling?
			if (GetCharacterYAxisState() == CHARACTERYAXISSTATES::CHARACTERFALLING ||
				GetCharacterYAxisState() == CHARACTERYAXISSTATES::CHARACTERONGROUND)
			{
				Falling();
			}
			else if (GetCharacterYAxisState() == CHARACTERYAXISSTATES::CHARACTERJUMPING)
			{
				Jumping();
			}



		}
	}




	//this is moving in X direction
	bool Character::CheckNextXPositionGoingLeft(float nextPosX, float nextPosY)
	{
		float height = GetHeight()*Constants::TileSize();

		//check if tile is going off bounds return false;
		if ((nextPosX) / Constants::TileSize() < 0) {
			return false;
		}

		for (int i = 0; i < height; i++)
		{
			auto cellFuture = &cellMap_->at((nextPosX) / Constants::TileSize()).at((nextPosY + i) / Constants::TileSize());
			if (cellFuture->GetTileType() == TILETYPE::SOLIDTILE || cellFuture->GetTileType() == TILETYPE::COLLISIONRIGHTTILE)
			{
				return false;
			}
		}
		return true;
	}
	bool Character::CheckNextXPositionGoingRight(float nextPosX, float nextPosY)
	{
		float height = GetHeight()*Constants::TileSize();

		//check if tile is going off bounds return false;
		if ((nextPosX) / Constants::TileSize() + GetWidth() >= mapWidth_) {
			return false;
		}

		for (int i = 0; i < height; i++)
		{
			auto cellFuture = &cellMap_->at((nextPosX) / Constants::TileSize() + GetWidth()).at((nextPosY + i) / Constants::TileSize());
			if (cellFuture->GetTileType() == TILETYPE::SOLIDTILE || cellFuture->GetTileType() == TILETYPE::COLLISIONLEFTTILE)
			{

				return false;
			}
		}
		return true;
	}




	//this is moving in Y direction
	bool Character::CheckNextYPositionFalling(float nextPosX, float nextPosY)
	{
		float width = GetWidth()*Constants::TileSize();
		//check if tile is going off bounds return false;
		if ((nextPosY) / Constants::TileSize() + GetHeight() >= mapHeight_) {
			SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERONGROUND);
			SetVelocityY(0.125);
			//set no moving
			return false;
		}
		for (int i = 0; i < width; i++)
		{
			auto cellFuture = &cellMap_->at((nextPosX + i) / Constants::TileSize()).at((nextPosY) / Constants::TileSize() + GetHeight());
			if (cellFuture->GetTileType() == TILETYPE::SOLIDTILE || cellFuture->GetTileType() == TILETYPE::COLLISIONTOPTILE)
			{
				SetCurrentPositionY(cellFuture->GetCurrentPositionY() - GetHeight());
				SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERONGROUND);
				SetVelocityY(0.125);
				return false;
			}
		}
		return true;
	}

	//this is moving in Y direction
	bool Character::CheckNextYPositionJumping(float nextPosX, float nextPosY)
	{
		float width = GetWidth()*Constants::TileSize();
		//check if tile is going off bounds return false;
		if ((nextPosY) / Constants::TileSize() < 0) {
			SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERFALLING);
			SetVelocityY(0.125);
			//set no moving
			return false;
		}
		for (int i = 0; i < width; i++)
		{
			auto cellFuture = &cellMap_->at((nextPosX + i) / Constants::TileSize()).at((nextPosY) / Constants::TileSize() );
			if (cellFuture->GetTileType() == TILETYPE::SOLIDTILE)
			{
				SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERFALLING);
				SetVelocityY(0.125);
				return false;
			}
		}
		return true;
	}


	void Character::CollisionMovingLeft()
	{
		SetPlayerFacingDirection(CHARACTERFACINGDIRECTION::CHARACTERLEFT);
		for (int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosX = GetCurrentPositionX()*Constants::TileSize() - GetMoveSpeedDelta();

			if (CheckNextXPositionGoingLeft(nextPosX, GetCurrentPositionY()*Constants::TileSize()))
			{
				AdjustPlayerRotation();


				SetCurrentPositionX(nextPosX / Constants::TileSize());
				
			}
			else {
				SetKeyRight(true);
				return;
			}
		}
	}




	void Character::CollisionMovingRight()
	{
		SetPlayerFacingDirection(CHARACTERFACINGDIRECTION::CHARACTERRIGHT);
		for (int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosX = GetCurrentPositionX()*Constants::TileSize() + GetMoveSpeedDelta();

			if (CheckNextXPositionGoingRight(nextPosX, GetCurrentPositionY()*Constants::TileSize()))
			{
				AdjustPlayerRotation();
				SetCurrentPositionX(nextPosX / Constants::TileSize());
				

			}
			else {
				SetKeyLeft(true);
				return;
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
				SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERFALLING);

			}
			else {
				SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERONGROUND);

				break;
			}
		}
		//Every tick update the fall speed
		if (GetVelocityY() + GetAccelerationY() <= GetMaxVelocityY() && GetCharacterYAxisState() != CHARACTERYAXISSTATES::CHARACTERONGROUND)
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
			SetVelocityY(0.125);
			SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERFALLING);
		}
	}









	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//------------
	//------------
	//------------






}