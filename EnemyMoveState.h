#ifndef ENEMY_MOVE_STATE_H
#define ENEMY_MOVE_STATE_H

#include "EnemyStateMachine.h"

class Enemy;

class EnemyMoveState : public EnemyStateMachine {
public:
	EnemyMoveState();
	~EnemyMoveState();

	virtual void Start(Enemy *bred);
	virtual EnemyStateMachine * Update(Enemy *bred);
};

#endif // !ENEMY_MOVE_STATE_H

