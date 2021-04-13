#pragma once
#include "../ecs/Component.h"

class State : public Component {
public:
	enum GameState {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER // game over
	};

	State() : state_() {
	}

	virtual ~State() {
	}

	void init() override;
	void update() override;
	void render() override;
	GameState getState() const { return state_; }
	void setState(GameState newState) { state_ = newState; }
	void moveNave();

private:
	GameState state_;
};