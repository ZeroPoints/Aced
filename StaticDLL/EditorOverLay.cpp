#include "EditorOverLay.h"


namespace StaticDLL{

	EditorOverLay::EditorOverLay(Settings *settings)
	{
		settings_ = settings;


		widthMax_ = 10;
		height_ = settings_->GetDisplayHeight()*Constants::TileSize;

		overLayState_ = StaticDLL::EnumDLL::OVERLAYSTATE::OVERLAYOPENED;
		overLayAction_ = StaticDLL::EnumDLL::OVERLAYACTIONS::OVERLAYNONE;

		chosenColor_ = al_map_rgb_f(0.8,0.3,0.3);

		CreateTileArrow();
		CreateTileWindow();
		CreateMenuBar();
		

	}


	void EditorOverLay::CreateTileArrow()
	{
		//Create an arrow object
		tileWindowArrow_ = new ObjectBase();
		tileWindowArrow_->SetCurrentPosition(widthMax_, settings_->GetDisplayHeight()/2);
		tileWindowArrow_->SetWidth(1);
		tileWindowArrow_->SetHeight(1);
		tileWindowArrow_->SetColor(al_map_rgb_f(0.3,0.6,0.6));
	}


	void EditorOverLay::CreateTileWindow()
	{
		//Create an arrow object
		tilePickerWindow_ = new ObjectBase();
		tilePickerWindow_->SetCurrentPosition(0, 1);
		tilePickerWindow_->SetWidth(10);
		tilePickerWindow_->SetHeight(settings_->GetDisplayHeight());
		tilePickerWindow_->SetColor(al_map_rgb_f(0.8,0.3,0.3));
	}


	void EditorOverLay::CreateMenuBar()
	{
		//Create an arrow object
		menuBar_ = new ObjectBase();
		menuBar_->SetCurrentPosition(0, 0);
		menuBar_->SetWidth(settings_->GetDisplayWidth());
		menuBar_->SetHeight(1);
		menuBar_->SetColor(al_map_rgb_f(1,1,1));
	}




	void EditorOverLay::PreCalc()
	{


	}



	void EditorOverLay::Update()
	{
		if(overLayAction_ == EnumDLL::OVERLAYACTIONS::OVERLAYNONE)
		{
			return;
		}



		if(overLayAction_ == EnumDLL::OVERLAYACTIONS::OVERLAYOPENING)
		{
			if(overLayState_ == EnumDLL::OVERLAYSTATE::OVERLAYCLOSED)
			{
				if(tilePickerWindow_->GetWidth() < widthMax_)
				{
					tilePickerWindow_->SetWidth(tilePickerWindow_->GetWidth() + (10.0/Constants::TileSize));
					tileWindowArrow_->SetCurrentPositionX(tileWindowArrow_->GetCurrentPositionX() + (10.0/Constants::TileSize));
				}
				else
				{
					overLayState_ = EnumDLL::OVERLAYSTATE::OVERLAYOPENED;
					overLayAction_ = EnumDLL::OVERLAYACTIONS::OVERLAYNONE;
				}
			}
		}
		else if(overLayAction_ == EnumDLL::OVERLAYACTIONS::OVERLAYCLOSING)
		{
			if(overLayState_ == EnumDLL::OVERLAYSTATE::OVERLAYOPENED)
			{
				if(tilePickerWindow_->GetWidth() > 0)
				{
					tilePickerWindow_->SetWidth(tilePickerWindow_->GetWidth() - (10.0/Constants::TileSize));
					tileWindowArrow_->SetCurrentPositionX(tileWindowArrow_->GetCurrentPositionX() - (10.0/Constants::TileSize));
				}
				else
				{
					overLayState_ = EnumDLL::OVERLAYSTATE::OVERLAYCLOSED;
					overLayAction_ = EnumDLL::OVERLAYACTIONS::OVERLAYNONE;
				}
			}
		}
	}


	

	void EditorOverLay::Draw()
	{
		DrawMenuBar();
		DrawTilePicker();
		DrawBottomArrow();
	}




	void EditorOverLay::DrawBottomArrow()
	{
		tileWindowArrow_->DrawObject();
	}
	void EditorOverLay::DrawTilePicker()
	{
		tilePickerWindow_->DrawObject();
	}

	void EditorOverLay::DrawMenuBar()
	{
		menuBar_->DrawObject();
	}




	void EditorOverLay::MouseActivity(ALLEGRO_EVENT *event, int mouseX, int mouseY){
		if(event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			switch(event->mouse.button)
			{
				case 1:
					if(tileWindowArrow_->ClickIntersects(mouseX, mouseY))
					{
						if(overLayState_ == EnumDLL::OVERLAYSTATE::OVERLAYCLOSED)
						{
							overLayAction_ = EnumDLL::OVERLAYACTIONS::OVERLAYOPENING;
						}
						else if(overLayState_ == EnumDLL::OVERLAYSTATE::OVERLAYOPENED)
						{
							overLayAction_ = EnumDLL::OVERLAYACTIONS::OVERLAYCLOSING;
						}
					}

					
					break;
			}
		}
	}



	void EditorOverLay::KeyBoardActivity(ALLEGRO_EVENT *event){
		if(event->type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(event->keyboard.keycode)
			{
				case ALLEGRO_KEY_TAB:

					if(overLayState_ == EnumDLL::OVERLAYSTATE::OVERLAYCLOSED)
					{
						overLayAction_ = EnumDLL::OVERLAYACTIONS::OVERLAYOPENING;
					}
					else if(overLayState_ == EnumDLL::OVERLAYSTATE::OVERLAYOPENED)
					{
						overLayAction_ = EnumDLL::OVERLAYACTIONS::OVERLAYCLOSING;
					}

					break;
			}
		}
	}



}