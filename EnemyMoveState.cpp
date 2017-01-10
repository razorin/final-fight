#include "EnemyMoveState.h"
#include <ctime>
#include "Enemy.h"
#include "Player.h"
#include "EnemyIdleState.h"
#include "ModuleCollision.h"
#include "Point.h"
#include "Timer.h"
#include "EnemyAttackState.h"

EnemyMoveState::EnemyMoveState() : EnemyStateMachine(ENEMY_MOVING) {
}


EnemyMoveState::~EnemyMoveState() {
}


void EnemyMoveState::Start(Enemy *bred) {
	const static std::string anim = "movement";
	bred->setCurrentAnimation(anim);
	timer->Start();
}

EnemyStateMachine * EnemyMoveState::Update(Enemy *bred) {
	distanceVector = bred->distanceToTarget();
	flipEnemy(bred);

	
	if (distanceVector.x <= 30 && distanceVector.x >= -30 &&
		distanceVector.y <= 10 && distanceVector.y >= -10) {
		srand(time(NULL));
		int number = rand() % 10 + 1;
		if (number > 6)
			return new EnemyAttackState();
		else
			return new EnemyIdleState();
	}

	if (timer->Ellapsed() >= 1000) {
		srand(time(NULL));
		int number = rand() % 10 + 1;

		if (number < 7)
			return new EnemyIdleState();
	}


	if (!distanceVector.IsZero()) {
		if (distanceVector.x != 0 && distanceVector.y != 0) {
			if(rand() % 2 == 0)
				bred->speed.x = distanceVector.x < 0 ? -bred->baseSpeed : distanceVector.x > 0 ? bred->baseSpeed : 0;
			else
				bred->speed.y = distanceVector.y < 0 ? -bred->baseSpeed : distanceVector.y > 0 ? bred->baseSpeed : 0;
		}
		else if (distanceVector.x != 0) {
			bred->speed.x = distanceVector.x < 0 ? -bred->baseSpeed : distanceVector.x > 0 ? bred->baseSpeed : 0;
		} else if(distanceVector.y != 0){
			bred->speed.y = distanceVector.y < 0 ? -bred->baseSpeed : distanceVector.y > 0 ? bred->baseSpeed : 0;

		}
	} 



	return nullptr;
	
}
