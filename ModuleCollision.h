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
	int z = 0;
	bool ignore_z = false;
	COLLIDER_TYPE type;
	std::function<void(COLLIDER_TYPE)> onCollision;

	// TODO 10: Add a way to notify other classes that a collision happened

	Collider(SDL_Rect rectangle, int z, COLLIDER_TYPE type, bool ignore_z, std::function<void(COLLIDER_TYPE)> onCollision) : // expand this call if you need to
		rect(rectangle), z(z), type(type), ignore_z(ignore_z), onCollision(onCollision)
	{

	}

	void SetPos(int x, int y, int z)
	{
		rect.x = x;
		rect.y = y;
		this->z = z;
	}

	bool CheckCollision(const SDL_Rect& r, int z, bool ignore_z = false) const;

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

	Collider* AddCollider(const SDL_Rect& rect, int z, COLLIDER_TYPE type = COLLIDER_TYPE::NONE, bool ignore_z = false, std::function<void(COLLIDER_TYPE)> onCollision = nullptr);
	void DebugDraw();

private:
	bool *matrix_collision;
	std::list<Collider*> colliders;
	bool debug = false;
};

#endif // __ModuleCollision_H__