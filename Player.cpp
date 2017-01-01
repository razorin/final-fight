#include "Player.h"
#include "SDL/include/SDL.h"


Player::Player(SDL_Texture* graphics) : Creature(graphics){
	section = new SDL_Rect();
	section->x = 10;
	section->y = 20;
	section->w = 37;
	section->h = 88;
}


Player::~Player() {
}


void Player::Update() {

}