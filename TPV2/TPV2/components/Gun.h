#pragma once

#include <cassert>

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"
#include "Image.h"
#include "DisableOnExit.h"

class Gun : public Component {

public:
	Gun() : tr_(nullptr), timeToFire(250), lastTimeFired(0.0){};
	virtual ~Gun() {};
	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}
	void update() override;

private:
	Transform* tr_;
	float timeToFire;
	float lastTimeFired;
};
