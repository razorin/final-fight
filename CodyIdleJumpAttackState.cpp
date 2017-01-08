#include "CodyIdleJumpAttackState.h"
#include "CodyIdleFallState.h"


CodyIdleJumpAttackState::CodyIdleJumpAttackState() {
}


CodyIdleJumpAttackState::~CodyIdleJumpAttackState() {
}

void CodyIdleJumpAttackState::Start(Player *player) {
	player->setCurrentAnimation("iddleJumpAttack");
}

PlayerStateMachine *CodyIdleJumpAttackState::Update(Player *player) {
	if (player->position->z > -55) {
		player->speed.z -= player->baseSpeed * 2;
	}
	else if (player->position->z <= -55) {
		return new CodyIdleFallState();

	}
	return nullptr;
}