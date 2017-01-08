#include "EnemyMoveState.h"
#include <ctime>
#include "Enemy.h"
#include "Player.h"
#include "EnemyIdleState.h"
#include "ModuleCollision.h"
#include "Point.h"
#include "Timer.h"

EnemyMoveState::EnemyMoveState() : EnemyStateMachine(ENEMY_MOVING) {
}


EnemyMoveState::~EnemyMoveState() {
}


void EnemyMoveState::Start(Enemy *enemy) {
	const static std::string anim = "movement";
	enemy->setCurrentAnimation(anim);
	timer->Start();
}

EnemyStateMachine * EnemyMoveState::Update(Enemy *enemy) {

	if (timer->Ellapsed() >= 1000) {
		srand(time(NULL));
		int number = rand() % 10 + 1;

		if (number < 6)
			return new EnemyIdleState();
	}

	distanceVector = enemy->distanceToTarget();
	flipEnemy(enemy);

	if (!distanceVector.IsZero()) {
		if (distanceVector.x != 0 && distanceVector.y != 0) {
			if(rand() % 2 == 0)
				enemy->speed.x = distanceVector.x < 0 ? -enemy->baseSpeed : distanceVector.x > 0 ? enemy->baseSpeed : 0;
			else
				enemy->speed.y = distanceVector.y < 0 ? -enemy->baseSpeed : distanceVector.y > 0 ? enemy->baseSpeed : 0;
		}
		else if (distanceVector.x != 0) {
			enemy->speed.x = distanceVector.x < 0 ? -enemy->baseSpeed : distanceVector.x > 0 ? enemy->baseSpeed : 0;
		} else if(distanceVector.y != 0){
			enemy->speed.y = distanceVector.y < 0 ? -enemy->baseSpeed : distanceVector.y > 0 ? enemy->baseSpeed : 0;

		}
	} 

	//TODO: if distance is near...ATTACK!d


	return nullptr;
	
}
