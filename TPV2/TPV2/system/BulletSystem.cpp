#include "BulletSystem.h"

void BulletSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{

	sdlutils().soundEffects().at("fire").play();

	auto* e = manager_->addEntity();
	auto* nave = manager_->getHandler<Nave>();

	float w = width;
	float h = height;
	float r = -vel.angle(Vector2D(0.0f, -1.0f));

	auto bPos = pos + Vector2D(w / 2.0f, h / 2.0f) - Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(nave->getComponent<Transform>()->getRot()) - Vector2D(2.0f, 10.0f);
	auto bVel = Vector2D(0.0f, -1.0f).rotate(nave->getComponent<Transform>()->getRot()) * (vel.magnitude() + 5.0f);

	e->addComponent<Transform>(bPos, bVel, 5.0, 20.0, nave->getComponent<Transform>()->getRot());
	e->setGroup<Balas>(true);
	e->addComponent<Image>(&sdlutils().images().at("fire"));
	e->addComponent<DisableOnExit>();
	
}

void BulletSystem::onCollisionWithAsteroid(Entity* b, Entity* a)
{
}

void BulletSystem::update()
{
	
}
