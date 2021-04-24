#pragma once

#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

#include "Health.h"///////////////////////////////////////////////////////NO DEBERIA ESTAR AQUI?///////////////////////////////////////////////////////
#include "FighterCtrl.h"
#include "State.h"


class GameCtrlSystem : public System
{
public:
	// - a este m�todo se le va a llamar cuando muere el caza.
	// - desactivar los asteroides y las balas, actualizar el estado del juego, etc.
	void onFighterDeath();
	// - a este m�todo se le va a llamar cuando no haya m�s asteroides.
	// - desactivar todas las balas, etc.
	void onAsteroidsExtinction();
	// - devuelve el estado del juego.
	State::GameState getGameState() { state_.getState(); }
	// - inicializar el estado del juego si es necesario, etc.
	void init() override;
	// - si el juego est� parado y el jugador pulsa SDLK_SPACE cambia el estado como
	// en la pr�ctica 1, etc.
	void update() override;

private:
	State state_;
	
};

