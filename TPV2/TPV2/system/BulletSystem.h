#pragma once

//#include "../ecs/System.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrlSystem.h"
#include "FighterSystem.h"


class BulletSystem : public System {
public:
	// - añadir una bala al juego, como en la práctica 1. La rotación de la bala
	// sería vel.angle(Vector2D(0.0f,-1.0f))
	void shoot(Vector2D pos, Vector2D vel, double width, double height);
	// - desactivar la bala “b”
	// - pasamos una referencia al asteroid aunque no se usa de momento (en el futuro
	// se puede usar para tener comportamientos distintos depende del tipo de
	// asteroid, etc).
	void onCollisionWithAsteroid(Entity* b, Entity* a);
	// - si el juego está parado no hacer nada.
	// - mover las balas y desactivar las que se salen de la ventana
	void update() override;

	void render();
private:
	
	Texture* tex_Bal = &sdlutils().images().at("fire");
	SDL_Rect src_Bal = { 0,0,tex_Bal->width(), tex_Bal->height() };
};