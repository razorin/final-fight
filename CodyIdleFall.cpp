#include "CodyIdleFall.h"
#include "Player.h"
#include "Point.h"
#include "CodyIdleState.h"
#include "Animation.h"

CodyIdleFall::CodyIdleFall() {
}


CodyIdleFall::~CodyIdleFall() {
}

void CodyIdleFall::Start(Player *player) {
	player->setCurrentAnimation(player->animations["fall"]);
}

PlayerStateMachine *CodyIdleFall::Update(Player *player) {
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
	}

	player->Move(speed);

	return result;
}