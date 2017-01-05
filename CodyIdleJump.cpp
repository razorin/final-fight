#include "CodyIdleJump.h"
#include "Player.h"
#include "Point.h"
#include "CodyIdleFall.h"

CodyIdleJumpState::CodyIdleJumpState() {
}


CodyIdleJumpState::~CodyIdleJumpState() {
}

void CodyIdleJumpState::Start(Player *player) {
	player->setCurrentAnimation(player->animations["iddleJump"]);
}

PlayerStateMachine *CodyIdleJumpState::Update(Player *player) {
	PlayerStateMachine *result = nullptr;
	iPoint speed;
	speed.SetToZero();
	if (player->position->z > -55) {
		speed.z -= player->baseSpeed * 2;
	}
	else if (player->position->z <= -55) {
		return new CodyIdleFall();
	}

	player->Move(speed);

	return result;
}
