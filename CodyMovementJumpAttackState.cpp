#include "CodyMovementJumpAttackState.h"
#include "Player.h"
#include "Animation.h"

#include "CodyMovementFallState.h"


CodyMovementJumpAttackState::CodyMovementJumpAttackState() {
}


CodyMovementJumpAttackState::~CodyMovementJumpAttackState() {
}


void CodyMovementJumpAttackState::Start(Player *player) {
	player->setCurrentAnimation("moveJumpAttack");
}

PlayerStateMachine *CodyMovementJumpAttackState::Update(Player *player) {

	if (player->position->z > -55) {
		player->speed.z -= player->baseSpeed * 2;
		player->speed.x += (player->flipped ? -player->baseSpeed : player->baseSpeed) * 2;
	}
	else if (player->position->z <= -55) {
		return new CodyMovementFallState();

	}
	return nullptr;
}