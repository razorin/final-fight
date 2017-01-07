#include "CodyIdleJumpState.h"
#include "Player.h"
#include "Point.h"
#include "Application.h"
#include "ModuleInput.h"
#include "CodyIdleFallState.h"
#include "CodyIdleJumpAttackState.h"

CodyIdleJumpState::CodyIdleJumpState() {
}


CodyIdleJumpState::~CodyIdleJumpState() {
}

void CodyIdleJumpState::Start(Player *player) {
	player->setCurrentAnimation(player->animations["iddleJump"]);
}

PlayerStateMachine *CodyIdleJumpState::Update(Player *player) {
	iPoint speed;
	speed.SetToZero();
	if (player->position->z > -55) {
		speed.z -= player->baseSpeed * 2;
		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) {
			return new CodyIdleJumpAttackState();
		}
	}
	else if (player->position->z <= -55) {
		return new CodyIdleFallState();
	}

	player->Move(speed);

	return nullptr;
}