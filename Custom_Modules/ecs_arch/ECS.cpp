#include "ECS.h"

EcsNode::EcsNode() {}
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

//----------------------------------------------------------------------- Systems

void MovementSystem::updateSystem()
{

}

void CombatSystem::updateSystem()
{

}

//----------------------------------------------------------------------- GoDot class

void EcsNode::_update()
{
	//Update the systems
	for (auto it : mSystemsVector)
	{
		it->updateSystem();
	}
}

void EcsNode::_notification(int p_what) 
{
	switch (p_what) 
	{
	case NOTIFICATION_PROCESS:
	{
		_update();
	}
	case NOTIFICATION_READY:
	{
		_ready();
	}
	case NOTIFICATION_DRAW:
	{
		_draw();
	}

	}
}
