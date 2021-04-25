#include "GameCtrlSystem.h"

void GameCtrlSystem::onFighterDeath() //////////////////////////////////////////////////////FALTA CAMBIAR ESTADO DE JUEGO//////////////////////////////////////////////////////
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
}

void GameCtrlSystem::onAsteroidsExtinction()//////////////////////////////////////////////////////FALTA CAMBIAR ESTADO DE JUEGO//////////////////////////////////////////////////////
{
	auto entities = manager_->getEnteties();

	for (int i = 0; i < entities.size(); i++) {
		if (entities[i]->hasGroup<Balas>()) {
			entities[i]->setActive(false);
		}
	}
}

void GameCtrlSystem::init()/////////////////////////////////////////////INICIALIZAR EL RESTO//////////////////////////////////////////////////////
{
	state_.setState(state_.NEWGAME);
}

void GameCtrlSystem::update()
{
	
}
