#pragma once
#include"Animation.h"
#include"../../Utilipy/SkinCluster.h"
#include"../../Utilipy/AdditionInclude.h"
#include"../../Management/LoadObjManagement.h"

class Bone
{
public:
	Skeleton CreateSkeleton(const Node& rootNode);
	int32_t CreateJoint(const Node& node, const optional<int32_t>& parent, vector<Joint>& joints);
	void Update(Skeleton& skeleton);
	void ApplyAnimation(Skeleton& skeleton, const Animation& animation, float animatiionTime);
private:

};
