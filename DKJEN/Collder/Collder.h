#pragma once
#include<format>
#include"DKJEN/Math/Math.h"
class Collider {
public:
	// セッター
	void steRadius(float radius) { radius_ = radius; }
	void steCollisionAttribute(uint32_t CollisionAttribute) {CollisionAttribute_ = CollisionAttribute;}
	void steCollisionMask(uint32_t CollisionMask) { CollisionMask_ = CollisionMask; }
	// ゲッター
	float GetRadius() { return radius_; }
	virtual void OnCollision() = 0;
	virtual Vector3 GetWorldPosition() = 0;
	uint32_t GetCollisionAttribute() { return CollisionAttribute_; }
	uint32_t GetCollisionMask() { return CollisionMask_; }

private:
	float radius_ = 1.0f;
	uint32_t CollisionAttribute_ = 0xffffffff;
	uint32_t CollisionMask_ = 0xffffffff;
};
