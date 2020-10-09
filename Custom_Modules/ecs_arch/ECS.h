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

//Sprite component
struct SpriteComponent
{
	Sprite* sprite = NULL;
	Color colour = Color(0, 0, 0, 1);
};

//Position
struct Position2DComponent
{
	float locX;
	float locY;
};

//Movement
struct MovementComponent
{
	float moveSpeed;
	float minPosX;
	float maxPosX;
	float minPosY;
	float maxPosY;
};

//Health
struct HealthComponent
{
	int maxHealth;
	int currentHealth;
};

//Projectile
struct ProjectileComponent
{
	float speed;
	int damageValue;
};

//Entity Node in GoDot
class PlayerNode : public Node2D
{
	GDCLASS(PlayerNode, Node2D);

protected:
	static void _bind_methods();
	Entity mPlayerEntity;

	//Components
	SpriteComponent mSpriteComponent;
	Position2DComponent mPosition2DComponent;
	MovementComponent mMovementComponent;
	HealthComponent mHealthComponent;
	ProjectileComponent mProjectileComponent;

public:
	PlayerNode();
	~PlayerNode();
	void _notification(int p_what);
	void _update();
	void _ready();
	void _draw();
	//void _input(Variant event);
};

class EnemyNode : public Node2D
{
	GDCLASS(EnemyNode, Node2D);

protected:
	static void _bind_methods();
	Entity mEnemyEntity;

	//Components
	SpriteComponent mSpriteComponent;
	Position2DComponent mPosition2DComponent;
	MovementComponent mMovementComponent;
	HealthComponent mHealthComponent;

public:
	EnemyNode();
	~EnemyNode();
	void _notification(int p_what);
	void _update();
	void _ready();
	void _draw();
	//void _input(Variant event);
};

#endif
