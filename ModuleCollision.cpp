#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

using namespace std;

ModuleCollision::ModuleCollision()
{
	matrix_collision = new bool[36]{false, false, false, false, false, false,
									false, false, false, true, true, true,
									false, false, false, true, false, true,
									false, true, true, false, false, false,
									false, true, false, false, false, false,
									false, true, true, false, false, false };
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		if ((*it)->to_delete == true)
		{
			RELEASE(*it);
			it = colliders.erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollision::Update()
{
	// TODO 8: Check collisions between all colliders. 
	// After making it work, review that you are doing the minumum checks possible
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it){
		for (list<Collider*>::iterator jt = std::next(it); jt != colliders.end(); ++jt) {
			if (matrix_collision[(*it)->type * 6 + (*jt)->type] && (*it)->CheckCollision((*jt)->rect)) {
				(*it)->Notify((*jt)->type);
				(*jt)->Notify((*it)->type);
			}
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(debug == true)
		DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		App->renderer->DrawQuad((*it)->rect, 255, 0, 0, 80);
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		RELEASE(*it);

	colliders.clear();

	return true;
}

Collider* ModuleCollision::AddCollider(const SDL_Rect& rect, COLLIDER_TYPE type, std::function<void(COLLIDER_TYPE)> onCollision)
{
	Collider* ret = new Collider(rect, type, onCollision);

	colliders.push_back(ret);

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	// TODO 7: Create by hand (avoid consulting the internet) a simple collision test
	// Return true if the argument and the own rectangle are intersecting
	return (this->rect.x < r.x + r.w &&
			this->rect.x + this->rect.w > r.x &&
			this->rect.y < r.y + r.h &&
			this->rect.h + this->rect.y > r.y);
}

void Collider::Notify(COLLIDER_TYPE type) {
	if (onCollision)
		onCollision(type);
}