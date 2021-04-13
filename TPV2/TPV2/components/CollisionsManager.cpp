#include "CollisionManager.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../utils/Collisions.h"
#include "GameCtrl.h"
#include "AsteroidsManager.h"
#include "Health.h"

CollisionManager::CollisionManager() {

}

CollisionManager::~CollisionManager() {

}

void CollisionManager::init() {

}

void CollisionManager::update() {

	auto nave = entity_->getMngr()->getHandler<Nave>();
	auto naTR = nave->getComponent<Transform>();

	auto& ents = entity_->getMngr()->getEnteties();
	int n = ents.size();

	//comprobamos si los asteroides colisionan con la nave
	for (int i = 0; i < n; i++) {
		if (ents[i]->hasGroup<Asteroids>()) {
			auto eTR = ents[i]->getComponent<Transform>();
			if (Collisions::collides(
				naTR->getPos(), naTR->getW(), naTR->getH(),
				eTR->getPos(), eTR->getW(), eTR->getH())) {
				//METODO PARA DESTRUIR NAVE Y REINICIAR JUEGO
				/*entity_->getComponent<GameCtrl>()->collisionAsteroid(ents[i]);*/
				//entity_->setActive(false);

				//cambiamos el estado del juego
				entity_->getComponent<AsteroidsManager>()->setNumAsteroids(0);

				//destruye las balas y asteroides del juego
				for (int j = 0; j < n; j++) {
					if (ents[j]->hasGroup<Balas>() || ents[j]->hasGroup<Asteroids>()) {
						ents[j]->setActive(false);						
					}
					else if (ents[j]->hasComponent<Health>()) {
						ents[j]->getComponent<Health>()->quitaVida();
						ents[j]->getComponent<Health>()->colocaVidas();

						auto& pos = naTR->getPos();
						pos = Vector2D(((sdlutils().width() / 2)), (sdlutils().height() / 2));

						auto& vel = naTR->getVel();
						vel = Vector2D();

						naTR->setRot(0.0f);

						if (ents[j]->getComponent<Health>()->vivo()) {
							entity_->getComponent<AsteroidsManager>()->addAsteroid(10);
						}
					}
				}				

			}

			for (int j = 0; j < n; j++) {
				if (ents[j]->hasGroup<Balas>()){
						auto jTR = ents[j]->getComponent<Transform>();
					if (Collisions::collides(
						eTR->getPos(), eTR->getW(), eTR->getH(),
						jTR->getPos(), jTR->getW(), jTR->getH())) {
						entity_->getComponent<AsteroidsManager>()->onCollision(ents[i]);
						//entity_->getComponent<GameCtrl>()->collisionAsteroid(ents[i]);
						ents[j]->setActive(false);
					}
				}
			}
		}
	}

	
}

