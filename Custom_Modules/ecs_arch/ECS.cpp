#include "ECS.h"
#include "scene/2d/sprite.h"
#include <core/engine.h>

#include <iostream>
#include <ctime>

//----------------------------------------------------------------------- GoDot class

EcsNode::EcsNode()
{
	//Make it process automatically
	set_process(true);

	//Seed rand
	srand(time(0));
}

EcsNode::~EcsNode()
{
	
}


void EcsNode::_bind_methods()
{

}

void EcsNode::_ready()
{
	//Do not let it run in the editor
	if (!Engine::get_singleton()->is_editor_hint())
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
				Sprite* pSprite = (Sprite*)get_child(i);
				SpriteComponent spriteComponent(pSprite->get_texture());
				mSpriteComponents.emplace(std::make_pair(entity.ID, spriteComponent));

				//Health component
				HealthComponent health(50);
				mHealthComponents.emplace(std::make_pair(entity.ID, health));

				//Position component
				Position2DComponent pos(get_global_position());
				mPosition2DComponents.emplace(std::make_pair(entity.ID, pos));

				//Movement component
				MovementComponent movement(10.0f, 10.0f, 10.0f, 0.0f, get_viewport_rect().get_size().y - 100, true);
				mMovementComponents.emplace(std::make_pair(entity.ID, movement));

				//Combat component
				CombatComponent combat(10, 300);
				mCombatComponents.emplace(std::make_pair(entity.ID, combat));
			}
			else    //Otherwise (enemy)
			{
				//Sprite component
				Sprite* pSprite = (Sprite*)get_child(i);
				SpriteComponent spriteComponent(pSprite->get_texture());
				mSpriteComponents.emplace(std::make_pair(entity.ID, spriteComponent));

				//Health component
				HealthComponent health(10);
				mHealthComponents.emplace(std::make_pair(entity.ID, health));

				//Position component
				Point2 positionOffset((i - 1) * rand() % 500 + 50, (i - 1) * 250);	//i - 1 to account for the player being at index 0
				Point2 spawnPos(get_viewport_rect().get_size().x - positionOffset.x, positionOffset.y);
				Position2DComponent pos (spawnPos);
				mPosition2DComponents.emplace(std::make_pair(entity.ID, pos));

				//Movement component
				MovementComponent movement(10.0f, 10.0f, get_viewport_rect().get_size().x, 0.0f, get_viewport_rect().get_size().y);
				mMovementComponents.emplace(std::make_pair(entity.ID, movement));
			}
		}
		std::cout << "\t\t Press the Space Bar to start the game.\n\n\n\n";
	}
}

void EcsNode::_update()
{
	//Start the game	(make sure this does not happen in the editor)
	if (!Engine::get_singleton()->is_editor_hint() && !mbGameStart)
	{
		//If they press space
		if (Input::get_singleton()->is_key_pressed(KEY_SPACE))
		{
			//They can start the game
			mbGameStart = true;
		}
	}

	//If the game started, and still did not end
	if (mbGameStart && !mbGameEnd)
	{
		//W Key		https://docs.godotengine.org/en/stable/classes/class_@globalscope.html#enum-globalscope-keylist
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
						}
					}
				}
			}
		}

		//Space key
		if (Input::get_singleton()->is_key_pressed(KEY_SPACE))
		{
			//Player ID and distance vector
			int playerID = 0;
			Point2 distance;

			//Get the combat component
			Position2DComponent playerPosition2DComponent = mPosition2DComponents.find(playerID)->second;
			CombatComponent playerCombatComponent = mCombatComponents.find(playerID)->second;

			//Go through the rest of the entities
			for (auto& it : mEntitiesVector)
			{
				//Make sure this is not the player
				if (it.ID != playerID)
				{
					//Components
					Position2DComponent enemyPosition2DComponent = mPosition2DComponents.find(it.ID)->second;
					MovementComponent enemyMovementComponent = mMovementComponents.find(it.ID)->second;
					HealthComponent enemyHealthComponent = mHealthComponents.find(it.ID)->second;

					//Calculate the distance
					distance = enemyPosition2DComponent.mPosition - playerPosition2DComponent.mPosition;

					//Check if it's less than the range
					if (distance.length() <= playerCombatComponent.mRange)
					{
						//Inflict damage to the enemy
						enemyHealthComponent.mCurrentHealth -= playerCombatComponent.mDamageValue;

						//If it is 0
						if (enemyHealthComponent.mCurrentHealth <= 0)
						{
							//Reset their position (random Y)
							float randomRespawnPosY = rand() % (int)enemyMovementComponent.mMaxPosY - ((int)enemyMovementComponent.mMinPosY + 100);
							Point2 newPosition(enemyMovementComponent.mMaxPosX, randomRespawnPosY);
							mPosition2DComponents.find(it.ID)->second.mPosition = newPosition;
							mScore++;
							std::cout << "Enemy killed. Score: " << mScore << ".\n";

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
						{
							newPosX = movementComponent.mMaxPosX;

							//Loss state
							std::cout << "\n\n\t\tGAME OVER. SCORE: " << mScore << " PTS.\n\n\n\n";
							mbGameEnd = true;
						}

						//Update the position
						Point2 newPosition(newPosX, position2DComponent.mPosition.y);
						mPosition2DComponents.find(it.ID)->second.mPosition = newPosition;
					}
				}
			}
		}
	}
}

void EcsNode::_draw()
{
	//Do not let it run in the editor
	if (!Engine::get_singleton()->is_editor_hint())
	{
		for (auto& it : mEntitiesVector)
		{
			//Find all the entities with the sprite component
			if (mSpriteComponents.find(it.ID) != mSpriteComponents.end())
			{
				Ref<Texture> textureRef = mSpriteComponents.find(it.ID)->second.mTextureRef;

				//Get the position2D components
				if (mPosition2DComponents.find(it.ID) != mPosition2DComponents.end())
				{
					Point2 drawPos = mPosition2DComponents.find(it.ID)->second.mPosition;

					//Draw
					draw_texture(textureRef, drawPos);
				}
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
		break;
	}
	case NOTIFICATION_PROCESS:
	{
		_update();
		update();
		break;
	}
	case NOTIFICATION_DRAW:
	{
		_draw();
		break;
	}

	}
}