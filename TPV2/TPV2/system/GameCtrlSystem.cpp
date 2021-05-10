#include "GameCtrlSystem.h"
#include "FighterSystem.h"
#include"AsteroidsSystem.h"

void GameCtrlSystem::onFighterDeath() 
{
	auto entities = manager_->getEnteties();
	bool sigueVivo;
	
	//recorremos todas las entidades
	for (int i = 0; i < entities.size(); i++) {

		//eliminamos todas las balas y asteroides, reseteamos vida y reseteamos transform
		if (entities[i]->hasGroup<Balas>() || entities[i]->hasGroup<Asteroids>()) {
			entities[i]->setActive(false);
		}
		else if (entities[i]->hasComponent<Health>()) {
			entities[i]->getComponent<Health>()->quitaVida();
			
			if (entities[i]->getComponent<Health>()->devuelveVidas() > 0) { sigueVivo = true; }
			else {
				sigueVivo = false;
				entities[i]->getComponent<Health>()->reseteaVidas();

			}
			entities[i]->getComponent<Health>()->colocaVidas();

		}
	}

	if(sigueVivo){ setState(PAUSED); }
	else{ setState(GAMEOVER); }

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
}

void GameCtrlSystem::init()
{
	setState(RUNNING);
	manager_->getSystem<AsteroidsSystem>()->addAsteroids(10);
}

void GameCtrlSystem::update()
{
 		if (ih().isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (state_) {
			case RUNNING:
				state_ = PAUSED;
				break;
			case NEWGAME:
				state_ = RUNNING;
				break;
			case PAUSED:
				state_ = RUNNING;
				break;
			case GAMEOVER:
				state_ = NEWGAME;
				break;
			default:
				break;
			}
		}
}
