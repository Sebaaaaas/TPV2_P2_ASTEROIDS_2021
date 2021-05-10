#include "GameCtrlSystem.h"
#include "FighterSystem.h"
#include"AsteroidsSystem.h"

void GameCtrlSystem::onFighterDeath() 
{
	auto entities = manager_->getEnteties();
	
	//recorremos todas las entidades
	for (int i = 0; i < entities.size(); i++) {

		//eliminamos todas las balas y asteroides, reseteamos vida y reseteamos transform
		if (entities[i]->hasGroup<Balas>() || entities[i]->hasGroup<Asteroids>()) {
			entities[i]->setActive(false);
		}
		else if (entities[i]->hasComponent<Health>()) {
			entities[i]->getComponent<Health>()->quitaVida();
			entities[i]->getComponent<Health>()->colocaVidas();
			
			entities[i]->getComponent<FighterCtrl>()->reset();
		}
	}

	setState(GAMEOVER);
	//state_.setState(state_.GAMEOVER);
}

void GameCtrlSystem::onAsteroidsExtinction()
{
	auto entities = manager_->getEnteties();

	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]->hasGroup<Balas>()) {
			entities[i]->setActive(false);
		}
	}

	setState(GAMEOVER);
	//state_.setState(state_.GAMEOVER);
}

void GameCtrlSystem::init()/////////////////////////////////////////////INICIALIZAR EL RESTO//////////////////////////////////////////////////////
{
	setState(RUNNING);
	manager_->addSystem<AsteroidsSystem>()->addAsteroids(10);
	
	//state_.setState(state_.NEWGAME);
}

void GameCtrlSystem::update()
{
	/*manager_->refresh();
	int i = manager_->getEnteties().size();*/
	//std::cout << i;
	/*if (state_ != RUNNING) {*/
 		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (state_) {
			case RUNNING:
				state_ = PAUSED;
				break;
				/*case NEWGAME:
					state_ = RUNNING;
					manager_->getSystem<FighterSystem>()->resetNave();
					manager_->getSystem<AsteroidsSystem>()->addAsteroids(10);
					break;*/
			case PAUSED:
				state_ = RUNNING;
				//manager_->getSystem<FighterSystem>()->resetNave();
				//manager_->getSystem<FighterSystem>()->init();
				break;
			case GAMEOVER:
				state_ = NEWGAME;
				break;
			default:
				break;
			}
		}
	/*}*/
		
}
