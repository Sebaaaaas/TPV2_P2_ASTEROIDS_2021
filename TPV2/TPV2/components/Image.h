// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"

#include "Transform.h"

class Image: public Component {
public:
	Image(Texture *tex) :
			tr_(nullptr), //
			tex_(tex), //
		src_({0,0,tex->width(), tex->height()})//
	{
	}

	Image(Texture* tex, SDL_Rect src) :
		tr_(nullptr), //
		tex_(tex), src_(src) //
	{
	}

	Image(Texture* tex, int rows, int cols, int r, int c) :
		tr_(nullptr), //
		tex_(tex) //
	{
		//calcular el src_ introduciendo columna y fila del frame
		auto w = tex_->width() / cols;
		auto h = tex_->height() / rows;
		src_ = { w * c, h * r, w, h };
	}

	virtual ~Image() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void render() override {
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		tex_->render(src_,//dibujar solo el rectangulo de la text
			dest, tr_->getRot());
	}

private:
	Transform *tr_;
	Texture *tex_;
	SDL_Rect src_; //para los spritesheet
};

