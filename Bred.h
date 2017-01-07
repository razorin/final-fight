#ifndef BRED_H
#define BRED_H

#include "Enemy.h"
#include "Point.h"

class Bred : public Enemy {
public:
	Bred(const JSON_Object *bredConfig);
	Bred(const Bred *other);
	~Bred();
	void Update();
	void OnCollision(const Collider &other);
	void Move(const iPoint &movement);
	void Init(const iPoint &initialPosition);
private:
	static int number_of_instances;
	iPoint targetPoint{ 0,0,0 };

};

#endif // !BRED_H
