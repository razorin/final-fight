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

Player::Player() : Creature(ENTITY_TYPE::PLAYER){
	
	JSON_Object *root = json_value_get_object(App->configuration);
	JSON_Object *playerConfig = json_object_dotget_object(root, "config.entities.player");
	JSON_Array *configAnimations = json_object_dotget_array(playerConfig, "animations");
	const char* path = json_object_dotget_string(playerConfig, "graphics");
	graphics =  App->textures->Load(path);

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

	currentAnimation = animations["idle"];

	positionCollider = App->collision->AddCollider({position->x, position->y, 37, 88}, position->z, COLLIDER_PLAYER, false, false, std::bind(&Player::OnCollision, this, std::placeholders::_1));
	timer = new Timer();
}

void Player::Init(const iPoint &initialPosition) {
	*position = initialPosition;
	positionCollider->SetPos(position->x + 35, position->y + 9, position->z);
}

Player::~Player() {
	currentAnimation = nullptr;
	for (auto it = animations.begin(); it != animations.end(); ++it) {
		RELEASE(it->second);
	}
	animations.clear();
	RELEASE(timer);
}


void Player::Update() {
	iPoint speed;
	previousPosition = iPoint(*position);
	int baseSpeed = 1;
	speed.SetToZero();
	if (is_attacking == false && is_jumping == false) {
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			speed.x -= baseSpeed;
			currentAnimation = animations["movement"];
			flipped = true;
		}
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			speed.x += baseSpeed;
			currentAnimation = animations["movement"];
			flipped = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			//speed.z += baseSpeed;
			speed.y += baseSpeed;
			currentAnimation = animations["movement"];
		}
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			//speed.z -= baseSpeed;
			speed.y -= baseSpeed;
			currentAnimation = animations["movement"];
		}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			is_jumping = true;
			speed.z -= baseSpeed;
			currentAnimation = animations["idle"];
			timer->Start();
		}
		if (App->input->GetKey(SDL_SCANCODE_C) == KEY_REPEAT) {
			speed.z -= baseSpeed;
			currentAnimation = animations["idle"];
		}

		if (App->input->GetKey(SDL_SCANCODE_V) == KEY_REPEAT) {
			speed.z += baseSpeed;
			currentAnimation = animations["idle"];
		}


		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) {
			LOG("Attacking");
			is_attacking = true;
			//attack1->Reset();
			currentAnimation = animations["attack1"];
		}

		
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE &&
			App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE &&
			App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE &&
			App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE &&
			App->input->GetKey(SDL_SCANCODE_E) == KEY_IDLE) {

			animations["movement"]->Reset();
			currentAnimation = animations["idle"];
		}
	} else if(is_attacking == true){
		if (currentAnimation->Finished()){
			LOG("Attack ending!!");
			animations["attack1"]->Reset();
			is_attacking = false;
			currentAnimation = animations["idle"];
		}
	}
	else if (is_jumping == true) {
		if (is_falling) {
			if (position->z >= 0) {
				is_jumping = false;
				is_falling = false;
			} else{
				speed.z += baseSpeed;
			}
		}
		else if (position->z > -10) {
			speed.z -= baseSpeed;
		}
		else if (position->z <= -10) {
			is_falling = true;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		LOG("Player Previous Position: %i,%i,%i (x, y, z)", previousPosition.x, previousPosition.y, previousPosition.z);
		LOG("Player Position: %i,%i,%i (x, y, z)", position->x, position->y, position->z);
		LOG("Player Collider: %i,%i,%i,%i,%i (x, w, y, h, z)", positionCollider->rect.x, positionCollider->rect.w, positionCollider->rect.y, positionCollider->rect.h, positionCollider->z);
	}

	Move(speed);
	//section = &currentAnimation->GetCurrentFrame();
}

void Player::OnCollision(const Collider &other) {
	switch (other.type) {
	case COLLIDER_TYPE::WALL:
		//LOG("COLLISION WITH WALL!!!");
		//LOG("PREVIOUS POSITION: %i,%i,%i (x, y, z)", previousPosition.x, previousPosition.y, previousPosition.z);
		//LOG("Position BEFORE WALL COLLISION: %i,%i,%i (x, y, z)", position->x, position->y, position->z);
		Move(previousPosition- *position);
		//*position = previousPosition;
		//LOG("Position AFTER WALL COLLISION: %i,%i,%i (x, y, z)", position->x, position->y, position->z);
		//Move(iPoint(0, 0, 0));
		break;
	}
}

void Player::Move(const iPoint &movement) {
	*position += movement;
	positionCollider->AddPoint(movement);
	//positionCollider->SetPos(position->x + 35, position->y + 9, position->z + 9);
	/*if (is_jumping) {
		LOG("Movement jumping: %i,%i,%i (x, y, z)", movement.x, movement.y, movement.z);
		LOG("Position jumping: %i,%i,%i (x, y, z)", position->x, position->y, position->z);
		LOG("Collider jumping: %i,%i,%i (x, y, z)", positionCollider->rect.x, positionCollider->rect.y, positionCollider->z);
	}*/
}