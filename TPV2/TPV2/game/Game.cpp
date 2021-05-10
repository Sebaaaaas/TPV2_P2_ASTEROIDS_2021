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
#include "../system/BulletSystem.h"
#include "../system/AsteroidsSystem.h"
#include "../system/CollisionSystem.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"


Game::Game() {
	mngr_.reset(new Manager());
	gameCtrlSyst_ = nullptr;
	fighterCtrlSyst_ = nullptr;
	bulletSyst_ = nullptr;
	renderSyst_ = nullptr;
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("ASTEROIDS", 800, 600,
			"resources/config/asteroids.resources.json");

	/*Manager *gameMngr_ = new Manager();*/
	
	
	

	fighterCtrlSyst_ = mngr_->addSystem<FighterSystem>();

	bulletSyst_ = mngr_->addSystem<BulletSystem>();

	collisionSyst_ = mngr_->addSystem<CollisionSystem>();

	renderSyst_ = mngr_->addSystem<RenderSystem>();

	asteroidsSyst_ = mngr_->addSystem<AsteroidsSystem>();

	gameCtrlSyst_ = mngr_->addSystem<GameCtrlSystem>();
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

		mngr_->refresh();

		

		gameCtrlSyst_->update();

		
		fighterCtrlSyst_->update();
		bulletSyst_->update();
		asteroidsSyst_->update();
		collisionSyst_->update();

		sdlutils().clearRenderer();

		renderSyst_->update();
		
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

