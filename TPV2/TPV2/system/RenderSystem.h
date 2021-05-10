#pragma once

#include "../ecs/System.h"
#include "../ecs/Entity.h"

class RenderSystem : public System {
public:
	// - dibujar asteroides, balas y caza (s�lo si el juego no est� parado).
	// - dibujar el marcador y las vidas (siempre).
	// - dibujar el mensaje correspondiente si el juego est� parado (como en la
	// pr�ctica 1)
	// - Otra posibilidad es definir un m�todo render en la clase System, y distribuir
	// este c�digo en los sistemas correspondientes en lugar de tener un s�lo
	// sistema para rendering
	void update() override;
	/*void dibuja(Transform* tr, Texture* tex, SDL_Rect src);*/

private:
	/*Transform* tr_Ast;
	Transform* tr_Bal;
	Texture* tex_Ast;
	Texture* tex_Bal;
	SDL_Rect src_Ast;
	SDL_Rect src_Bal;*/
};