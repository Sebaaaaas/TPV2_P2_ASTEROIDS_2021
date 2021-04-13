#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"

#include "Transform.h"

class ShowAtOppositeSide : public Component {

public:
	ShowAtOppositeSide() : tr_(nullptr){
	};
	virtual ~ShowAtOppositeSide() {};

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override{

		auto& pos = tr_->getPos();
		auto w = tr_->getW();
		auto h = tr_->getH();

		if (pos.getX() + w < 0) {
			pos.setX(sdlutils().width());
		}
		else if (pos.getX() > sdlutils().width()) {
			pos.setX(- w);
			
		}

		if (pos.getY() + h < 0) {
			pos.setY(sdlutils().height());
			
		}
		else if (pos.getY() > sdlutils().height()) {
			pos.setY(- h);

		}
	}
	
private:
	Transform* tr_;
};
