#ifndef ENEMY_IDLE_STATE_H
#define ENEMY_IDLE_STATE_H

#include "EnemyStateMachine.h"

class Enemy;

class EnemyIdleState : public EnemyStateMachine {
public:
	EnemyIdleState();
	~EnemyIdleState();

	virtual void Start(Enemy *bred);
	virtual EnemyStateMachine * Update(Enemy *bred);
};

#endif // !ENEMY_IDLE_STATE_H

