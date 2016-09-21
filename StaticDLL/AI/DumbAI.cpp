#include "DumbAI.h"

namespace StaticDLL {

	DumbAI::DumbAI(Character *character, Map *map)
	{
		character_ = character;
		character_->SetKeyRight(true);
		map_ = map;
	}




	void DumbAI::Update() {
		if (character_->GetCurrentPositionX() - character_->GetMoveSpeedDelta() <= 0) {
			character_->SetKeyRight(true);
			character_->SetKeyLeft(false);
		}
		else if (character_->GetCurrentPositionX() + character_->GetWidth() + character_->GetMoveSpeedDelta() >= map_->GetMapWidth()) {
			character_->SetKeyLeft(true);
			character_->SetKeyRight(false);
		}







		character_->Update();
	}




	void DumbAI::Draw() {
		character_->DrawObjectRotate();
	}




}