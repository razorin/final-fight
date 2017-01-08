#include "Enemy.h"
#include "Globals.h"
#include "ModuleCollision.h"
#include "EnemyIdleState.h"
#include <cassert>
#include "Player.h"
#include "Point.h"
#include "Animation.h"
#include "Globals.h"

Enemy::Enemy(const JSON_Object *enemyConfig, ENEMY_TYPE type) : type(type), Creature(enemyConfig, ENTITY_TYPE::ENEMY){
	state = new EnemyIdleState();
	JSON_Array *configAttacks = json_object_dotget_array(enemyConfig, "attacks");

	for (int i = 0; i < json_array_get_count(configAttacks); ++i) {
		JSON_Object *configAttack = json_array_get_object(configAttacks, i);
		attacks.push_back(json_object_dotget_string(configAttack, "name"));
	}
}

Enemy::Enemy(const Enemy *other) : type(other->type), attacks(other->attacks), Creature(other){
	state = new EnemyIdleState();
}


Enemy::~Enemy() {
	RELEASE(state);
	if (attackCollider != nullptr)
		attackCollider->to_delete = true;
}

iPoint &Enemy::distanceToTarget() const {
	iPoint result{ 0,0,0 };
	if (player != nullptr) {
		iPoint playerPoint = player->getBottomPoint();
		iPoint enemyPoint = getBottomPoint();
		result = playerPoint - enemyPoint;
	}
	//TODO: Random target to move enemy!
	return result;
}

void Enemy::OnCollision(const Collider &other) {
	switch (other.type) {
	case COLLIDER_TYPE::PLAYER_HIT:
		TakeDamage((Player*)other.owner);
		/*Player *playerCollides = (Player*)other.owner;
		++playerCollides->hits;
		life -= player->attack;
		if (life <= 0) {
			to_delete = true;
			positionCollider->to_delete = true;
		}*/
		LOG("ENEMY HAS BEEN HIT!");
		break;
	}
}

void Enemy::TakeDamage(Player *player) {
	LOG("ENEMY DAMAGED!!!");
	EnemyStateMachine *newState = state->ChangeTo(ENEMY_DAMAGED);
	if (newState != nullptr) {
		player->hits++;
		RELEASE(state);
		if (attackCollider != nullptr) {
			attackCollider->to_delete = true;
			attackCollider = nullptr;
		}
		state = newState;
		currentAnimation->Reset();
		state->Start(this);
		life -= player->attack;
		LOG("Current LIFE: %i", life);
		if (life <= 0)
			Kill();
	}
}

void Enemy::TakeDamage(int damage) {
	EnemyStateMachine *newState = state->ChangeTo(ENEMY_DAMAGED);
	if (newState != nullptr) {
		life -= player->attack;
		player->hits++;
		RELEASE(state);
		if (attackCollider != nullptr) {
			attackCollider->to_delete = true;
			attackCollider = nullptr;
		}
		state = newState;
		currentAnimation->Reset();
		state->Start(this);
	}
}

void Enemy::Kill() {
	EnemyStateMachine *newState = state->ChangeTo(ENEMY_DAMAGED);
	if (newState != nullptr) {
		RELEASE(state);
		if (attackCollider != nullptr) {
			attackCollider->to_delete = true;
			attackCollider = nullptr;
		}
		state = newState;
		currentAnimation->Reset();
		state->Start(this);
	}
}

void Enemy::Update() {
	previousPosition = iPoint(*position);
	speed.SetToZero();
	EnemyStateMachine *newState = state->Update(this);
	if (newState != nullptr) {
		RELEASE(state);
		if (attackCollider != nullptr) {
			attackCollider->to_delete = true;
			attackCollider = nullptr;
		}
		state = newState;
		currentAnimation->Reset();
		state->Start(this);
	}
	Move(speed);
}


