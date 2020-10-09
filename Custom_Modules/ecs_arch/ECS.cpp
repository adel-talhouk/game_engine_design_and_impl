#include "ECS.h"

//----------------------------------------------------------------------- Systems

MovementSystem::MovementSystem()
	:System()
{
}

void MovementSystem::updateSystem()
{

}

CombatSystem::CombatSystem()
	:System()
{
}

void CombatSystem::updateSystem()
{

}

//----------------------------------------------------------------------- GoDot class

EcsNode::EcsNode()
{
	
}

EcsNode::~EcsNode()
{
	//Safety check
	if (!mbIsDeleted)
	{
		//Clear the systems vector
		for (auto it : mSystemsVector)
		{
			delete it;
			it = nullptr;
		}
		mSystemsVector.clear();

		mbIsDeleted = true;
	}
}


void EcsNode::_bind_methods()
{

}

void EcsNode::_ready()
{
	//Create the new systems and add them to the systems vector
	MovementSystem* pMovementSystem = new MovementSystem();
	mSystemsVector.push_back(pMovementSystem);
	CombatSystem* pCombatSystem = new CombatSystem();
	mSystemsVector.push_back(pCombatSystem);
}

void EcsNode::_update()
{
	//Update the systems
	for (auto it : mSystemsVector)
	{
		it->updateSystem();
	}
}

void EcsNode::_draw()
{

}

void EcsNode::_notification(int p_what) 
{
	switch (p_what) 
	{
	case NOTIFICATION_READY:
	{
		_ready();
	}
	case NOTIFICATION_PROCESS:
	{
		_update();
	}
	case NOTIFICATION_DRAW:
	{
		_draw();
	}

	}
}
