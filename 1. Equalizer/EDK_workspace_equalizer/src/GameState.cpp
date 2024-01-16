#include "GameState.h"

GameState* GameState::instance_ = nullptr;

GameState::GameState() {

}

GameState::~GameState() {

}

void GameState::set_Stage(unsigned int st)
{
	stages_ = st;
}

unsigned int GameState::currentStage()
{
    return stages_;
}

void GameState::destroyStage()
{
	childBackground = 0;
	circleIndex_left = 0;
	circleIndex_right = 0;
	stars_index = 0;
	ring_index = 0;
	
	for (int i = root->num_children(); i >= 0; i--) {
		root->removeChildByIndex(i);
	}

	toDestroy = false;
	toPrepare = true;

	set_Stage(currentStage() + 1);

}

GameState& GameState::instance() {
	// Lazy initialize.
	if (instance_ == nullptr) { instance_ = new GameState(); }
	return *instance_;
}