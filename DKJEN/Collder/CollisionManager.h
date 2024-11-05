#pragma once
#include"Collder.h"
#include <list>
class CollisionManager {
public:
	void CheckAllCollisions();
	void ColliderPush(Collider* collider);
	void CollideClear();

private:
	void ChekCollisionPair(Collider* cA, Collider* cB);
	bool CheckBallCollosion(Vector3 V1, float v1radius, Vector3 V2, float v2rad);

	std::list<Collider*> Colliders_;
};
