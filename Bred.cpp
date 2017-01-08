#include "Bred.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleInput.h"
#include "Player.h"
#include "EnemyStateMachine.h"


int Bred::number_of_instances = 0;

Bred::Bred(const JSON_Object *bredConfig) : Enemy(bredConfig, ENEMY_TYPE::BRED){
	const char* path = json_object_dotget_string(bredConfig, "graphics");
	graphics = App->textures->Load(path);
	JSON_Array *configAnimations = json_object_dotget_array(bredConfig, "animations");

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

		animations[key] = anim;
	}

	currentAnimation = animations["idle"];
	//state = new CodyIdleState();

	positionCollider = App->collision->AddCollider({ position->x, position->y, 37, 88 }, COLLIDER_TYPE::ENEMY_COLLIDER, false, false, std::bind(&Bred::OnCollision, this, std::placeholders::_1));
	//state->Start(this);
	++number_of_instances;
}

Bred::Bred(const Bred *other) : Enemy(other) {
	graphics = other->graphics;
	for (auto it = other->animations.begin(); it != other->animations.end(); ++it) {
		Animation *anim = new Animation((*it->second));
		animations[(it->first)] = anim;
	}
	currentAnimation = animations["idle"];
	position = new iPoint(*other->position);
	positionCollider = App->collision->AddCollider({ position->x, position->y, 37, 88 }, COLLIDER_TYPE::ENEMY_COLLIDER, false, false, std::bind(&Bred::OnCollision, this, std::placeholders::_1));
	++number_of_instances;
}


Bred::~Bred() {
	if (--number_of_instances > 0)
		graphics = nullptr;
	currentAnimation = nullptr;
}

void Bred::Update() {
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
	/*currentAnimation = animations["movement"];
	speed.SetToZero();
	targetPoint = iPoint{ player->positionCollider->rect.x + player->positionCollider->rect.w/2, player->positionCollider->rect.y + player->positionCollider->rect.h, 0};
	
	iPoint distanceVector = targetPoint - iPoint{ positionCollider->rect.x + positionCollider->rect.w / 2, positionCollider->rect.y + positionCollider->rect.h, 0 };

	if (distanceVector.x < 0) {
		flipped = true;
	}
	else {
		flipped = false;
	}

	srand(time(NULL));
	int number = rand() % 2 + 1;

	if (number == 1 && !distanceVector.IsZero()) {
		speed.x = distanceVector.x < 0 ? -baseSpeed : distanceVector.x > 0 ? baseSpeed : 0;
		speed.y = distanceVector.y < 0 ? -baseSpeed : distanceVector.y > 0 ? baseSpeed : 0;
	}
	else {
		currentAnimation = animations["idle"];
	}


	Move(speed);*/
}

void Bred::Init(const iPoint &initialPosition) {
	active = true;
	*position = initialPosition;
	positionCollider->SetPos(position->x + 40, position->y + 15, position->z);
}

void Bred::OnCollision(const Collider &other) {
	switch (other.type) {
	case COLLIDER_TYPE::PLAYER_HIT:
		Player *playerCollides = (Player*)other.owner;
		++playerCollides->hits;
		life -= player->attack;
		if (life <= 0) {
			to_delete = true;
			positionCollider->to_delete = true;
		}
		LOG("ENEMY HAS BEEN HIT!");
		break;
	}
}

void Bred::Move(const iPoint &movement) {
	*position += movement;
	positionCollider->AddPoint(movement);
}