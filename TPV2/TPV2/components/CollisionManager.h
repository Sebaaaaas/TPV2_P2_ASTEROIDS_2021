#pragma once
#include "../ecs/Component.h"

class CollisionManager : public Component {
public:
	CollisionManager();
	virtual ~CollisionManager();
	void init() override;
	void update() override;
};