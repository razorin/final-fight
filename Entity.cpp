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
	RELEASE(positionCollider);
	entities.clear();
}

void Entity::Update() {
	LOG("Updating entity");
}

SDL_Texture* Entity::getGraphics() const {
	return graphics;
}

SDL_Rect * Entity::getSection() const {
	return section;
}

Frame & Entity::getCurrentFrame() const {
	return currentAnimation->GetCurrentFrame();
}