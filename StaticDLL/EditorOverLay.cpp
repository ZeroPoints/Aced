#include "EditorOverLay.h"


namespace StaticDLL{

	EditorOverLay::EditorOverLay(Settings *settings)
	{
		settings_ = settings;




		//Create an arrow object
		arrow_ = new ObjectBase();
		arrow_->SetCurrentPosition((settings_->GetDisplayWidth()/2) - (Constants::TileSize/Constants::TileSize)+.5, settings_->GetDisplayHeight()-1);
		arrow_->SetWidth(1);
		arrow_->SetHeight(1);
		arrow_->SetColor(al_map_rgb_f(0.5,0.5,0.5));

	}





	void EditorOverLay::PreCalc()
	{


	}



	void EditorOverLay::Update()
	{


	}


	void EditorOverLay::Draw()
	{
		arrow_->DrawObject();
	}


	void EditorOverLay::DrawBottomArrow()
	{


	}




	//TODO: Make object base have interactive click function
	//Or make an overlay Object that inherits and has clickable
	void EditorOverLay::OnBottomArrowClick()
	{


	}
}