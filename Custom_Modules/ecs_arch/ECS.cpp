#include "ECS.h"
#include "scene/2d/sprite.h"
#include <iostream>

//----------------------------------------------------------------------- Systems

MovementSystem::MovementSystem()
	:System()
{
	////Player input
	//if (Input::get_singleton()->is_key_pressed(KEY_W)) 
	//{
	//	for (auto& it : EcsNode::getEntitiesVector())
	//	{
	//		//Find all the entities with the movement components and input components
	//		if (mMovementComponents.find(it.ID) != godotComponents.end())
	//		{
	//			godotComponent gd = godotComponents.find(it.ID)->second;
	//			gd.s->set_modulate(gd.c);
	//		}
	//	}
	//}
	//if (Input::get_singleton()->is_key_pressed(KEY_S))
	//{
	//	for (auto& it : entities)
	//	{
	//		if (godotComponents.find(it.ID) != godotComponents.end())
	//		{
	//			godotComponent gd = godotComponents.find(it.ID)->second;
	//			gd.s->set_modulate(Color(1, 1, 1, 1));
	//		}
	//	}
	//}

	////Enemy constant move

}

void MovementSystem::updateSystem()
{
	std::cout << "MovementSystem::updateSystem().\n";
}

CombatSystem::CombatSystem()
	:System()
{
}

void CombatSystem::updateSystem()
{
	std::cout << "CombatSystem::updateSystem().\n";
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
		//Make an entity, give it an ID, and add it to the vector
		Entity entity;
		entity.ID = i;
		mEntitiesVector.push_back(entity);
		
		//If it's the PlayerNode
		if (get_child(i)->get_name() == "PlayerNode")
		{
			//Sprite component
			SpriteComponent spriteComponent((Sprite*)get_child(i));
			spriteComponent.mTextureRef = spriteComponent.pSprite->get_texture();
			mSpriteComponents.emplace(std::make_pair(entity.ID, spriteComponent));

			//Health component
			HealthComponent health(50);
			mHealthComponents.emplace(std::make_pair(entity.ID, health));

			//Position component
			Position2DComponent pos(get_global_position());
			mPosition2DComponents.emplace(std::make_pair(entity.ID, pos));

			//Movement component
			MovementComponent movement(10.0f, 0.0f, get_viewport_rect().get_size().x, 0.0f, get_viewport_rect().get_size().y, true);
			mMovementComponents.emplace(std::make_pair(entity.ID, movement));

			//Combat component
			CombatComponent combat(10, 50);
			mCombatComponents.emplace(std::make_pair(entity.ID, combat));
		}
		else    //Otherwise (enemy)
		{
			//Sprite component
			SpriteComponent spriteComponent((Sprite*)get_child(i));
			spriteComponent.mTextureRef = spriteComponent.pSprite->get_texture();
			mSpriteComponents.emplace(std::make_pair(entity.ID, spriteComponent));

			//Health component
			HealthComponent health(10);
			mHealthComponents.emplace(std::make_pair(entity.ID, health));

			//Position component
			Position2DComponent pos(get_global_position());
			mPosition2DComponents.emplace(std::make_pair(entity.ID, pos));

			//Movement component
			MovementComponent movement(7.5f, 0.0f, get_viewport_rect().get_size().x, 0.0f, get_viewport_rect().get_size().y);
			mMovementComponents.emplace(std::make_pair(entity.ID, movement));
		}
	}
}

void EcsNode::_update()
{
	////Update the systems
	//for (auto it : mSystemsVector)
	//{
	//	it->updateSystem();
	//}

	//W Key		https://docs.godotengine.org/en/stable/classes/class_inputeventkey.html#class-inputeventkey, https://docs.godotengine.org/en/stable/classes/class_@globalscope.html#enum-globalscope-keylist
	if (Input::get_singleton()->is_key_pressed(KEY_W))
	{
		for (auto& it : mEntitiesVector)
		{
			//Find all the entities with the movement components and pposition2d components
			if (mMovementComponents.find(it.ID) != mMovementComponents.end())
			{
				MovementComponent movementComponent = mMovementComponents.find(it.ID)->second;
				
				//As long as this is the player
				if (movementComponent.mbIsPlayer)
				{
					if (mPosition2DComponents.find(it.ID) != mPosition2DComponents.end())
					{
						Position2DComponent position2DComponent = mPosition2DComponents.find(it.ID)->second;
						float newPosY = position2DComponent.mPosition.y - movementComponent.mMoveSpeed;

						//Check the bounds
						if (newPosY > movementComponent.mMaxPosY)
							newPosY = movementComponent.mMaxPosY;

						//Update the position
						Point2 newPosition(position2DComponent.mPosition.x, newPosY);
						position2DComponent.mPosition = newPosition;
					}
				}
			}
		}
	}

	//S Key
	if (Input::get_singleton()->is_key_pressed(KEY_S))
	{
		for (auto& it : mEntitiesVector)
		{
			//Find all the entities with the movement components and pposition2d components
			if (mMovementComponents.find(it.ID) != mMovementComponents.end())
			{
				MovementComponent movementComponent = mMovementComponents.find(it.ID)->second;

				//As long as this is the player
				if (movementComponent.mbIsPlayer)
				{
					if (mPosition2DComponents.find(it.ID) != mPosition2DComponents.end())
					{
						Position2DComponent position2DComponent = mPosition2DComponents.find(it.ID)->second;
						float newPosY = position2DComponent.mPosition.y + movementComponent.mMoveSpeed;

						//Check the bounds
						if (newPosY > movementComponent.mMaxPosY)
							newPosY = movementComponent.mMaxPosY;

						//Update the position
						Point2 newPosition(position2DComponent.mPosition.x, newPosY);
						position2DComponent.mPosition = newPosition;
					}
				}
			}
		}
	}

	//Enemy constant move
	for (auto& it : mEntitiesVector)
	{
		//Find all the entities with the movement components and pposition2d components
		if (mMovementComponents.find(it.ID) != mMovementComponents.end())
		{
			MovementComponent movementComponent = mMovementComponents.find(it.ID)->second;

			//As long as it's not a player
			if (!movementComponent.mbIsPlayer)
			{
				if (mPosition2DComponents.find(it.ID) != mPosition2DComponents.end())
				{
					Position2DComponent position2DComponent = mPosition2DComponents.find(it.ID)->second;
					float newPosX = position2DComponent.mPosition.x - movementComponent.mMoveSpeed;

					//Check the bounds
					if (newPosX < movementComponent.mMinPosX)
						newPosX = movementComponent.mMaxPosX;

					//Update the position
					Point2 newPosition(newPosX, position2DComponent.mPosition.y);
					position2DComponent.mPosition = newPosition;
				}
			}
		}
	}
}

void EcsNode::_draw()
{
	std::cout << "Inside _draw().\n";

	//for (auto& it : mEntitiesVector)
	//{
	//	//Find all the entities with the sprite component
	//	if (mSpriteComponents.find(it.ID) != mSpriteComponents.end())
	//	{
	//		Sprite* pSprite = mSpriteComponents.find(it.ID)->second.pSprite;

	//		pSprite->_notification(NOTIFICATION_DRAW);
	//	}
	//}

	//draw_line(Vector2(0, 0), Vector2(50, 50), Color(255, 0, 0), 1);
	//Vector2 pos = get_global_position();

	//Color c = Color(1, 1, 1, 1);
	//Vector<Color> colors;
	//colors.push_back(c);
	//colors.push_back(c);
	//colors.push_back(c);
	//colors.push_back(c);


	//Vector<Vector2> pts;
	//pts.push_back(pos);
	//pts.push_back(Vector2(pos.x + 30, pos.y));
	//pts.push_back(Vector2(pos.x + 30, pos.y - 30));
	//pts.push_back(Vector2(pos.x, pos.y - 30));

	//Vector<Vector2> uvs;
	//uvs.push_back(Vector2(1, 1));
	//uvs.push_back(Vector2(0, 1));
	//uvs.push_back(Vector2(0, 0));
	//uvs.push_back(Vector2(1, 0));

	//draw_polygon(pts, colors, uvs, mTextureRef);
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
		it->second.mPosition = pos;
		std::cout << "New position: " << pos.x << ", " << pos.y << ".\n";
	}
}