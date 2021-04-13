// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

class Rotate : public Component {
public:

	Rotate() : tr_(nullptr){

	}

	virtual ~Rotate() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);

	}
	void update() override {
		
		if (ih().keyDownEvent()) {
			if (ih().isKeyDown(SDLK_RIGHT)) {
				tr_->setRot(tr_->getRot() + 5.0f);//-- - SDLK_RIGHT
			}
			else if (ih().isKeyDown(SDLK_LEFT)) {
				tr_->setRot(tr_->getRot() - 5.0f);//-- - SLDK_LEFT
			}
		}

	}
private:
	Transform* tr_;
};
