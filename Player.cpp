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

Player::Player(const JSON_Object *playerConfig) : Creature(ENTITY_TYPE::PLAYER){
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

	positionCollider = App->collision->AddCollider({position->x, position->y, 37, 88}, COLLIDER_PLAYER, false, false, std::bind(&Player::OnCollision, this, std::placeholders::_1));
	state->Start(this);
	
}

void Player::Init(const iPoint &initialPosition) {
	*position = initialPosition;
	positionCollider->SetPos(position->x + 35, position->y + 9, position->z);
}

Player::~Player() {
	currentAnimation = nullptr;
}


void Player::Update() {
	previousPosition = iPoint(*position);
	PlayerStateMachine *newState = state->Update(this);
	if (newState != nullptr) {
		RELEASE(state);
		state = newState;
		currentAnimation->Reset();
		state->Start(this);
	}
}

void Player::OnCollision(const Collider &other) {
	switch (other.type) {
	case COLLIDER_TYPE::WALL:
	case COLLIDER_TYPE::CAMERA_WALL:
		
		Move(previousPosition- *position);
		break;
	}
}

void Player::Move(const iPoint &movement) {
	*position += movement;
	positionCollider->AddPoint(movement);
}