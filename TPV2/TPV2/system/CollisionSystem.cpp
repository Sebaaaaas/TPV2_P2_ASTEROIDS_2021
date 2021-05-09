#include "CollisionSystem.h"
#include "../utils/Collisions.h"
#include "FighterSystem.h"
#include "AsteroidsSystem.h"
#include "BulletSystem.h"

void CollisionSystem::update()
{
	auto& ents = manager_->getEnteties();
	auto* nave = manager_->getHandler<Nave>();
	auto naTR = nave->getComponent<Transform>();

	for (int i = 0; i < ents.size(); i++) {

		
		if (ents[i]->hasGroup<Asteroids>()) {

			//colisiones de la nave con los asteroides
			auto eTR = ents[i]->getComponent<Transform>();
			if (Collisions::collides(
				naTR->getPos(), naTR->getW(), naTR->getH(),
				eTR->getPos(), eTR->getW(), eTR->getH())) {

				manager_->getSystem<FighterSystem>()->onCollisionWithAsteroid(ents[i]);
			}

			//colisiones de las balas con los asteroides
			for (int j = 0; j < ents.size(); j++) {
				if (ents[j]->hasGroup<Balas>()) {
					auto jTR = ents[j]->getComponent<Transform>();
					if (Collisions::collides(
						eTR->getPos(), eTR->getW(), eTR->getH(),
						jTR->getPos(), jTR->getW(), jTR->getH())) {

						manager_->getSystem<AsteroidsSystem>()->onCollisionWithBullet(ents[i], ents[j]);
						manager_->getSystem<BulletSystem>()->onCollisionWithAsteroid(ents[j], ents[i]);
						//ents[i]->getComponent<AsteroidsSystem>()->onCollisionWithBullet(ents[i], ents[j]);
						
						//ents[j]->getComponent<BulletSystem>()->onCollisionWithAsteroid(ents[j], ents[i]);
					}
				}
			}
		}
		

	}
}
