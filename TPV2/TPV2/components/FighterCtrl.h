#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"

//#include <math.h>

class FighterCtrl : public Component {
public:
	FighterCtrl() :
		tr_(nullptr), speed_(10.0){
		thrust_ = 0.2;
		speedLimit_ = 3.0f;
	}

	virtual ~FighterCtrl() {
	}


	inline void setSpeed(float speed) {
		speed_ = speed;
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().keyDownEvent()) {
			auto& vel = tr_->getVel();
			auto rot = tr_->getRot();

			if (ih().isKeyDown(SDL_SCANCODE_LEFT)) {
				rot -= 5.0f;
			}
			else if (ih().isKeyDown(SDL_SCANCODE_RIGHT)) {
				rot += 5.0f;				
			}

			tr_->setRot(rot);


			if (ih().isKeyDown(SDL_SCANCODE_UP)) {
				newVel = vel + Vector2D(0, -1).rotate(rot) * thrust_;
				
				sdlutils().soundEffects().at("thrust").play();

				if (newVel.getX() > speedLimit_) {
					newVel.setX(speedLimit_);
				}
				else if (newVel.getX() < -speedLimit_) {
					newVel.setX(-speedLimit_);
				}

				if (newVel.getY() > speedLimit_) {
					newVel.setY(speedLimit_);
				}
				else if (newVel.getY() < -speedLimit_) {
					newVel.setY(-speedLimit_);
				}

				vel = newVel;

			}

		}
	}

	//reseteae la posicion de la nave, su velocidad y su rotacion
	void reset() { 
		tr_->setVel(Vector2D());
		tr_->setRot(0.0f);
		tr_->setPos(Vector2D());
	}

private:
	Transform* tr_;
	float speed_;
	float thrust_;
	float speedLimit_;
	Vector2D newVel;
}
;

