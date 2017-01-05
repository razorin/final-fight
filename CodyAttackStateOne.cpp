#include "CodyAttackStateOne.h"
#include "Player.h"
#include "Animation.h"
#include "CodyIdleState.h"

CodyAttackStateOne::CodyAttackStateOne() {
}


CodyAttackStateOne::~CodyAttackStateOne() {
}

void CodyAttackStateOne::Start(Player *player) {
	player->setCurrentAnimation(player->animations["attack1"]);
}

PlayerStateMachine *CodyAttackStateOne::Update(Player *player) {
	if (player->getCurrentAnimation()->Finished()) {
		return new CodyIdleState();
	}
	return nullptr;
}