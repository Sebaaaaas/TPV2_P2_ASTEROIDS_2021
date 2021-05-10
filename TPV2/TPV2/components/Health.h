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
		/*tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);*/
		colocaVidas();
	}
	void render() override {
		/*SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		tex_->render(dest, tr_->getRot());
		*/
	}
	void colocaVidas();
	void quitaVida();
	void reseteaVidas(){health = startingHealth;}
	int devuelveVidas() {return health;}
	bool vivo() { return health > 0; }
private:
	int health;
	int startingHealth;
	//Transform* tr_;
	//Texture* tex_;
};
