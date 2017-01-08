#include "EnemyIdleState.h"
#include "Enemy.h"
#include "Player.h"
#include "ModuleCollision.h"
#include <ctime>
#include "EnemyMoveState.h"
#include "Timer.h"

EnemyIdleState::EnemyIdleState() : EnemyStateMachine(ENEMY_IDLE){
}


EnemyIdleState::~EnemyIdleState() {
}

void EnemyIdleState::Start(Enemy *enemy) {
	const static std::string anim = "idle";
	enemy->setCurrentAnimation(anim);
	timer->Start();

}

EnemyStateMachine * EnemyIdleState::Update(Enemy *enemy) {
	if (timer->Ellapsed() >= 500) {
		srand(time(NULL));
		int number = rand() % 10 + 1;

		distanceVector = enemy->distanceToTarget();
		flipEnemy(enemy);

		if (number < 5)
			return nullptr;
		else {
			return new EnemyMoveState();
		}
	}
	return nullptr;
}