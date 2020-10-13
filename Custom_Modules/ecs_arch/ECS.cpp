#include "ECS.h"
#include "scene/2d/sprite.h"
#include <iostream>

//----------------------------------------------------------------------- GoDot class

EcsNode::EcsNode()
{
	
}

EcsNode::~EcsNode()
{
	//Safety check
	//if (!mbIsDeleted)
	//{
	//
	//	Delete stuff here
	//
	//	mbIsDeleted = true;
	//}
}


void EcsNode::_bind_methods()
{
	//ClassDB::bind_method(D_METHOD("setEntityPosition", "ID", "pos"), &EcsNode::setEntityPosition);
}

void EcsNode::_ready()
{
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
			spriteComponent.pSprite->set_texture(spriteComponent.mTextureRef);
			mSpriteComponents.emplace(std::make_pair(entity.ID, spriteComponent));

			//Health component
			HealthComponent health(50);
			mHealthComponents.emplace(std::make_pair(entity.ID, health));

			//Position component
			Position2DComponent pos(get_global_position());
			mPosition2DComponents.emplace(std::make_pair(entity.ID, pos));

			//Movement component
			MovementComponent movement(10.0f, 10.0f, 10.0f, 0.0f, get_viewport_rect().get_size().y, true);
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
			spriteComponent.pSprite->set_texture(spriteComponent.mTextureRef);
			mSpriteComponents.emplace(std::make_pair(entity.ID, spriteComponent));

			//Health component
			HealthComponent health(10);
			mHealthComponents.emplace(std::make_pair(entity.ID, health));

			//Position component
			Position2DComponent pos(get_global_position());
			mPosition2DComponents.emplace(std::make_pair(entity.ID, pos));

			//Movement component
			MovementComponent movement(7.5f, 10.0f, get_viewport_rect().get_size().x, 0.0f, get_viewport_rect().get_size().y);
			mMovementComponents.emplace(std::make_pair(entity.ID, movement));
		}
	}
}

void EcsNode::_update()
{
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
						if (newPosY < movementComponent.mMinPosY)
							newPosY = movementComponent.mMinPosY;

						//Clamp x pos
						if (position2DComponent.mPosition.x > movementComponent.mMaxPosX)
							position2DComponent.mPosition.x = movementComponent.mMaxPosX;
						if (position2DComponent.mPosition.x < movementComponent.mMinPosX)
							position2DComponent.mPosition.x = movementComponent.mMinPosX;

						//Update the position
						Point2 newPosition(position2DComponent.mPosition.x, newPosY);
						mPosition2DComponents.find(it.ID)->second.mPosition = newPosition;
						std::cout << "Player new Pos: " << position2DComponent.mPosition.x << ", " << position2DComponent.mPosition.y << ".\n";
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

						//Clamp x pos
						if (position2DComponent.mPosition.x > movementComponent.mMaxPosX)
							position2DComponent.mPosition.x = movementComponent.mMaxPosX;
						if (position2DComponent.mPosition.x < movementComponent.mMinPosX)
							position2DComponent.mPosition.x = movementComponent.mMinPosX;

						//Update the position
						Point2 newPosition(position2DComponent.mPosition.x, newPosY);
						mPosition2DComponents.find(it.ID)->second.mPosition = newPosition;
						std::cout << "Player new Pos: " << position2DComponent.mPosition.x << ", " << position2DComponent.mPosition.y << ".\n";
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
					mPosition2DComponents.find(it.ID)->second.mPosition = newPosition;

					//std::cout << "Enemy " << it.ID << " new Pos: " << position2DComponent.mPosition.x << ", " << position2DComponent.mPosition.y << ".\n";
				}
			}
		}
	}
}

void EcsNode::_draw()
{
	for (auto& it : mEntitiesVector)
	{
		//Find all the entities with the sprite component
		if (mSpriteComponents.find(it.ID) != mSpriteComponents.end())
		{
			Sprite* pSprite = mSpriteComponents.find(it.ID)->second.pSprite;

			//Get the position2D components
			if (mPosition2DComponents.find(it.ID) != mPosition2DComponents.end())
			{
				Point2 drawPos = mPosition2DComponents.find(it.ID)->second.mPosition;

				//Draw
				//pSprite->_notification(NOTIFICATION_DRAW);
				//pSprite->set_modulate(mSpriteComponents.find(it.ID)->second.mColour);
				//pSprite->set_frame_coords(drawPos);
				//std::cout << "Entity " << it.ID << " has SpriteComponent and Position2DComponent. Pos: " << drawPos.x << ", " << drawPos.y << std::endl;

				draw_texture(mSpriteComponents.find(it.ID)->second.mTextureRef, drawPos);
			}
		}
	}
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
		update();
	}
	case NOTIFICATION_DRAW:
	{
		_draw();
	}

	}
}

//void EcsNode::setEntityPosition(int ID, Point2 pos)
//{
//	//Get the Position2DComponent
//	std::map<int, Position2DComponent>::iterator it;
//	it = mPosition2DComponents.find(ID);
//
//	if (it != mPosition2DComponents.end())
//	{
//		//Set the position
//		it->second.mPosition = pos;
//		//std::cout << "New position: " << pos.x << ", " << pos.y << ".\n";
//	}
//}