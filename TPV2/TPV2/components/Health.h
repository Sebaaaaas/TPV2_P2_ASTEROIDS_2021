#pragma once
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "Image.h"


class Health : public Component {
public:

	Health() {
		health = startingHealth = 3;
	}
	virtual ~Health() {
	}

	void init() override {

		colocaVidas();
	}
	void render() override {

	}
	void colocaVidas();
	void quitaVida();
	void reseteaVidas(){health = startingHealth;}
	int devuelveVidas() {return health;}
	bool vivo() { return health > 0; }
private:
	int health;
	int startingHealth;
};
