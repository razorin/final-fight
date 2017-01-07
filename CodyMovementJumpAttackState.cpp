#include "CodyMovementJumpAttackState.h"
#include "Player.h"
#include "Animation.h"

#include "CodyMovementFallState.h"


CodyMovementJumpAttackState::CodyMovementJumpAttackState() {
}


CodyMovementJumpAttackState::~CodyMovementJumpAttackState() {
}


void CodyMovementJumpAttackState::Start(Player *player) {
	player->setCurrentAnimation(player->animations["moveJumpAttack"]);
}

PlayerStateMachine *CodyMovementJumpAttackState::Update(Player *player) {
	iPoint speed;
	speed.SetToZero();
	if (player->position->z > -55) {
		speed.z -= player->baseSpeed * 2;
		speed.x += (player->flipped ? -player->baseSpeed : player->baseSpeed) * 2;
	}
	else if (player->position->z <= -55) {
		return new CodyMovementFallState();

	}
	player->Move(speed);
	return nullptr;
}