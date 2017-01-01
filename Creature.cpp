#include "Creature.h"
#include "SDL/include/SDL.h"

Creature::Creature(SDL_Texture* graphics) : Entity(ENTITY_TYPE::CREATURE, graphics) {
}


Creature::~Creature() {
}
