#include "EnemyIdleState.h"
#include "Enemy.h"
#include "Player.h"
#include "ModuleCollision.h"
#include <ctime>
#include "EnemyMoveState.h"
#include "Timer.h"
#include "EnemyAttackState.h"

EnemyIdleState::EnemyIdleState() : EnemyStateMachine(ENEMY_IDLE){
}


EnemyIdleState::~EnemyIdleState() {
}

void EnemyIdleState::Start(Enemy *bred) {
	const static std::string anim = "idle";
	bred->setCurrentAnimation(anim);
	timer->Start();

}

EnemyStateMachine * EnemyIdleState::Update(Enemy *bred) {
	//return new EnemyAttackState();
	distanceVector = bred->distanceToTarget();
	flipEnemy(bred);
	if (timer->Ellapsed() >= 500) {
		srand(time(NULL));
		int number = rand() % 10 + 1;


		if (number < 5)
			return nullptr;
		else {
			return new EnemyMoveState();
		}
	}
	return nullptr;
}