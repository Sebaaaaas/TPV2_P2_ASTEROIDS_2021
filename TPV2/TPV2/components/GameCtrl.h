#pragma once
#include "../ecs/Component.h"
#include "../ecs/State.h"

class GameCtrl : public Component{
public:
	GameCtrl();
	virtual ~GameCtrl();

	void init() override;
	void update() override;
	void addAsteroid(int n);
	void collisionAsteroid(Entity* e);
	
private:
	State *gameState_;
};
