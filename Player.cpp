#include "Player.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModuleRender.h"
#include "Animation.h"
#include "ModuleInput.h"
#include "Globals.h"
#include "ModuleCollision.h"
#include "Parson.h"
#include "ModuleTextures.h"
#include "Timer.h"
#include "CodyIdleState.h"
#include "Enemy.h"

Player::Player(const JSON_Object *playerConfig) : Creature(playerConfig, ENTITY_TYPE::PLAYER){
	const char* path = json_object_dotget_string(playerConfig, "graphics");
	graphics =  App->textures->Load(path);
	JSON_Array *configAnimations = json_object_dotget_array(playerConfig, "animations");

	for (int i = 0; i < json_array_get_count(configAnimations); ++i) {
		JSON_Object *configAnimation = json_array_get_object(configAnimations, i);
		std::string key = json_object_dotget_string(configAnimation, "name");
		
		Animation *anim = new Animation();
		anim->loop = json_object_dotget_boolean(configAnimation, "loop");
		anim->speed = json_object_dotget_number(configAnimation, "speed");
		
		JSON_Array *configFrames = json_object_dotget_array(configAnimation, "frames");

		for (int j = 0; j < json_array_get_count(configFrames); ++j) {
			JSON_Object *configFrame = json_array_get_object(configFrames, j);
			anim->frames.push_back(Frame({ (int)json_object_dotget_number(configFrame, "x"), (int)json_object_dotget_number(configFrame, "y"),
				(int)json_object_dotget_number(configFrame, "width"), (int)json_object_dotget_number(configFrame, "height") },
				(int)json_object_dotget_number(configFrame, "offset_x"), (int)json_object_dotget_number(configFrame, "offset_y")));
		}

		animations[key] =  anim;
	}

	//currentAnimation = animations["idle"];
	state = new CodyIdleState();

	positionCollider = App->collision->AddCollider({position->x, position->y, 37, 88}, PLAYER_COLLIDER, false, false, std::bind(&Player::OnCollision, this, std::placeholders::_1));
	state->Start(this);
	
}

void Player::Init(const iPoint &initialPosition) {
	active = true;
	*position = initialPosition;
	positionCollider->SetPos(position->x + 35, position->y + 9, position->z);
	attack = 50;
}

Player::~Player() {
	currentAnimation = nullptr;
}


void Player::Update() {
	previousPosition = iPoint(*position);
	speed.SetToZero();
	PlayerStateMachine *newState = state->Update(this);
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
	if (hits > 3)
		hits = 0;
	Move(speed);
}

void Player::OnCollision(const Collider &other) {
	iPoint newPosition = previousPosition - *position;
	switch (other.type) {
	case COLLIDER_TYPE::WALL:
	case COLLIDER_TYPE::CAMERA_WALL:
		if (previousPosition.x != position->x &&
			positionCollider->rect.x > other.rect.x && positionCollider->rect.x < other.rect.x + other.rect.w) {
			newPosition.x = 0;
		}
		//TODO: Now it's a little tricky. It needs a good revision to fix wall collisions
		if (previousPosition.y != position->y && other.ignore_y) {
			newPosition.y = 0;
		}
		newPosition.z = 0;
		Move(newPosition);
		break;
	case COLLIDER_TYPE::ENEMY_HIT:
		TakeDamage((Enemy*)other.owner);
		break;
	}
}

void Player::TakeDamage(Enemy *enemy) {
	if (state != nullptr) {
		PlayerStateMachine *newState = state->ChangeState(PLAYER_DAMAGE_STATE);
		if (newState != nullptr) {
			RELEASE(state);
			if (attackCollider != nullptr) {
				attackCollider->to_delete = true;
				attackCollider = nullptr;
			}
			state = newState;
			currentAnimation->Reset();
			state->Start(this);
			LOG("LIFE BEFORE: %i", life);
			life -= enemy->attack;
			LOG("LIFE AFETER: %i", life);
			//if (life <= 0)
				//Kill();
				
		}
	}
}

void Player::Kill() {
	LOG("KILLING!");
	if (state != nullptr) {
		PlayerStateMachine *newState = state->ChangeState(PLAYER_KILLED_STATE);
		if (newState != nullptr) {
			//--lives;
			//life = max_life;
			if (lives <= 0) {
				RELEASE(state);
				if (attackCollider != nullptr) {
					attackCollider->to_delete = true;
					attackCollider = nullptr;
				}
			}
			state = newState;
			currentAnimation->Reset();
			state->Start(this);
		}
	}
}