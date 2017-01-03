#include "Player.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModuleRender.h"
#include "Animation.h"
#include "ModuleInput.h"
#include "Globals.h"
#include "ModuleCollision.h"


Player::Player(SDL_Texture* graphics) : Creature(graphics){
	
	idle = new Animation();
	idle->frames.push_back(Frame({0, 0, 107, 107}));
	idle->loop = false;

	movement = new Animation();

	movement->frames.push_back(Frame({ 107, 0, 107, 107}));
	movement->frames.push_back(Frame({ 214, 0, 107, 107}));
	movement->frames.push_back(Frame({ 321, 0, 107, 107}));
	movement->frames.push_back(Frame({ 428, 0, 107, 107}));
	movement->frames.push_back(Frame({ 535, 0, 107, 107}));
	movement->frames.push_back(Frame({ 642, 0, 107, 107}));
	movement->loop = true;
	movement->speed = .1f;

	attack1 = new Animation();
	attack1->frames.push_back(Frame({ 0, 107, 107, 107}, 0, 2));
	attack1->frames.push_back(Frame({ 107, 107, 107, 107 }, 13, 2));
	attack1->loop = true;
	attack1->speed = .1f;

	currentAnimation = idle;

	positionCollider = App->collision->AddCollider({position->x, position->y, 37, 88}, position->z, COLLIDER_PLAYER, false, std::bind(&Player::OnCollision, this, std::placeholders::_1));
}


Player::~Player() {
	currentAnimation = nullptr;
	RELEASE(idle);
	RELEASE(movement);
	RELEASE(jump);
	RELEASE(attack1);
}


void Player::Update() {
	iPoint speed;
	previousPosition = *position;
	int baseSpeed = 1;
	speed.SetToZero();
	if (is_attacking == false) {
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			speed.x -= baseSpeed;
			currentAnimation = movement;
			flipped = true;
		}
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			speed.x += baseSpeed;
			currentAnimation = movement;
			flipped = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			speed.z += baseSpeed;
			speed.y += baseSpeed;
			currentAnimation = movement;
		}
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			speed.z -= baseSpeed;
			speed.y -= baseSpeed;
			currentAnimation = movement;
		}

		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) {
			LOG("Attacking");
			is_attacking = true;
			//attack1->Reset();
			currentAnimation = attack1;
		}
		
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE &&
			App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE &&
			App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE &&
			App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE &&
			App->input->GetKey(SDL_SCANCODE_E) == KEY_IDLE) {

			movement->Reset();
			currentAnimation = idle;
		}
	} else if(is_attacking == true){
		if (currentAnimation->Finished()){
			LOG("Attack ending!!");
			attack1->Reset();
			is_attacking = false;
			currentAnimation = idle;
		}
	}

		
	Move(speed);
	//section = &currentAnimation->GetCurrentFrame();
}

void Player::OnCollision(COLLIDER_TYPE type) {
	switch (type) {
	case COLLIDER_TYPE::WALL:
		LOG("COLLISION WITH WALL!!!");
		*position = previousPosition;
		break;
	}
}

void Player::Move(const iPoint &movement) {
	*position += movement;
	positionCollider->SetPos(position->x + 35, position->y + 9, position->z);
}