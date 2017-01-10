#include "EnemyAttackState.h"
#include "Timer.h"
#include "Enemy.h"
#include <ctime>
#include "Animation.h"
#include "EnemyIdleState.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "Attack.h"

EnemyAttackState::EnemyAttackState() : EnemyStateMachine(ENEMY_ATTACKING) {
}


EnemyAttackState::~EnemyAttackState() {
}

void EnemyAttackState::Start(Enemy *bred) {
	srand(time(NULL));
	int number = rand() % bred->attacks.size();
	Attack attack = bred->attacks.at(number);
	bred->setCurrentAnimation(attack.name);
	if (bred->attackCollider != nullptr) {
		bred->attackCollider->to_delete = true;
	}
	int attack_x = bred->positionCollider->rect.x + (bred->flipped ? -(bred->positionCollider->rect.w / 2) : (bred->positionCollider->rect.w / 2));

	bred->attackCollider = App->collision->AddCollider({ attack_x, bred->positionCollider->rect.y - attack.y, attack.x, bred->positionCollider->rect.h + attack.y * 2 }, COLLIDER_TYPE::ENEMY_HIT, false, false, std::bind(&Enemy::OnCollision, bred, std::placeholders::_1), bred);
}

EnemyStateMachine * EnemyAttackState::Update(Enemy *bred) {
	distanceVector = bred->distanceToTarget();
	flipEnemy(bred);

	if (bred->getCurrentAnimation()->Finished())
		return new EnemyIdleState();

	return nullptr;
}