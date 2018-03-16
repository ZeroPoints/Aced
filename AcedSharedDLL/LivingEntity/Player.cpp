#include "player.h"

namespace AcedSharedDLL {

	Player::Player(std::shared_ptr<BaseSettings> &settings, std::shared_ptr<Map> &map)
	{

		hasText_ = false;
		movespeed_ = 0;
		hasImage_ = false;
		hasColor_ = false;
		hasImageReference_ = false;
		showInvetory_ = false;


		settings_ = settings;
		map_ = map;

		KeyUp_ = false;
		KeyDown_ = false;

		KeyLeft_ = false;
		OldKeyLeft_ = false;
		KeyRight_ = false;
		OldKeyRight_ = false;
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
		//font30_ = al_load_font("arial.ttf", Constants::TileSize(), 0);


		imageState_ = CHARACTERIMAGESTATES::CHARACTERIDLERIGHT;
		animationTick_ = 0;

		SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERFALLING);


		lastImageUpdate_ = 0;




	}


	Player::~Player()
	{
		if (itemList_.size() > 0) {
			//Safety precaution for some reason
		}

	}



	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//Sets



	void Player::SetCharacterYAxisState(CHARACTERYAXISSTATES characterState)
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


	void Player::SetPlayerFacingDirection(CHARACTERFACINGDIRECTION direction)
	{
		faceDirection_ = direction;
	}


	void Player::SetImageBundle(std::shared_ptr<ImageBundle> &imageBundle)
	{
		if (imageBundle->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetImage() != nullptr)
		{
			hasImage_ = true;
			imageBundle_ = imageBundle;
			height_ = imageBundle->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetHeight();
			width_ = imageBundle->GetImageStateGroupDictionary()[0]->GetImageDictionary()[0]->GetWidth();
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





	CHARACTERFACINGDIRECTION Player::GetPlayerFacingDirection()
	{
		return faceDirection_;
	}



	double Player::GetCurrentPositionX() {
		return currentPositionX_;
	};


	double Player::GetCurrentPositionY() {
		return currentPositionY_;
	};


	CHARACTERYAXISSTATES Player::GetCharacterYAxisState()
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

	std::vector<std::shared_ptr<Item>> &Player::GetItemList() {
		return itemList_;
	}





	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//Misc


	void Player::AdjustHealth(int hp) {
		health_ = health_ + hp;
	}




	void Player::IncrementAnimationTick() {
		int sizeOfDictionary = imageBundle_->GetImageStateGroupDictionary()[(int)imageState_]->GetImageDictionary().size();


		if (animationTick_ + 1 >= sizeOfDictionary) {
			animationTick_ = 0;
		}
		else {
			animationTick_++;
		}
	}


	



	void Player::Draw(ALLEGRO_FONT* font) {
		//0.8


		




		if (hasImage_)
		{
			al_draw_scaled_bitmap(
				imageBundle_->GetImageStateGroupDictionary()[(int)imageState_]->GetImageDictionary()[animationTick_]->GetImage(),
				0, 0,
				imageBundle_->GetImageStateGroupDictionary()[(int)imageState_]->GetImageDictionary()[animationTick_]->GetWidth()*Constants::TileSize(),
				imageBundle_->GetImageStateGroupDictionary()[(int)imageState_]->GetImageDictionary()[animationTick_]->GetHeight()*Constants::TileSize(),
				currentPositionX_*Constants::TileSize() + map_->GetMapXOffset(),
				currentPositionY_*Constants::TileSize() + map_->GetMapYOffset(),
				imageBundle_->GetImageStateGroupDictionary()[(int)imageState_]->GetImageDictionary()[animationTick_]->GetWidth()*Constants::TileSize(),
				imageBundle_->GetImageStateGroupDictionary()[(int)imageState_]->GetImageDictionary()[animationTick_]->GetHeight()*Constants::TileSize(),
				0
			);

		}




		if (showInvetory_) {

			for (int i = 0; i < itemList_.size(); i++) {

				itemList_[i]->DrawObject(0, 0);

			}
		}



		std::stringstream text;
		text << "Player:" << animationTick_;

		al_draw_text(font, al_map_rgb(0, 0, 0),
		0,
		20 * 9, ALLEGRO_ALIGN_LEFT, text.str().c_str());



	};






























	int Player::Keypress(ALLEGRO_EVENT *ev)
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
			case ALLEGRO_KEY_TAB:
				showInvetory_ = !showInvetory_;
				break;
			case ALLEGRO_KEY_UP://choose later....
				KeyUp_ = true;
				break;
			case ALLEGRO_KEY_DOWN://choose later....
				KeyDown_ = true;
				break;
			case ALLEGRO_KEY_RIGHT://choose later....
				KeyRight_ = true;
				break;
			case ALLEGRO_KEY_LEFT://choose later....
				KeyLeft_ = true;
				break;
			case ALLEGRO_KEY_E://choose later....
				KeyE_ = true;
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

			case ALLEGRO_KEY_UP://choose later....
				KeyUp_ = false;
				break;
			case ALLEGRO_KEY_DOWN://choose later....
				KeyDown_ = false;
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






	//Player E interaction handler for objects
	void Player::KeyPressUpdateE() {
		//Perform Special Action
		if (faceDirection_ == CHARACTERFACINGDIRECTION::CHARACTERRIGHT) {
			float nextPosX = GetCurrentPositionX()*Constants::TileSize() + 1;
			double height = GetHeight()*Constants::TileSize();
			//check if tile is going off bounds return false;
			if ((nextPosX) / Constants::TileSize() + GetWidth() >= map_->GetMapWidth()) {
				return;
			}
			for (int i = 0; i < height; i++)
			{
				std::shared_ptr<Cell> cellFuture = map_->GetCellMap()[(nextPosX) / Constants::TileSize() + GetWidth()][(GetCurrentPositionY()*Constants::TileSize() + i) / Constants::TileSize()];
				//detect if its an object and if it is use item
				if (CheckNextPositionForObject(cellFuture)) {
					//Object exists if its a door do something
					switch (cellFuture->GetInteractiveObject()->GetObjectType()) {
						case OBJECTTYPES::DOOR:
							return;
							break;
					}
					return;
				}
			}
		}
		else if (faceDirection_ == CHARACTERFACINGDIRECTION::CHARACTERLEFT) {
			float nextPosX = GetCurrentPositionX()*Constants::TileSize() - 1;
			double height = GetHeight()*Constants::TileSize();
			//check if tile is going off bounds return false;
			if ((nextPosX) / Constants::TileSize() < 0) {
				return;
			}
			for (int i = 0; i < height; i++)
			{
				std::shared_ptr<Cell> cellFuture = map_->GetCellMap()[(nextPosX) / Constants::TileSize()][(GetCurrentPositionY()*Constants::TileSize() + i) / Constants::TileSize()];
				//detect if its an object and if it is use item
				if (CheckNextPositionForObject(cellFuture)) {
					//Object exists if its a door do something
					switch (cellFuture->GetInteractiveObject()->GetObjectType()) {
					case OBJECTTYPES::DOOR:
						return;
						break;
					}
					return;
				}
			}
		}
	}







	void Player::Update(ALLEGRO_EVENT *ev)
	{

		if (ev->timer.timestamp - lastImageUpdate_ >= 5.0 / GetMoveSpeed()) {
			IncrementAnimationTick();
			lastImageUpdate_ = ev->timer.timestamp;
		}








		if (KeyE_) {
			KeyE_ = false;
			KeyPressUpdateE();
		}


		if (KeyDown_) {
			SetMoveSpeed(GetMoveSpeed() - 1);
		}

		if (KeyUp_) {
			SetMoveSpeed(GetMoveSpeed() + 1);
		}





		if (KeyRight_)
		{

			CollisionMovingRight();

			SetPlayerFacingDirection(CHARACTERFACINGDIRECTION::CHARACTERRIGHT);
			imageState_ = CHARACTERIMAGESTATES::CHARACTERMOVINGRIGHT;
			if (!OldKeyRight_) {
				animationTick_ = 0;
			}


			OldKeyRight_ = true;
			OldKeyLeft_ = false;
		}
		else if (KeyLeft_)
		{

			CollisionMovingLeft();

			SetPlayerFacingDirection(CHARACTERFACINGDIRECTION::CHARACTERLEFT);
			imageState_ = CHARACTERIMAGESTATES::CHARACTERMOVINGLEFT;
			if (!OldKeyLeft_) {
				animationTick_ = 0;
			}

			OldKeyRight_ = false;
			OldKeyLeft_ = true;
		}
		else {

			if (faceDirection_ == CHARACTERFACINGDIRECTION::CHARACTERLEFT) {
				imageState_ = CHARACTERIMAGESTATES::CHARACTERIDLELEFT;
			}
			else if (faceDirection_ == CHARACTERFACINGDIRECTION::CHARACTERRIGHT) {
				imageState_ = CHARACTERIMAGESTATES::CHARACTERIDLERIGHT;
			}

			if (OldKeyRight_ || OldKeyLeft_) {
				animationTick_ = 0;
			}


			OldKeyRight_ = false;
			OldKeyLeft_ = false;
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



		if (map_->ItemCollisionCheckAtXYExists(currentPositionX_, currentPositionY_, width_, height_)) {
			//shouldnt be null ever
			auto item = map_->ItemCollisionCheckAtXY(currentPositionX_, currentPositionY_, width_, height_);
			AddItemToInventory(item);
		}
		

	}



	//Checks the next cell if that cell has object then check if player has an item that can interact with it???
	bool Player::CheckNextPositionForObject(std::shared_ptr<Cell> &cellFuture) {

		if (cellFuture->GetHasInteractiveObject()) {

			if (cellFuture->GetInteractiveObject()->CollisionInteraction(itemList_)) {
				//player interaction code
				//return true to stop user walking into that objects space
				return true;
			}
		}
		return false;
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
			std::shared_ptr<Cell> cellFuture = map_->GetCellMap()[(nextPosX) / Constants::TileSize()][(nextPosY + i) / Constants::TileSize()];
			//detect if its an object and if it is use item
			if (CheckNextPositionForObject(cellFuture)) {
				return false;
			}
			if (cellFuture->GetTileType() == TILETYPE::SOLIDTILE || cellFuture->GetTileType() == TILETYPE::COLLISIONRIGHTTILE)
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
		if ((nextPosX) / Constants::TileSize() + GetWidth() >= map_->GetMapWidth()) {
			return false;
		}

		for (int i = 0; i < height; i++)
		{
			std::shared_ptr<Cell> cellFuture = map_->GetCellMap()[(nextPosX) / Constants::TileSize() + GetWidth()][(nextPosY + i) / Constants::TileSize()];
			//detect if its an object and if it is use item
			if (CheckNextPositionForObject(cellFuture)) {
				return false;
			}
			if (cellFuture->GetTileType() == TILETYPE::SOLIDTILE || cellFuture->GetTileType() == TILETYPE::COLLISIONLEFTTILE)
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
			SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERONGROUND);
			SetVelocityY(0.125);
			//set no moving
			return false;
		}
		for (int i = 0; i < width; i++)
		{
			std::shared_ptr<Cell> cellFuture = map_->GetCellMap()[(nextPosX + i) / Constants::TileSize()][(nextPosY) / Constants::TileSize() + GetHeight()];
			//detect if its an object and if it is use item
			if (CheckNextPositionForObject(cellFuture)) {
				SetCurrentPositionY(cellFuture->GetCurrentPositionY() - GetHeight());
				SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERONGROUND);
				SetVelocityY(0.125);
				return false;
			}
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
	bool Player::CheckNextYPositionJumping(float nextPosX, float nextPosY)
	{
		double width = GetWidth()*Constants::TileSize();
		//check if tile is going off bounds return false;
		if ((nextPosY) / Constants::TileSize() < 0) {
			SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERFALLING);
			SetVelocityY(0.125);
			//set no moving
			return false;
		}
		for (int i = 0; i < width; i++)
		{
			std::shared_ptr<Cell> cellFuture = map_->GetCellMap()[(nextPosX + i) / Constants::TileSize()][(nextPosY) / Constants::TileSize()];
			//detect if its an object and if it is use item
			if (CheckNextPositionForObject(cellFuture)) {
				SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERFALLING);
				SetVelocityY(0.125);
				return false;
			}
			if (cellFuture->GetTileType() == TILETYPE::SOLIDTILE)
			{
				SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERFALLING);
				SetVelocityY(0.125);
				return false;
			}
		}
		return true;
	}














	void Player::CollisionMovingLeft()
	{

		for (int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosX = GetCurrentPositionX()*Constants::TileSize() - GetMoveSpeedDelta();
			if (CheckNextXPositionGoingLeft(nextPosX, GetCurrentPositionY()*Constants::TileSize()))
			{
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
			else {
			}
		}
	}




	void Player::CollisionMovingRight()
	{
		for (int i = 0; i < GetMoveSpeed(); i++)
		{
			float nextPosX = GetCurrentPositionX()*Constants::TileSize() + GetMoveSpeedDelta();
			if (CheckNextXPositionGoingRight(nextPosX, GetCurrentPositionY()*Constants::TileSize()))
			{
				SetCurrentPositionX(nextPosX / Constants::TileSize());
				if (map_->GetMapWidth() * Constants::TileSize() + map_->GetMapXOffset() - settings_->GetScreenWidth() <= 0 || nextPosX <= settings_->GetScreenWidth() / 2)
				{

				}
				else
				{
					map_->SetMapMoveXDelta(-GetMoveSpeedDelta());
					map_->SetMapXOffset(map_->GetMapXOffset() - GetMoveSpeedDelta());
				}
			}
			else
			{

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
				SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERFALLING);
				if (map_->GetMapHeight() * Constants::TileSize() + map_->GetMapYOffset() - settings_->GetScreenHeight() <= 0 || nextPosY <= settings_->GetScreenHeight() / 2)
				{
				}
				else
				{
					map_->SetMapMoveYDelta(-GetVelocityY());
					map_->SetMapYOffset(map_->GetMapYOffset() - GetVelocityY());
				}
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
					map_->SetMapMoveYDelta(-GetVelocityY());
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
			SetCharacterYAxisState(CHARACTERYAXISSTATES::CHARACTERFALLING);
		}
	}




	void Player::AddItemToInventory(std::shared_ptr<Item> &thing) {
		double x, y;
		if (itemList_.size() == 0) {
			//offset init item placement by half a tilesize
			x = 0.5;
			y = 0.5;
		}
		else {
			auto lastItemPos = itemList_[itemList_.size() - 1];
			//.25 for padding between items
			x = lastItemPos->GetPosX() + 1.25;
			y = lastItemPos->GetPosY();
		}

		if (x > 10) {
			y = y + 1.25;
			x = 0.5;
		}


		thing->SetPosX(x);
		thing->SetPosY(y);
		itemList_.push_back(thing);
	}


	void Player::RemoveItemFromInventory(int id) {

		//delete itemList_[id];
		itemList_.erase(itemList_.begin() + 0);

	}



}












