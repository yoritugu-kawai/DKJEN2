#include "CollisionManager.h"

void CollisionManager::CheckAllCollisions() {
	std::list<Collider*>::iterator itrA = Colliders_.begin();
	for (; itrA != Colliders_.end(); ++itrA) {
		Collider* colliderA = *itrA;
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != Colliders_.end(); ++itrB) {
			Collider* colliderB = *itrB;
			ChekCollisionPair(colliderA, colliderB);
		}
	}
}

void CollisionManager::ColliderPush(Collider*collider) { 
	Colliders_.push_back(collider);

}

void CollisionManager::CollideClear() {
	Colliders_.clear();
}

void CollisionManager::ChekCollisionPair(Collider* cA, Collider* cB) {
	if ((cA->GetCollisionAttribute() & cB->GetCollisionMask()) == 0 ||
	    (cB->GetCollisionAttribute() & cA->GetCollisionMask()) == 0) {
		return;
	}
	Vector3 coA, coB;

	coA = cA->GetWorldPosition();
	coB = cB->GetWorldPosition();
	float coAR, coBR;
	coAR = cA->GetRadius();
	coBR = cB->GetRadius();
	if (CheckBallCollosion(coA, coAR, coB, coBR)) {
		cA->OnCollision();
		cB->OnCollision();
	}
}

bool CollisionManager::CheckBallCollosion(
    Vector3 v1, float v1Radious, Vector3 v2, float v2Radious) {
	float x = (v2.x - v1.x);

	float y = (v2.y - v1.y);
	float z = (v2.z - v1.z);

	float resultPos = (x * x) + (y * y) + (z * z);

	float resultRadious = v1Radious + v2Radious;

	bool Flag = false;

	if (resultPos <= (resultRadious * resultRadious)) {
		Flag = true;
	}

	return Flag;
}
