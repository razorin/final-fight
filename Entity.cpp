#include "Entity.h"
#include "Point.h"
#include "Globals.h"
#include <string.h>
#include "Animation.h"
#include <assert.h>
#include "ModuleCollision.h"

Entity::Entity(ENTITY_TYPE type) : type(type) {
	position = new iPoint(0, 0, 0);

}


Entity::~Entity() {
	RELEASE(position);
	graphics = nullptr;
	
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

void Entity::setCurrentAnimation(const std::string &animation) {
	map<std::string, Animation*>::iterator anim = animations.find(animation);
	assert(animations.find(animation) != animations.end());
	this->currentAnimation = anim->second;
}

Animation * Entity::getCurrentAnimation() const {
	return currentAnimation;
}

iPoint &Entity::getBottomPoint() const {
	if (positionCollider == nullptr)
		return iPoint{ 0,0,0 };
	return iPoint{ positionCollider->rect.x + positionCollider->rect.w / 2,
		positionCollider->rect.y + positionCollider->rect.h, 0 };
}