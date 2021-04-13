#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

class Generations : public Component {
public:
	Generations(){
		int n = 1 + (rand() % 3);
		numGen = n;
	}

	virtual ~Generations() {
	}

	void init() override {
	}

	int getNumGen() {
		return numGen;
	}

	void setNumGen(int n) {
		numGen = n;
	}

private:
	int numGen;
};