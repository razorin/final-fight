#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include<list>
#include "Module.h"
#include <functional>

// TODO 9: Create a matrix of game specific types of collision for early discard
// Example: lasers should not collide with lasers but should collider with walls
// enemy shots will collide with other enemies ? and against walls ?

/*class CollisionEvent {
public:
	void virtual OnCollision(COLLIDER_TYPE type) {

	}
};*/


struct Collider
{
	SDL_Rect rect = { 0,0,0,0 };
	bool to_delete = false;
	COLLIDER_TYPE type;
	std::function<void(COLLIDER_TYPE)> onCollision;

	// TODO 10: Add a way to notify other classes that a collision happened

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, std::function<void(COLLIDER_TYPE)> onCollision) : // expand this call if you need to
		rect(rectangle), type(type), onCollision(onCollision)
	{

	}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;

	void Notify(COLLIDER_TYPE type);
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

	Collider* AddCollider(const SDL_Rect& rect, COLLIDER_TYPE type = COLLIDER_TYPE::NONE, std::function<void(COLLIDER_TYPE)> onCollision = nullptr);
	void DebugDraw();

private:
	bool *matrix_collision;
	std::list<Collider*> colliders;
	bool debug = false;
};

#endif // __ModuleCollision_H__