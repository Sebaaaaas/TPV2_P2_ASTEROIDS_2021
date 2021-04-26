// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Bounce.h"
#include "../components/KeyBoardCtrl.h"
#include "../components/Rectangle.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Rotate.h"
//#include "../components/deAcceleration.h"
#include "../components/Health.h"
//#include "../components/FighterCtrl.h"
#include "../components/GameCtrl.h"
//#include "../components/Gun.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/DisableOnExit.h"
#include "../components/FramedImage.h"
#include "../ecs/State.h"
#include "../utils/Collisions.h"
#include "../components/CollisionManager.h"
#include "../components/AsteroidsManager.h"

#include "../system/GameCtrlSystem.h"
#include "../system/FighterSystem.h"
#include "../system/RenderSystem.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"

Game::Game() {
	mngr_.reset(new Manager());
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("ASTEROIDS", 800, 600,
			"resources/config/asteroids.resources.json");

	Manager *gameMngr_ = new Manager();
	

	gameCtrlSyst_ = new GameCtrlSystem();
	gameCtrlSyst_->setMngr(gameMngr_);
	gameCtrlSyst_->init();


	fighterCtrlSyst_ = new FighterSystem();
	fighterCtrlSyst_->setMngr(gameMngr_);
	fighterCtrlSyst_->init();

	renderSyst_ = new RenderSystem();
	renderSyst_->setMngr(gameMngr_);
	renderSyst_->init();

	/*gameCtrlSys_ = gameMngr_->a
	gameCtrlSys_ = new GameCtrlSystem();
	gameCtrlSys_->setMngr(gameMngr_);*/

	/*auto* gm = mngr_->addEntity();
	gm->addComponent<Health>();
	gm->addComponent<AsteroidsManager>();
	gm->addComponent<GameCtrl>();
	gm->addComponent<CollisionManager>();
	gm->addComponent<State>();*/


}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		gameCtrlSyst_->update();
		//mngr_->update();
		//mngr_->refresh();
		//std::cout << mngr_->getEnteties().size();//<<<<<<<<<<<<<<MIRAR POR CONSOLA LA CANTIDAD DE ENTIDADES EN ESCENA
		sdlutils().clearRenderer();
		/*mngr_->render();*/
		renderSyst_->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

