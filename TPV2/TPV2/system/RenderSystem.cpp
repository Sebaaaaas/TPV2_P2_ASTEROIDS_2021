#include "RenderSystem.h"
#include "GameCtrlSystem.h"
#include "BulletSystem.h"
#include "AsteroidsSystem.h"

void RenderSystem::update()
{
	auto n = manager_->getEnteties().size(); 
	for (auto i = 0u; i < n; i++)
		manager_->getEnteties()[i]->render();
	
	auto state_ = manager_->getSystem<GameCtrlSystem>()->getState();

	if (state_ != manager_->getSystem<GameCtrlSystem>()->RUNNING) {

		// game over message
		if (state_ == manager_->getSystem<GameCtrlSystem>()->GAMEOVER) {
			auto& t = sdlutils().msgs().at("gameover");
			t.render((sdlutils().width() - t.width()) / 2,
				(sdlutils().height() - t.height()) / 2);
		}

		// new game message
		if (state_ == manager_->getSystem<GameCtrlSystem>()->NEWGAME) {
			auto& t = sdlutils().msgs().at("start");
			t.render((sdlutils().width() - t.width()) / 2,
				sdlutils().height() / 2 + t.height() * 2);
		}
		else if(state_ == manager_->getSystem<GameCtrlSystem>()->PAUSED){										
			auto& t = sdlutils().msgs().at("continue");
			t.render((sdlutils().width() - t.width()) / 2,
				sdlutils().height() / 2 + t.height() * 2);
		}
	}

	manager_->getSystem<BulletSystem>()->render();
	//manager_->getSystem<AsteroidsSystem>()->render();

}

//void RenderSystem::dibuja(Transform* tr_, Texture* tex_, SDL_Rect src_)
//{
//	SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
//	tex_->render(src_,//dibujar solo el rectangulo de la text
//		dest, tr_->getRot());
//}


