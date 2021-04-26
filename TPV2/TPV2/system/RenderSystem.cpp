#include "RenderSystem.h"
#include "GameCtrlSystem.h"
void RenderSystem::update()
{
	auto n = manager_->getEnteties().size(); 
	for (auto i = 0u; i < n; i++)
		manager_->getEnteties()[i]->render();
	
}
