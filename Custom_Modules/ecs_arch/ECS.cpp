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
	ClassDB::bind_method(D_METHOD("setEntityPosition", "ID", "pos"), &EcsNode::setEntityPosition);
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

	//Shared components
	Sprite* theSprite;


	//Iterate through the children
	for (int64_t i = 0; i < childCount; i++) 
	{
		//Make an entity, give it an ID, and add it to the vector
		Entity entity;
		entity.ID = i;
		mEntitiesVector.push_back(entity);

		//Sprite Component
		theSprite = (Sprite*)get_child(i);
		SpriteComponent spriteComponent(theSprite);

		//Add the component to the map
		mSpriteComponents.emplace(std::make_pair(entity.ID, spriteComponent));

		//If it's the PlayerNode
		if (get_child(i)->get_name() == "PlayerNode")
		{
			//Health component
			HealthComponent health(50);
			mHealthComponents.emplace(std::make_pair(entity.ID, health));

			//Position component
			Position2DComponent pos(get_global_position());
			mPosition2DComponents.emplace(std::make_pair(entity.ID, pos));

			//Movement component


			//Projectiles?

		}
		else    //Otherwise (enemy)
		{
			//Health component


			//Position component


			//Movement component

		}
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

void EcsNode::setEntityPosition(int ID, Point2 pos)
{
	//Get the Position2DComponent
	std::map<int, Position2DComponent>::iterator it;
	it = mPosition2DComponents.find(ID);

	if (it != mPosition2DComponents.end())
	{
		//Set the position
		it->second = Position2DComponent(pos);
	}
}