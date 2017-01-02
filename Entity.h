#ifndef ENTITY_H
#define ENTITY_H

#include <list>

template <class TYPE> class Point;
typedef Point<int> iPoint;

struct SDL_Texture;
struct SDL_Rect;
struct Collider;

enum ENTITY_TYPE {
	PLAYER,
	CREATURE,
	UNKNOWN
};

class Entity {
public:
	Entity(ENTITY_TYPE type, SDL_Texture* graphics);
	virtual ~Entity();
	virtual void Update();
	SDL_Texture* getGraphics() const;
	SDL_Rect * getSection() const;


public:
	std::list<Entity *> entities;
	Collider* positionCollider = nullptr;
	bool to_delete = false;
	ENTITY_TYPE type;
	iPoint* position = nullptr;
	bool flipped = false;

protected:
	SDL_Texture* graphics = nullptr;
	SDL_Rect *section = nullptr;

};

#endif // !ENTITY_H

