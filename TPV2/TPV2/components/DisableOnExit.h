#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class DisableOnExit : public Component {
public:
	DisableOnExit() :
		tr_(nullptr) {
	}
	virtual ~DisableOnExit() {
	}
	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		auto& pos = tr_->getPos();
		auto w = tr_->getW();
		auto h = tr_->getH();

		if (entity_->getComponent<Transform>()->getPos().getX() < 0 || entity_->getComponent<Transform>()->getPos().getX() + w > sdlutils().width()
			|| entity_->getComponent<Transform>()->getPos().getY() < 0 || entity_->getComponent<Transform>()->getPos().getY() + h > sdlutils().height()) {

			entity_->setActive(false);
		}

	}

private:
	Transform* tr_;
};
