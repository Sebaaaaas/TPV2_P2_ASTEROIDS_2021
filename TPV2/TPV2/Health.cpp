#include "components/Health.h"

void Health::colocaVidas()
{
	//auto& ents = entity_->getMngr()->getEnteties();
	//int n = ents.size();
	//int vidasRecorridas = 0;
	//for (int i = 0; i < n; i++) { //borramos las vidas anteriores para colocar las nuevas
	//	if (ents[i]->hasGroup<Vidas>()) {
	//		vidasRecorridas++;
	//		if (vidasRecorridas > health) {
	//			ents[i]->setActive(false);
	//		}
	//		else {
	//			auto e = entity_->getMngr()->addEntity();

	//			Vector2D pos = Vector2D(30.0 + i * 30.0, 30.0);

	//			e->addComponent<Transform>(pos, Vector2D(), 25.0, 25.0, 0.0);
	//			e->setGroup<Vidas>(true);
	//			e->addComponent<Image>(&sdlutils().images().at("heart"));
	//		}
	//	}
	//}
	for (int i = 0; i < health; i++) {
		auto e = entity_->getMngr()->addEntity();
		
		Vector2D pos = Vector2D(30.0 + i * 30.0, 30.0);

		e->addComponent<Transform>(pos, Vector2D(), 25.0, 25.0, 0.0);
		e->setGroup<Vidas>(true);
		e->addComponent<Image>(&sdlutils().images().at("heart"));
	}
}

void Health::quitaVida()
{
	health--;
	auto& ents = entity_->getMngr()->getEnteties();
	int n = ents.size();
	int vidasRecorridas = 0;
	for (int i = 0; i < n; i++) { //borramos las vidas anteriores para colocar las nuevas
		if (ents[i]->hasGroup<Vidas>()) {
			vidasRecorridas++;
			if (vidasRecorridas >= health) {
				ents[i]->setActive(false);
			}
		}
	}
}
