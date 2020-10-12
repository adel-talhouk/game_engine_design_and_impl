#include "ECS.h"
#include <iostream>

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

	//Iterate through the children
	for (int64_t i = 0; i < childCount; i++) 
	{
		std::cout << "For-loop: i = " << i << ".\n";
		//Make an entity, give it an ID, and add it to the vector
		Entity entity;
		entity.ID = i;
		mEntitiesVector.push_back(entity);
		
		//If it's the PlayerNode
		if (get_child(i)->get_name() == "PlayerNode")
		{
			std::cout << "Inside if-statement.\n";

			//Sprite component
			SpriteComponent spriteComponent((Sprite*)get_child(i));
			mSpriteComponents.emplace(std::make_pair(entity.ID, spriteComponent));
			std::cout << "Added sprite component to PlayerNode.\n";

			//Health component
			HealthComponent health(50);
			mHealthComponents.emplace(std::make_pair(entity.ID, health));
			std::cout << "Added health component to PlayerNode.\n";

			//Position component
			Position2DComponent pos(get_global_position());
			mPosition2DComponents.emplace(std::make_pair(entity.ID, pos));
			std::cout << "Added position2d component to PlayerNode.\n";

			//Movement component
			MovementComponent movement(10.0f, 0.0f, get_viewport_rect().get_size().x, 0.0f, get_viewport_rect().get_size().y);
			mMovementComponents.emplace(std::make_pair(entity.ID, movement));
			std::cout << "Added movement component to PlayerNode.\n";

			//Combat component
			CombatComponent combat(10, 50);
			mCombatComponents.emplace(std::make_pair(entity.ID, combat));
			std::cout << "Added combat component to PlayerNode.\n";
		}
		else    //Otherwise (enemy)
		{
			std::cout << "Inside else-statement.\n";

			//Sprite component
			SpriteComponent spriteComponent((Sprite*)get_child(i));
			mSpriteComponents.emplace(std::make_pair(entity.ID, spriteComponent));
			std::cout << "Added sprite component to " << get_child(i)->get_name() << ".\n";

			//Health component
			HealthComponent health(10);
			mHealthComponents.emplace(std::make_pair(entity.ID, health));
			std::cout << "Added health component to " << get_child(i)->get_name() << ".\n";

			//Position component
			Position2DComponent pos(get_global_position());
			mPosition2DComponents.emplace(std::make_pair(entity.ID, pos));
			std::cout << "Added position2d component to " << get_child(i)->get_name() << ".\n";

			//Movement component
			MovementComponent movement(7.5f, 0.0f, get_viewport_rect().get_size().x, 0.0f, get_viewport_rect().get_size().y);
			mMovementComponents.emplace(std::make_pair(entity.ID, movement));
			std::cout << "Added movement component to " << get_child(i)->get_name() << ".\n";
		}

		std::cout << "Outside of if-else-statement, in for-loop.\n";
	}
}

void EcsNode::_update()
{
	//update();

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
		std::cout << "New position: " << pos.x << ", " << pos.y << ".\n";
	}
}