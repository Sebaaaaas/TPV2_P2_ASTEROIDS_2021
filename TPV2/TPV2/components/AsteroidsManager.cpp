#include "AsteroidsManager.h"
#include "Generations.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "FramedImage.h"
#include "Follow.h"
#include "ShowAtOppositeSide.h"
#include "Health.h"


void AsteroidsManager::init()
{
	addAsteroid(10);
}

void AsteroidsManager::update()
{
	if (sdlutils().currRealTime() > lastTime_ + 5000) {

		lastTime_ = sdlutils().currRealTime();
		if (entity_->getComponent<Health>()->vivo())
			addAsteroid(1);
	}
}

void AsteroidsManager::onCollision(Entity* e)
{
	int nGen = e->getComponent<Generations>()->getNumGen();
	if (nGen - 1 > 0) {
		for (int i = 0; i < 2; i++) {
			auto eg = entity_->getMngr()->addEntity();
			auto eTR = e->getComponent<Transform>();
			Vector2D ePos = eTR->getPos();
			Vector2D eVel = eTR->getVel();
			int r = sdlutils().rand().nextInt(0, 360);
			int w = eTR->getW();
			int h = eTR->getH();
			int nGen = e->getComponent<Generations>()->getNumGen();
			eg->addComponent<Generations>()->setNumGen(nGen - 1);
			Vector2D newPos = ePos + eVel.rotate(r) * 2 * w;
			Vector2D newVel = eVel.rotate(r) * 1.1f;

			eg->addComponent<Transform>(newPos, newVel, (nGen - 1) * 15.0f,(nGen - 1) * 15.0f, 0.0f);
			FramedImage imagenPad = *e->getComponent<FramedImage>();
			if (e->getComponent<Follow>()) {
				eg->addComponent<Follow>();
			}
			eg->addComponent<FramedImage>(imagenPad);
			eg->addComponent<ShowAtOppositeSide>();
			eg->setGroup<Asteroids>(true);

			numAsteroides++;
		}		
	}
	e->setActive(false);
	numAsteroides--;
}

void AsteroidsManager::addAsteroid(int n)
{
	numAsteroides += n;

	auto& r = sdlutils().rand();
	int grand = 1 + (rand() % 2);
	auto& rp = sdlutils().rand();
	float x, y;
	r.nextInt(0, 3);
	int rx = rp.nextInt(-100, 100);
	int ry = rp.nextInt(-100, 100);

	for (int i = 0; i < n; i++) {
		auto e = entity_->getMngr()->addEntity(); 
		if (grand == 1) {
			x = r.nextInt(-25.0f / 2, sdlutils().width() + 25.0f / 2);
			grand = 1 + (rand() % 2);
			if (grand == 1)
				y = sdlutils().height();
			else
				y = -(25.0f);
		}
		else {
			y = r.nextInt(-25.0f / 2, sdlutils().height() + 25.0f / 2);
			grand = 1 + (rand() % 2);
			if (grand == 1)
				x = sdlutils().width();
			else
				x = -(25.0f);
		}
		grand = 1 + (rand() % 5);
		auto pos = Vector2D(x, y);
		Vector2D bVel = Vector2D(((sdlutils().width() / 2)) - x - rx, (sdlutils().height() / 2) - y - ry) * 0.001f * grand;
		e->addComponent<Generations>();
		int nGeneration = e->getComponent<Generations>()->getNumGen();
		e->addComponent<Transform>(pos, bVel, 15.0f * nGeneration, 15.0f * nGeneration, 0.0f);

		if (sdlutils().rand().nextInt(0, 10) >= 3) { //tipo a
			e->addComponent<FramedImage>(&sdlutils().images().at("asteroid"), 5, 6, 50.0f);
		}
		else {  //tipo b
			e->addComponent<FramedImage>(&sdlutils().images().at("asteroid_gold"), 5, 6, 50.0f);
			e->addComponent<Follow>();
		}
		e->addComponent<ShowAtOppositeSide>();
		e->setGroup<Asteroids>(true);
	}
}
