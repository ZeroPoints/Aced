
#include "State.h"

namespace AcedSharedDLL {
	//Base class for states to inherit from
	//This is the driving structure for this projects state management system

	State::State(ALLEGRO_DISPLAY *display, std::shared_ptr<BaseSettings> &settings, std::shared_ptr<Map> &currentMap, std::shared_ptr<AssetLibrary> &assetLibrary) {
		SetAssetLibrary(assetLibrary);
		SetDisplay(display);
		SetSettings(settings);
		SetMap(currentMap);

		hasMenu_ = false;

		fprintf(stderr, "A State Created\n");
	}


	State::~State() {
		/*al_destroy_event_queue(eventQueue_);
		al_destroy_font(font30_);
		al_destroy_timer(timer);
		if (hasMenu_) {
			delete menu_;
		}*/
		//fprintf(stderr,"A State Destructed\n");
		return;
	}




	//-----------------------------------------------------------------------------------------------------

	//Gets




	STATES State::GetId()
	{
		return Id_;
	}

	STATES State::GetKeyPressState()
	{
		return keyPressState_;
	}

	bool State::GetRedraw()
	{
		return redraw_;
	}

	bool State::GetDone()
	{
		return done_;
	}



	ALLEGRO_TIMER* State::GetTimer()
	{
		return timer;
	}

	ALLEGRO_EVENT_QUEUE* State::GetEventQueue()
	{
		return eventQueue_;
	}

	std::shared_ptr<Map> &State::GetMap()
	{
		return currentMap_;
	}
	ALLEGRO_DISPLAY* State::GetDisplay()
	{
		return display_;
	}

	bool State::GetRightMouseDown() {
		return rightMouseDown_;
	}

	bool State::GetLeftMouseDown() {
		return leftmousedown_;
	}

	int State::GetMouseCursorX() {
		return mouseCursorX_;
	}

	int State::GetMouseCursorY() {
		return mouseCursorY_;
	}



	int State::GetRightMouseX() {
		return rightMouseX_;
	}

	int State::GetRightMouseY() {
		return rightMouseY_;
	}


	bool State::GetPlayerSelected() {
		return playerSelected_;
	}

	ALLEGRO_COLOR State::GetChosenColor() {
		return chosenColor_;
	}

	ALLEGRO_EVENT* State::GetEvent() {
		return event_;
	}

	bool State::GetRunning() {
		return running_;
	}

	std::shared_ptr<BaseSettings> &State::GetSettings() {
		return settings_;
	}
	std::shared_ptr<Menu> &State::GetMenu() {
		return menu_;
	}

	STATEDIRECTION State::GetStateDirection() {
		return stateDirection_;
	}


	std::shared_ptr<State> &State::GetNextState() {
		return nextState_;
	}

	int State::GetPopLevel() {
		return popLevel_;
	}






	//-----------------------------------------------------------------------------------------------------

	//Sets



	void State::SetId(STATES newId)
	{
		Id_ = newId;
	}

	void State::SetKeyPressState(STATES keyPress) {
		keyPressState_ = keyPress;
	}

	////keyPressReturnVal_ unused
	void State::SetKeyPressReturnVal(STATES val) {
		keyPressReturnVal_ = val;
	}

	void State::SetRedraw(bool flag) {
		redraw_ = flag;
	}

	void State::SetDone(bool flag) {
		done_ = flag;
	}

	void State::SetRunning(bool flag) {
		running_ = flag;
	}



	void State::SetTimer(ALLEGRO_TIMER* currentTimer) {
		timer = currentTimer;
	}

	void State::SetEventQueue(ALLEGRO_EVENT_QUEUE* eventQueue) {
		eventQueue_ = eventQueue;
	}

	void State::SetMap(std::shared_ptr<Map> &currentMap) {
		currentMap_ = currentMap;
	}

	void State::SetAssetLibrary(std::shared_ptr<AssetLibrary> &assetLibrary) {
		assetLibrary_ = assetLibrary;
	}

	std::shared_ptr<AssetLibrary> &State::GetAssetLibrary() {
		return assetLibrary_;
	}

	void State::SetDisplay(ALLEGRO_DISPLAY* currentDisplay) {
		display_ = currentDisplay;
	}

	void State::SetSettings(std::shared_ptr<BaseSettings> &settings) {
		settings_ = settings;
	}


	void State::SetRightMouseDown(bool rightMouseDown) {
		rightMouseDown_ = rightMouseDown;
	}

	void State::SetLeftMouseDown(bool leftMouseDown) {
		leftmousedown_ = leftMouseDown;
	}


	void State::SetMouseCursorPos(int x, int y) {
		mouseCursorX_ = x;
		mouseCursorY_ = y;
	}

	void State::SetRightMousePos(int x, int y) {
		rightMouseX_ = x;
		rightMouseY_ = y;
	}

	void State::SetRightMouseX(int x) {
		rightMouseX_ = x;
	}

	void State::SetRightMouseY(int y) {
		rightMouseY_ = y;
	}

	void State::SetPlayerSelected(bool selected) {
		playerSelected_ = selected;
	}

	void State::SetChosenColor(ALLEGRO_COLOR color) {
		chosenColor_ = color;
	}

	void State::SetMenu(std::shared_ptr<Menu> &menu) {
		menu_ = menu;
		hasMenu_ = true;
	}

	void State::SetEvent(ALLEGRO_EVENT *event) {
		event_ = event;
	}


	void State::SetStateDirection(STATEDIRECTION direction) {
		stateDirection_ = direction;
	}

	void State::SetNextState(std::shared_ptr<State> &state) {

		nextState_.swap(state);


		//nextState_.reset();
		//nextState_ = state;
	}

	void State::SetPopLevel(int level = 1) {
		popLevel_ = level;
	}








	//-----------------------------------------------------------------------------------------------------

	//Draws


	void State::Draw() {
		return;
	};






	//-----------------------------------------------------------------------------------------------------

	//Misc

	//key press probs goes in update
	void State::KeyPress() {
		return;
	};
	void State::MouseActivity() {
		return;
	};
	void State::Update() {
		return;
	};
	void State::Pause() {
		return;
	};
	//On resume maybe resize or graphics stuff? menus? overlay?
	void State::Resume() {
		return;
	};
	void State::CleanUp() {
		return;
	};

}
