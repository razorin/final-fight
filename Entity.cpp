#include "Entity.h"
#include "Point.h"
#include "Globals.h"
#include <string.h>
#include "Animation.h"

Entity::Entity(ENTITY_TYPE type) : type(type) {
	position = new iPoint(0, 0, 0);

}


Entity::~Entity() {
	RELEASE(position);
	RELEASE(graphics);
	
	for (auto it = animations.begin(); it != animations.end(); ++it) {
		RELEASE(it->second);
	}
	animations.clear();

	entities.clear();
}

void Entity::Update() {
	LOG("Updating entity");
}

SDL_Texture* Entity::getGraphics() const {
	return graphics;
}


Frame & Entity::getCurrentFrame() const {
	return currentAnimation->GetCurrentFrame();
}

void Entity::setCurrentAnimation(Animation *animation) {
	this->currentAnimation = animation;
}

Animation * Entity::getCurrentAnimation() const {
	return currentAnimation;
}