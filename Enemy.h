#ifndef ENEMY_H
#define ENEMY_H

#include "Creature.h"
#include "Parson.h"
#include "Point.h"
#include "Parson.h"

class EnemyStateMachine;
struct Collider;
class Player;


enum  ENEMY_TYPE {
	BRED,
	UNKNOWN_ENEMY
};

class Enemy : public Creature {
public:
	Enemy(const JSON_Object *enemyConfig, ENEMY_TYPE type);
	Enemy(const Enemy *other);
	virtual void OnCollision(const Collider &other) = 0;
	virtual void Move(const iPoint &movement) = 0;
	virtual void Init(const iPoint &initialPosition) = 0;
	~Enemy();
	iPoint &distanceToTarget() const;

protected:
	iPoint previousPosition = { 0,0,0 };
	EnemyStateMachine *state = nullptr;

public:
	ENEMY_TYPE type;
	int baseSpeed = 1;
	Collider *attackCollider = nullptr;
	Player *player = nullptr;
};

#endif // !ENEMY_H

