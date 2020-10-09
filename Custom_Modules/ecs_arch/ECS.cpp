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

	//See how many children this node has
	int64_t childCount = get_child_count();
	mEntitiesVector.resize(childCount);

	//Iterate through the children															//HERE
	for (int64_t i = 0; i < childCount; i++) 
	{
		//Set the sprite
		//s = (Sprite*)get_child(i);
		//godotComponent gd;
		//gd.s = s;
		//gd.c = Color(1, 0, 0, 1.0f);

		//Make an entity, give it an ID, and add it to the vector
		Entity entity;
		entity.ID = i;
		mEntitiesVector.push_back(entity);

		//Add the component to the map
		//godotComponents.emplace(std::make_pair(e.ID, gd));
	}
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
