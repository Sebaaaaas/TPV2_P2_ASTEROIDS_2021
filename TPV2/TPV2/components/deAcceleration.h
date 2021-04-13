// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"


class deAcceleration : public Component {
public:
	deAcceleration() :
		tr_(nullptr) {
	}
	virtual ~deAcceleration() {
	}
	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {

		auto& vel = tr_->getVel();

		vel.set(tr_->getVel() * 0.995f);

	}

private:
	Transform* tr_;
};

