#include "GameCtrl.h"
#include "../sdlutils/InputHandler.h"
#include "Health.h"
#include "FramedImage.h"
#include "ShowAtOppositeSide.h"
#include "Follow.h"
#include "Generations.h"
#include "AsteroidsManager.h"
#include "../ecs/Manager.h"

#include "deAcceleration.h"
#include "FighterCtrl.h"
#include "Gun.h"

GameCtrl::GameCtrl() : gameState_()
{
}

GameCtrl::~GameCtrl()
{
}

void GameCtrl::init()
{
	entity_->getComponent<Health>()->colocaVidas();

	auto* caza = entity_->getMngr()->addEntity();

	caza->addComponent<Transform>(Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
		Vector2D(), 30.0f, 30.0f, 0.0f);
	caza->addComponent<Image>(&sdlutils().images().at("fighter"));
	//caza->addComponent<FramedImage>(&sdlutils().images().at("asteroid"), 5, 6, 50.0f);
	//caza->addComponent<Image>(&sdlutils().images().at("asteroid"), 5, 6, 0, 0); //comprobar que funciona
	caza->addComponent<deAcceleration>();
	//caza->addComponent<KeyBoardCtrl>();
	caza->addComponent<FighterCtrl>();
	//caza->addComponent<Bounce>();
	caza->addComponent<ShowAtOppositeSide>();
	caza->addComponent<Gun>();
	entity_->getMngr()->setHandler<Nave>(caza);
	/*gameState_ = entity_->addComponent<State>();
	assert(gameState_ != nullptr);*/

	entity_->addComponent<AsteroidsManager>();
}

void GameCtrl::update()
{
	
	/*if (gameState_->getState() != gameState_->RUNNING) {
		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
			if (gameState_->getState() == gameState_->NEWGAME) {
				gameState_->setState(gameState_->RUNNING);
			}
			else if (gameState_->getState() == gameState_->PAUSED) {
				gameState_->setState(gameState_->RUNNING);
			}
			else if (gameState_->getState() == gameState_->GAMEOVER) {
				gameState_->setState(gameState_->NEWGAME);
			}
		}
	}
	else {
		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
			gameState_->setState(gameState_->PAUSED);
		}
	}*/
}