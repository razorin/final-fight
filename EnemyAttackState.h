#ifndef ENEMY_ATTACK_STATE_H
#define ENEMY_ATTACK_STATE_H

#include "EnemyStateMachine.h"

class Enemy;

class EnemyAttackState : public EnemyStateMachine {
public:
	EnemyAttackState();
	~EnemyAttackState();
	virtual void Start(Enemy *bred);
	virtual EnemyStateMachine * Update(Enemy *bred);
};

#endif // !ENEMY_ATTACK_STATE_H

