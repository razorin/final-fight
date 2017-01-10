#include "EnemyKilledState.h"
#include "EnemyIdleState.h"
#include "Enemy.h"
#include "Animation.h"
#include "ModuleCollision.h"


EnemyKilledState::EnemyKilledState() : EnemyStateMachine(ENEMY_KILLED){
}


EnemyKilledState::~EnemyKilledState() {
}

void EnemyKilledState::Start(Enemy *bred) {
	const static std::string anim = "killed";
	--bred->lives;
	bred->setCurrentAnimation(anim);
}

EnemyStateMachine * EnemyKilledState::Update(Enemy *bred) {
	if (bred->getCurrentAnimation()->Finished()) {
		if (bred->lives <= 0) {
			bred->positionCollider->to_delete = true;
			bred->to_delete = true;
		}
		else
			return new EnemyIdleState();
	}
	return nullptr;
}

EnemyStateMachine * EnemyKilledState::ChangeTo(ENEMY_STATE enemyState) {
	return nullptr;
}
