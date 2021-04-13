#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../ecs/Entity.h"

class FramedImage : public Component {
public:
	FramedImage(Texture* tex) :
		tr_(nullptr), //
		tex_(tex), //
		src_({ 0,0,tex->width(), tex->height() })//
	{
		timeFrame = 0;
	}

	FramedImage(Texture* tex, SDL_Rect src) :
		tr_(nullptr), //
		tex_(tex), src_(src) //
	{
	}

	FramedImage(Texture* tex, int rows, int cols, float time) :
		tr_(nullptr), //
		tex_(tex),
		src_({ 0,0,0,0 }),
		timeFrame(time),
		col_(cols),
		row_(rows), 
		r_(0),
		c_(0)//
	{
	}

	virtual ~FramedImage() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		//addComponent<Image>(&sdlutils().images().at("asteroid"), 5, 6, 0, 0);
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

	void cogerFrame(int c, int r) {
		
		auto w = tex_->width() / col_;
		auto h = tex_->height() / row_;
		src_ = { w * c, h * r, w, h };
	}

	void render() override {
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		tex_->render(src_,//dibujar solo el rectangulo de la text
			dest, tr_->getRot());
	}

private:
	float timeFrame, lastTimeFrame = 0;
	int col_, row_, r_, c_;
	Transform* tr_;
	Texture* tex_;
	SDL_Rect src_; //para los spritesheet
};