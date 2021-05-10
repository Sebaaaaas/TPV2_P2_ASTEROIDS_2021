//#include "FighterSystem.h"
//#include "BulletSystem.h"
#include "AsteroidsSystem.h"
#include "GameCtrlSystem.h"
#include "../ecs/Manager.h"
#include "../components/Generations.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/Follow.h"
#include "../components/ShowAtOppositeSide.h"

//#include "../components/ShowAtOppositeSide.h"
//#include "../components/Gun.h"


void AsteroidsSystem::addAsteroids(int n)
{
	sumaAsteroids(n);

	auto& r = sdlutils().rand();
	int grand = 1 + (rand() % 2);
	auto& rp = sdlutils().rand();
	float x, y;
	r.nextInt(0, 3);
	int rx = rp.nextInt(-100, 100);
	int ry = rp.nextInt(-100, 100);

	for (int i = 0; i < n; i++) {
		auto e = manager_->addEntity();
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
			tex_ = &sdlutils().images().at("asteroid");
			e->addComponent<FramedImage>(&sdlutils().images().at("asteroid"), 5, 6, 50.0f);
		}
		else {  //tipo b
			tex_ = &sdlutils().images().at("asteroid_gold");
			e->addComponent<FramedImage>(&sdlutils().images().at("asteroid_gold"), 5, 6, 50.0f);
			e->addComponent<Follow>();
		}
		e->addComponent<ShowAtOppositeSide>();
		e->setGroup<Asteroids>(true);
	}
}

void AsteroidsSystem::onCollisionWithBullet(Entity* a, Entity* b)
{
	//Desactivamos el aseroide y creamos dos hijitos
	int nGen = a->getComponent<Generations>()->getNumGen();
	if (nGen - 1 > 0) {
		for (int i = 0; i < 2; i++) {
			auto eg = a->getMngr()->addEntity();
			auto eTR = a->getComponent<Transform>();
			Vector2D ePos = eTR->getPos();
			Vector2D eVel = eTR->getVel();
			int r = sdlutils().rand().nextInt(0, 360);
			int w = eTR->getW();
			int h = eTR->getH();
			int nGen = a->getComponent<Generations>()->getNumGen();
			eg->addComponent<Generations>()->setNumGen(nGen - 1);
			Vector2D newPos = ePos + eVel.rotate(r) * 2 * w;
			Vector2D newVel = eVel.rotate(r) * 1.1f;

			eg->addComponent<Transform>(newPos, newVel, (nGen - 1) * 15.0f, (nGen - 1) * 15.0f, 0.0f);
			FramedImage imagenPad = *a->getComponent<FramedImage>();
			if (a->getComponent<Follow>()) {
				eg->addComponent<Follow>();
			}
			//FramedImage imagenPad = *a->getComponent<FramedImage>();
			eg->addComponent<FramedImage>(imagenPad);
			eg->addComponent<ShowAtOppositeSide>();
			eg->setGroup<Asteroids>(true);
			sumaAsteroids(1);
		}
	}
	a->setActive(false);
	restaAsteroids(1);

	
}

void AsteroidsSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getState() == manager_->getSystem<GameCtrlSystem>()->RUNNING) {

		int ents = manager_->getEnteties().size();
		for (int i = 0; i < ents; i++) {
			if (manager_->getEnteties()[i]->hasGroup<Asteroids>()) {
				auto* e = manager_->getEnteties()[i];
				e->update();

				/*if (e->getComponent<Transform>()->getPos().getX() < 0 || e->getComponent<Transform>()->getPos().getX() + e->getComponent<Transform>()->getW() > sdlutils().width()
					|| e->getComponent<Transform>()->getPos().getY() < 0 || e->getComponent<Transform>()->getPos().getY() + e->getComponent<Transform>()->getH() > sdlutils().height()) {

					e->setActive(false);
				}*/
			}
		}

		if (sdlutils().currRealTime() > lastTime_ + 5000) {

			lastTime_ = sdlutils().currRealTime();
			if (numOfAsteroids_ < numMaxAsteroids_ && !maxAste) {
				addAsteroids(1);
			}
			else maxAste = true; 

		}

		if (numOfAsteroids_ <= 0) {
			manager_->getSystem<GameCtrlSystem>()->setState(manager_->getSystem<GameCtrlSystem>()->GAMEOVER);
			maxAste = false;
		}
	}

	//para los frames
	if (sdlutils().currRealTime() > lastTimeFrame + timeFrame) {
		lastTimeFrame = sdlutils().currRealTime();
		c_++;
		if (c_ >= col_) {
			r_++;
			c_ = 0;
			if (r_ >= row_) {
				r_ = 0;
				c_ = 0;
			}
		}
		/*auto e = entity_->getMngr()->addEntity();*/
		cogerFrame(c_, r_);
		/*e ->addComponent<Image>(&sdlutils().images().at("asteroid"), 5, 6, r_, c_);
		e->setGroup<Asteroids>(true);*/
	}
}

void AsteroidsSystem::render()
{
	Transform* tr_Ast = nullptr;
	int ents = manager_->getEnteties().size();
	for (int i = 0; i < ents; i++) {
		if (manager_->getEnteties()[i]->hasGroup<Balas>()) {
			auto* e = manager_->getEnteties()[i];
			tr_Ast = e->getComponent<Transform>();
			SDL_Rect dest = build_sdlrect(tr_Ast->getPos(), tr_Ast->getW(), tr_Ast->getH());
			tex_->render(src_,//dibujar solo el rectangulo de la text
				dest, tr_Ast->getRot());
		}

	}
}

void AsteroidsSystem::cogerFrame(int c, int r)
{
	auto w = tex_->width() / col_;
	auto h = tex_->height() / row_;
	src_ = { w * c, h * r, w, h };
}
