//insert the Headername here
#ifndef ECS_H
#define ECS_H
#include <vector>
#include <map>
#include "scene/2d/node_2d.h"
#include "scene/2d/sprite.h"
#include "core/array.h"
#include "core/color.h"
#include "core/os/keyboard.h"
#include "core/os/input_event.h"
#include "core/os/input.h"

//Entity struct
struct Entity
{
	int ID;
};

//----------------------------------------------------------------------- Components

//Sprite
struct SpriteComponent
{
	//Constructor(s) and Destructor
	SpriteComponent(Sprite* sprite, Color colour = Color(0.0f, 0.0f, 0.0f, 1.0f)) : pSprite(sprite), mColour(colour) {};
	~SpriteComponent() { delete pSprite; pSprite = nullptr; };

	Sprite* pSprite;
	Color mColour;
};

//Health
struct HealthComponent
{
	//Constructor(s) and Destructor
	HealthComponent(int maxHealth) : mMaxHealth(maxHealth), mCurrentHealth(maxHealth) {};
	~HealthComponent() {};

	int mMaxHealth;
	int mCurrentHealth;
};

//Position
struct Position2DComponent
{
	//Constructor(s) and Destructor
	Position2DComponent(float locX, float locY) : mLocX(locX), mLocY(locY) {};
	~Position2DComponent() {};

	float mLocX;
	float mLocY;
};

//Movement
struct MovementComponent
{
	//Constructor(s) and Destructor
	MovementComponent(float moveSpeed, float minPosX, float maxPosX, float minPosY, float maxPosY)
		:mMoveSpeed(moveSpeed), mMinPosX(minPosX), mMaxPosX(maxPosX)
		, mMinPosY(minPosY), mMaxPosY(maxPosY) {};
	~MovementComponent() {};

	float mMoveSpeed;
	float mMinPosX;
	float mMaxPosX;
	float mMinPosY;
	float mMaxPosY;
};

//Projectile
struct ProjectileComponent
{
	//Constructor(s) and Destructor
	ProjectileComponent(float moveSpeed, int damageValue) : mMoveSpeed(moveSpeed), mDamageValue(damageValue) {};
	~ProjectileComponent() {};

	float mMoveSpeed;
	int mDamageValue;
};

//----------------------------------------------------------------------- Systems
class System
{
public:
	System() {};
	virtual ~System() {};
	virtual void updateSystem() = 0;
};

class MovementSystem : public System
{
public:
	MovementSystem();
	~MovementSystem() {};
	void updateSystem();
};

class CombatSystem : public System
{
public:
	CombatSystem();
	~CombatSystem() {};
	void updateSystem();
};

//----------------------------------------------------------------------- GoDot class

//Entity Node in GoDot
class EcsNode : public Node2D
{
	GDCLASS(EcsNode, Node2D);
	bool mbIsDeleted = false;	//Safety check

protected:
	static void _bind_methods();
	std::vector<Entity> mEntitiesVector;

	//Components
	std::map<int, SpriteComponent> mSpriteComponents;
	std::map<int, HealthComponent> mHealthComponents;
	std::map<int, Position2DComponent> mPosition2DComponents;
	std::map<int, MovementComponent> mMovementComponents;
	std::map<int, ProjectileComponent> mProjectileComponents;

	//Systems
	std::vector<System*> mSystemsVector;

public:
	EcsNode();
	~EcsNode();
	void _ready();
	void _update();
	void _draw();
	void _notification(int p_what);
	//void _input(Variant event);
};


#endif
