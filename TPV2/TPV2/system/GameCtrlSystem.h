#pragma once

#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

#include "../components/Health.h"///////////////////////////////////////////////////////NO DEBERIA ESTAR AQUI-->cpp///////////////////////////////////////////////////////
#include "../components/FighterCtrl.h"
#include "../ecs/State.h"


class GameCtrlSystem : public System
{
public:
	enum GameSate : Uint8 {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER // game over
	};
	// - a este m�todo se le va a llamar cuando muere el caza.
	// - desactivar los asteroides y las balas, actualizar el estado del juego, etc.
	void onFighterDeath();
	// - a este m�todo se le va a llamar cuando no haya m�s asteroides.
	// - desactivar todas las balas, etc.
	void onAsteroidsExtinction();
	// - devuelve el estado del juego.
	GameSate getState() { return state_; }
	void setState(GameSate newState) { state_ = newState; }
	// - inicializar el estado del juego si es necesario, etc.
	void init() override;
	// - si el juego est� parado y el jugador pulsa SDLK_SPACE cambia el estado como
	// en la pr�ctica 1, etc.
	void update() override;

private:
	GameSate state_;
	
};

