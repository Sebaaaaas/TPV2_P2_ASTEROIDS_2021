//#include "GameCtrlSystem.h"
#include "FighterSystem.h"
#include "BulletSystem.h"
#include "../ecs/Manager.h"
#include "../components/deAcceleration.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Gun.h"


void FighterSystem::onCollisionWithAsteroid(Entity* a)
{
	resetNave();
	manager_->getSystem<GameCtrlSystem>()->onFighterDeath();
}

void FighterSystem::init()
{
	auto* caza = manager_->addEntity();

	caza->addComponent<Transform>(Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
		Vector2D(), 30.0f, 30.0f, 0.0f);
	caza->addComponent<Image>(&sdlutils().images().at("fighter"));
	caza->addComponent<deAcceleration>();
	caza->addComponent<FighterCtrl>();
	caza->addComponent<ShowAtOppositeSide>();
	manager_->setHandler<Nave>(caza);

	entity_ = caza;

}

void FighterSystem::update()
{
	entity_->update();

	if (ih().keyDownEvent()) {

		if (ih().isKeyDown(SDLK_s) && sdlutils().currRealTime() > lastTimeFired + timeToFire) {		    
			manager_->getSystem<BulletSystem>()->shoot(entity_->getComponent<Transform>()->getPos(), entity_->getComponent<Transform>()->getVel(), entity_->getComponent<Transform>()->getW(), entity_->getComponent<Transform>()->getH());
			lastTimeFired = sdlutils().currRealTime();
		}
	}
	
}

void FighterSystem::resetNave()
{
	naveTrans = entity_->getComponent<Transform>();
	naveTrans->setVel(Vector2D());
	naveTrans->setPos(Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f));
}
