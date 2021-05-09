// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <algorithm>
#include <array>
#include <bitset>
#include <vector>
#include <iostream>
#include "Component.h"
#include "ecs.h"

class Manager;
struct Message;

class System {
public:
	virtual ~System() {
	}

	void setMngr(Manager *mngr) {
		manager_ = mngr;
	}

	virtual void init() {
	}

	virtual void update() {
	}

	virtual void receive(const Message&) {
	}

protected:
	Manager *manager_;
};

