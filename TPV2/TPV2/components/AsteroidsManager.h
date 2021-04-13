#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"

class AsteroidsManager : public Component{
public: 
	AsteroidsManager() :
	lastTime_(0) {}

	virtual ~AsteroidsManager() {}

	void init() override;
	void update() override;
	void onCollision(Entity * e);
	int getNumAsteroides() {
		return numAsteroides;
	}

	void setNumAsteroids(int n) {
		numAsteroides = n;
	}
	void addAsteroid(int n);

private:
	int numAsteroides;
	int lastTime_;
};

