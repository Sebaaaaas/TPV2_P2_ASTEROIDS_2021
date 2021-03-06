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
	//e->addComponent<Image>(&sdlutils().images().at("fire"));
	
}

void BulletSystem::onCollisionWithAsteroid(Entity* b, Entity* a)
{
	b->setActive(false);
}

void BulletSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getState() == manager_->getSystem<GameCtrlSystem>()->RUNNING) {
		int ents = manager_->getEnteties().size();
		for (int i = 0; i < ents; i++) {
			if (manager_->getEnteties()[i]->hasGroup<Balas>()) {
				auto* e = manager_->getEnteties()[i];
				e->update();

				if (e->getComponent<Transform>()->getPos().getX() < 0 || e->getComponent<Transform>()->getPos().getX() + e->getComponent<Transform>()->getW() > sdlutils().width()
					|| e->getComponent<Transform>()->getPos().getY() < 0 || e->getComponent<Transform>()->getPos().getY() + e->getComponent<Transform>()->getH() > sdlutils().height()) {

					e->setActive(false);
				}
			}
		}
	}


}

void BulletSystem::render()
{
	Transform* tr_Bal = nullptr;
	int ents = manager_->getEnteties().size();
	for (int i = 0; i < ents; i++) {
		if (manager_->getEnteties()[i]->hasGroup<Balas>()) {
			auto* e = manager_->getEnteties()[i];
			tr_Bal = e->getComponent<Transform>();
			SDL_Rect dest = build_sdlrect(tr_Bal->getPos(), tr_Bal->getW(), tr_Bal->getH());
			tex_Bal->render(src_Bal,//dibujar solo el rectangulo de la text
				dest, tr_Bal->getRot());
		}
		
	}
	
}
