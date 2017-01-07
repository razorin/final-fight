#include "CodyIdleJumpAttackState.h"
#include "CodyIdleFallState.h"


CodyIdleJumpAttackState::CodyIdleJumpAttackState() {
}


CodyIdleJumpAttackState::~CodyIdleJumpAttackState() {
}

void CodyIdleJumpAttackState::Start(Player *player) {
	player->setCurrentAnimation(player->animations["iddleJumpAttack"]);
}

PlayerStateMachine *CodyIdleJumpAttackState::Update(Player *player) {
	iPoint speed;
	speed.SetToZero();
	if (player->position->z > -55) {
		speed.z -= player->baseSpeed * 2;
	}
	else if (player->position->z <= -55) {
		return new CodyIdleFallState();

	}
	player->Move(speed);
	return nullptr;
}