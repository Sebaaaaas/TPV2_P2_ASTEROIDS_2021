#pragma once

#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"

class AsteroidsSystem : public System {
public:
	// - añade n asteroides al juego como en la práctica 1.
	void addAsteroids(int n);
	// - desactivar el asteroide “a” y crear 2 asteroides como en la práctica 1.
	// - pasamos una referencia a la bala aunque no se usa de momento (en el futuro
	// se puede usar para tener comportamientos distintos depende del tipo de
	// bala, etc.)
	// - si no hay más asteroides avisar al GameCtrlSystem
	void onCollisionWithBullet(Entity* a, Entity* b);
	// - si el juego está parado no hacer nada.
	// - mover los asteroides como en la práctica 1.
	void update() override;
	void sumaAsteroids(int n) {

		numOfAsteroids_ = numOfAsteroids_ + n;
	}

	void restaAsteroids(int n) {
		numOfAsteroids_ = numOfAsteroids_ - n;
	}

	void setAsteroids(int n) { numOfAsteroids_ = n; }

	int getAsteroids() { return numOfAsteroids_; }

	void render();

	void cogerFrame(int c, int r);

	//Texture* getText() { return tex_; };

private:
	const int numMaxAsteroids_ = 12;
	int numOfAsteroids_;
	int lastTime_;
	bool maxAste = false;

	Texture* tex_ = &sdlutils().images().at("asteroid_gold");
	SDL_Rect src_ = { 0,0,0,0 };
	float timeFrame = 50.0f, lastTimeFrame = 0;
	int col_ = 6;
	int row_ = 5;
	int r_ = 0;
	int c_ = 0;
};