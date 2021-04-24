// This file is part of the course TPV2@UCM - Samir Genaim

#include "State.h"

#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"

void State::update() {
	if (state_ != RUNNING) {
		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
			if (state_ == NEWGAME) {
				state_ = RUNNING;
			}
			else if (state_ == PAUSED) {
				state_ = RUNNING;
			}
			else if (state_ == GAMEOVER) {
				state_ = NEWGAME;
			}
		}
	}
	else {
		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
			state_ = PAUSED;
		}
	}
}

void State::render() {
	// message when game is not running
	if (state_ != RUNNING) {

		// game over message
		if (state_ == GAMEOVER) {
			auto& t = sdlutils().msgs().at("gameover");
			t.render((sdlutils().width() - t.width()) / 2,
				(sdlutils().height() - t.height()) / 2);
		}

		// new game message
		if (state_ == NEWGAME) {
			auto& t = sdlutils().msgs().at("start");
			t.render((sdlutils().width() - t.width()) / 2,
				sdlutils().height() / 2 + t.height() * 2);
		}
		else {											//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<¿cambiar por state_ == PAUSE?
			auto& t = sdlutils().msgs().at("continue");
			t.render((sdlutils().width() - t.width()) / 2,
				sdlutils().height() / 2 + t.height() * 2);
		}
	}

	// score
	//Texture scoreMsg(
	//	sdlutils().renderer(), //
	//	std::to_string(score_[0]) + " - " + std::to_string(score_[1]),
	//	sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
	//scoreMsg.render((sdlutils().width() - scoreMsg.width()) / 2, 10);

}

void State::moveNave()
{
	auto nave = entity_->getMngr()->getHandler<Nave>();
	auto naTR = nave->getComponent<Transform>();
	auto& pos = naTR->getPos();
	pos = Vector2D(((sdlutils().width() / 2)), (sdlutils().height() / 2));

	auto& vel = naTR->getVel();
	vel = Vector2D();

	naTR->setRot(0.0f);
}

void State::init() {
}
