#include "EnemyAttackState.h"
#include "Timer.h"
#include "Enemy.h"
#include <ctime>
#include "Animation.h"
#include "EnemyIdleState.h"

EnemyAttackState::EnemyAttackState() : EnemyStateMachine(ENEMY_ATTACKING) {
}


EnemyAttackState::~EnemyAttackState() {
}

void EnemyAttackState::Start(Enemy *enemy) {
	srand(time(NULL));
	int number = rand() % enemy->attacks.size();
	enemy->setCurrentAnimation(enemy->attacks.at(number));
	timer->Start();

}

EnemyStateMachine * EnemyAttackState::Update(Enemy *enemy) {
	distanceVector = enemy->distanceToTarget();
	flipEnemy(enemy);

	if (enemy->getCurrentAnimation()->Finished())
		return new EnemyIdleState();

	return nullptr;
}