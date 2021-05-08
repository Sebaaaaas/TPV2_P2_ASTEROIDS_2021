#include "GameCtrlSystem.h"
#include "FighterSystem.h"
#include "BulletSystem.h"
#include "../components/deAcceleration.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Gun.h"

void FighterSystem::onCollisionWithAsteroid(Entity* a)
{

}

void FighterSystem::init()
{

	auto* caza = manager_->addEntity();

	caza->addComponent<Transform>(Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
		Vector2D(), 30.0f, 30.0f, 0.0f);
	caza->addComponent<Image>(&sdlutils().images().at("fighter"));
	caza->addComponent<deAcceleration>();
	//caza->addComponent<KeyBoardCtrl>();
	caza->addComponent<FighterCtrl>();
	//caza->addComponent<Bounce>();
	caza->addComponent<ShowAtOppositeSide>();
	/*caza->addComponent<Gun>();*/
	manager_->setHandler<Nave>(caza);

	entity_ = caza;
}

void FighterSystem::update()
{
	entity_->update();
	if (ih().keyDownEvent()) {

		if (ih().isKeyDown(SDLK_s) && sdlutils().currRealTime() > lastTimeFired + timeToFire) {
		    BSystem->shoot(entity_->getComponent<Transform>()->getPos(), entity_->getComponent<Transform>()->getVel(), entity_->getComponent<Transform>()->getW(), entity_->getComponent<Transform>()->getH());
		}
	}
	
}
