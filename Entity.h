#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include <map>

template <class TYPE> class Point;
typedef Point<int> iPoint;

struct SDL_Texture;
struct SDL_Rect;
struct Collider;
struct Frame;
class Animation;

enum ENTITY_TYPE {
	PLAYER,
	CREATURE,
	UNKNOWN
};

class Entity {
public:
	Entity(ENTITY_TYPE type);
	virtual ~Entity();
	virtual void Update();
	SDL_Texture* getGraphics() const;
	Frame & getCurrentFrame() const;


public:
	std::list<Entity *> entities;
	Collider* positionCollider = nullptr;
	bool to_delete = false;
	ENTITY_TYPE type;
	iPoint* position = nullptr;
	bool flipped = false;

protected:
	SDL_Texture* graphics = nullptr;
	//SDL_Rect *section = nullptr;
	Animation *currentAnimation = nullptr;
	std::map<std::string, Animation*> animations;
};

#endif // !ENTITY_H

