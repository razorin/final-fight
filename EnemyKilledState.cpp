#include "EnemyKilledState.h"
#include "EnemyIdleState.h"
#include "Enemy.h"
#include "Animation.h"


EnemyKilledState::EnemyKilledState() : EnemyStateMachine(ENEMY_KILLED){
}


EnemyKilledState::~EnemyKilledState() {
}

void EnemyKilledState::Start(Enemy *enemy) {
	const static std::string anim = "killed";
	--enemy->lives;
	enemy->setCurrentAnimation(anim);
}

EnemyStateMachine * EnemyKilledState::Update(Enemy *enemy) {
	if (enemy->getCurrentAnimation()->Finished()) {
		if (enemy->lives <= 0)
			enemy->to_delete = true;
		else
			return new EnemyIdleState();
	}
	return nullptr;
}