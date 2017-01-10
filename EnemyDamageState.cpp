#include "EnemyDamageState.h"
#include <string>
#include "Enemy.h"
#include "Animation.h"
#include "EnemyIdleState.h"
#include "EnemyKilledState.h"

EnemyDamageState::EnemyDamageState() : EnemyStateMachine(ENEMY_DAMAGED){
}


EnemyDamageState::~EnemyDamageState() {
}

void EnemyDamageState::Start(Enemy *bred) {
	const static std::string anim = "damage";
	bred->setCurrentAnimation(anim);
	//timer->Start();

}

EnemyStateMachine * EnemyDamageState::Update(Enemy *bred) {
	if (bred->getCurrentAnimation()->Finished()) {
		if (bred->life <= 0)
			return new EnemyKilledState();
		else
			return new EnemyIdleState();
	}
	return nullptr;
}