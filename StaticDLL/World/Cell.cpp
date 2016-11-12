#include "Cell.h"


namespace StaticDLL {

	Cell::Cell()
	{
		tileCollisionTypeColor_ = al_map_rgb_f(0, 0, 0);
		hasTile_ = false;
		hasInteractiveObject_ = false;
		hasInteractiveObjectReference_ = false;
	}

	Cell::~Cell()
	{
		if (hasTile_) {
			delete tile_;
		}
		if (hasInteractiveObject_) {
			delete interactiveObject_;
		}
		//fprintf(stderr, "A Cell Destructed\n");
	}





	//-----------------------------------------------------------------------------------------------------

	//Sets




	void Cell::SetTile(Tile* tile)
	{
		hasTile_ = true;
		tile_ = tile;
	}

	void Cell::SetInteractiveObject(InteractiveObject* interactiveObject, bool isReference)
	{
		if (isReference) {
			hasInteractiveObjectReference_ = true;
		}
		else {
			hasInteractiveObject_ = true;
		}
		interactiveObject_ = interactiveObject;
	}


	void Cell::SetTileType(TILETYPE tileType)
	{
		tileType_ = tileType;
	}
	void Cell::SetTileTypeProperties(EditorItemBase *selectedTile)
	{
		tileType_ = selectedTile->GetTileType();
	}
	void Cell::SetCurrentPosition(double x, double y) {
		x_ = x;
		y_ = y;
	}
	void Cell::SetCurrentPositionX(double x) {
		x_ = x;
	}
	void Cell::SetCurrentPositionY(double y) {
		y_ = y;
	}



	//-----------------------------------------------------------------------------------------------------

	//Gets





	Tile* Cell::GetTile()
	{
		return tile_;
	}
	bool Cell::GetHasTile()
	{
		return hasTile_;
	}

	



	InteractiveObject* Cell::GetInteractiveObject()
	{
		return interactiveObject_;
	}
	bool Cell::GetHasInteractiveObject()
	{
		return hasInteractiveObject_ || hasInteractiveObjectReference_;
	}
	bool Cell::GetHasInteractiveObjectReference()
	{
		return hasInteractiveObjectReference_;
	}



	TILETYPE Cell::GetTileType()
	{
		return tileType_;
	}
	double Cell::GetCurrentPositionY() {
		return y_;
	}
	double Cell::GetCurrentPositionX() {
		return x_;
	}






	//-----------------------------------------------------------------------------------------------------

	//Draws


	//Draws the cell
	//This means it draws the Tile if it exists
	//Or draws the Interactive object if it exists
	//If its a Reference to a InteractiveObject Reference then dont draw anything
	//No matter what draw a collision type

	void Cell::Draw(int xoffset, int yoffset, bool invertCollision) {

		//DOBULE check that this ref code even needed???
		if (!hasInteractiveObjectReference_ && hasTile_) {
			tile_->DrawObject(x_,y_,xoffset, yoffset);
		}
		if (hasInteractiveObject_) {
			interactiveObject_->DrawObject(x_, y_, xoffset, yoffset);
		}
		DrawObjectType(xoffset, yoffset, invertCollision);
	}









	//Draws the tiles collision properties
	//Inverts them if necassery
	void Cell::DrawObjectType(int xOffset, int yOffset, bool invert) {
		ALLEGRO_COLOR newColor;
		newColor.a = 1;
		newColor.r = invert ? !tileCollisionTypeColor_.r : tileCollisionTypeColor_.r;
		newColor.g = invert ? !tileCollisionTypeColor_.g : tileCollisionTypeColor_.g;
		newColor.b = invert ? !tileCollisionTypeColor_.b : tileCollisionTypeColor_.b;

		if (tileType_ == TILETYPE::SOLIDTILE)
		{
			al_draw_rectangle(
				GetCurrentPositionX()*Constants::TileSize() + xOffset + (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				GetCurrentPositionX()*Constants::TileSize() + Constants::TileSize() + xOffset - (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + Constants::TileSize() + yOffset - (Constants::TileSize() / 5),
				newColor, 2
			);
		}
		else if (tileType_ == TILETYPE::COLLISIONTOPTILE)
		{
			al_draw_line(
				GetCurrentPositionX()*Constants::TileSize() + xOffset + (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				GetCurrentPositionX()*Constants::TileSize() + Constants::TileSize() + xOffset - (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				newColor, 2
			);
		}
		else if (tileType_ == TILETYPE::COLLISIONLEFTTILE)
		{
			al_draw_line(
				GetCurrentPositionX()*Constants::TileSize() + xOffset + (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				GetCurrentPositionX()*Constants::TileSize() + xOffset + (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + Constants::TileSize() + yOffset - (Constants::TileSize() / 5),
				newColor, 2
			);
		}
		else if (tileType_ == TILETYPE::COLLISIONRIGHTTILE)
		{
			al_draw_line(
				GetCurrentPositionX()*Constants::TileSize() + Constants::TileSize() + xOffset - (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
				GetCurrentPositionX()*Constants::TileSize() + Constants::TileSize() + xOffset - (Constants::TileSize() / 5),
				GetCurrentPositionY()*Constants::TileSize() + Constants::TileSize() + yOffset - (Constants::TileSize() / 5),
				newColor, 2
			);
		}
		//else if (tileType_ == TILETYPE::invert)
		//{
		//	//reverse inversion tile 
		//	newColor.r = invert ? tileCollisionTypeColor_.r : !tileCollisionTypeColor_.r;
		//	newColor.g = invert ? tileCollisionTypeColor_.g : !tileCollisionTypeColor_.g;
		//	newColor.b = invert ? tileCollisionTypeColor_.b : !tileCollisionTypeColor_.b;
		//	al_draw_rectangle(
		//		GetCurrentPositionX()*Constants::TileSize() + xOffset + (Constants::TileSize() / 5),
		//		GetCurrentPositionY()*Constants::TileSize() + yOffset + (Constants::TileSize() / 5),
		//		GetCurrentPositionX()*Constants::TileSize() + Constants::TileSize() + xOffset - (Constants::TileSize() / 5),
		//		GetCurrentPositionY()*Constants::TileSize() + Constants::TileSize() + yOffset - (Constants::TileSize() / 5),
		//		newColor, 2
		//	);
		//}
	}





	//-----------------------------------------------------------------------------------------------------

	//MISC




	//Detects If click intersects with the object selected
	bool Cell::ClickIntersects(int mouseX, int mouseY)
	{
		//Offset the mouse position to the actual coord as the mouseX and mouseY i read in a moded to be offset? by half the tile size for some reason
		mouseX = mouseX + (Constants::TileSize() / 2);
		mouseY = mouseY + (Constants::TileSize() / 2);

		if (mouseX >= (x_*Constants::TileSize()) &&
			mouseX < ((x_)*Constants::TileSize() + Constants::TileSize()) &&
			mouseY >= (y_*Constants::TileSize()) &&
			mouseY < ((y_)*Constants::TileSize() + Constants::TileSize()))
		{
			return true;
		}
		return false;

	};




	void Cell::DeleteTile() {
		hasTile_ = false;
		delete tile_;
	}
	void Cell::DeleteInteractiveObject() {
		if (hasInteractiveObjectReference_) {
			hasInteractiveObjectReference_ = false;
		}
		else if(hasInteractiveObject_){
			hasInteractiveObject_ = false;
			delete interactiveObject_;
		}
	}




}