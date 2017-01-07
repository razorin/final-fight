#include "CodyMovementFallState.h"
#include "Player.h"
#include "Animation.h"
#include "CodyIdleState.h"


CodyMovementFallState::CodyMovementFallState() {
}


CodyMovementFallState::~CodyMovementFallState() {
}

void CodyMovementFallState::Start(Player *player) {
	player->setCurrentAnimation(player->animations["fall"]);
}

PlayerStateMachine *CodyMovementFallState::Update(Player *player) {
	PlayerStateMachine *result = nullptr;
	iPoint speed;
	speed.SetToZero();

	if (player->position->z >= 0) {
		player->animations["iddleJump"]->Reset();
		player->animations["fall"]->Reset();
		return new CodyIdleState();
	}
	else {
		if (player->getCurrentAnimation()->Finished())
			player->setCurrentAnimation(player->animations["lastIddleJump"]);

		speed.z += player->baseSpeed * 2;
		speed.x += (player->flipped ? -player->baseSpeed : player->baseSpeed) * 2;

	}

	player->Move(speed);

	return result;
}