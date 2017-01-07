#include "CodyMovementJumpState.h"

#include "Player.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleInput.h"

#include "CodyIdleFallState.h"
#include "CodyMovementFallState.h"
#include "CodyMovementJumpAttackState.h"


CodyMovementJumpState::CodyMovementJumpState() {
}


CodyMovementJumpState::~CodyMovementJumpState() {
}


void CodyMovementJumpState::Start(Player *player) {
	player->setCurrentAnimation(player->animations["moveJump"]);
}

PlayerStateMachine *CodyMovementJumpState::Update(Player *player) {
	iPoint speed;
	speed.SetToZero();
	if (player->position->z > -55) {
		speed.z -= player->baseSpeed * 2;
		speed.x += (player->flipped ? -player->baseSpeed : player->baseSpeed) * 2;
		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) {
			return new CodyMovementJumpAttackState();
		}
	}
	else if (player->position->z <= -55) {
		return new CodyMovementFallState();
	}

	player->Move(speed);

	return nullptr;
}