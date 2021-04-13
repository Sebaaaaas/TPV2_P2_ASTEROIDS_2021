#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class Follow : public Component {
public:
	Follow() :
		tr_(nullptr), 
		lastTime_(0)
	{}

	virtual ~Follow() {}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override 
	{
		auto nave = entity_->getMngr()->getHandler<Nave>();
		auto naTR = nave->getComponent<Transform>();
		Vector2D naPos = naTR->getPos();
		Vector2D posAst = tr_->getPos();
		Vector2D velAst = tr_->getVel();

		if (sdlutils().currRealTime() > lastTime_ + 100) {

			lastTime_ = sdlutils().currRealTime();
			auto& vel = tr_->getVel();
			vel = velAst.rotate(velAst.angle(naPos - posAst) > 0 ? 1.0f : -1.0f);
		}
	}

private:
	Transform* tr_;
	float angulo = 25;
	Uint32 lastTime_;
};
