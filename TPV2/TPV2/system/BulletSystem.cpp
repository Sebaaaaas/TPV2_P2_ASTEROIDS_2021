#include "BulletSystem.h"

void BulletSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{

	sdlutils().soundEffects().at("fire").play();

	auto* e = manager_->addEntity();
	//se pueden mover algunas de estas variables 
	//Vector2D pos = Vector2D(tr_->getPos().getX(), tr_->getPos().getY());
	/*Vector2D pos = tr_->getPos();
	Vector2D vel = tr_->getVel();*/
	float w = 5.0;
	float h = 20.0;
	float r = vel.angle(Vector2D(0.0f, -1.0f));

	auto bPos = pos + Vector2D(w / 2.0f, h / 2.0f) - Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(r) - Vector2D(2.0f, 10.0f);
	auto bVel = Vector2D(0.0f, -1.0f).rotate(r) * (vel.magnitude() + 5.0f);

	e->addComponent<Transform>(bPos, bVel, w, h, r); //A LO MEJOR IRA BIEN SI PONES DIRECTAMENTE POS Y VEL
	e->setGroup<Balas>(true);
	e->addComponent<Image>(&sdlutils().images().at("fire"));
	/*e->addComponent<DisableOnExit>();*/
	
}

void BulletSystem::onCollisionWithAsteroid(Entity* b, Entity* a)
{
}

void BulletSystem::update()
{
	
}
