#include "Player.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModuleRender.h"
#include "Animation.h"
#include "ModuleInput.h"


Player::Player(SDL_Texture* graphics) : Creature(graphics){
	
	idle = new Animation();
	idle->frames.push_back(Frame({10, 20, 37, 88}));
	idle->loop = false;

	movement = new Animation();

	movement->frames.push_back(Frame({ 54, 17, 22, 88 }));
	movement->frames.push_back(Frame({ 85, 16, 45, 87 }));
	movement->frames.push_back(Frame({ 137, 15, 35, 86 }));
	movement->frames.push_back(Frame({ 180, 22, 23, 86 }));
	movement->frames.push_back(Frame({ 212, 20, 45, 86 }));
	movement->frames.push_back(Frame({ 265, 19, 35, 87 }));
	movement->loop = true;
	movement->speed = .1f;

	attack1 = new Animation();
	attack1->frames.push_back(Frame({ 120, 230, 43, 85 }, 0));
	attack1->frames.push_back(Frame({ 175, 231, 60, 85 }, -17));
	attack1->loop = true;
	attack1->speed = .1f;

	currentAnimation = idle;
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
	speed.SetToZero();
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		speed.x -= 1;
		currentAnimation = movement;
		flipped = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		speed.x += 1;
		currentAnimation = movement;
		flipped = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		speed.z += 1;
		currentAnimation = movement;
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		speed.z -= 1;
		currentAnimation = movement;
	}

	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) {
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

		
	*position += speed;
	//section = &currentAnimation->GetCurrentFrame();
}

