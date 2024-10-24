#include "Bone.h"

Skeleton Bone::CreateSkeleton(const Node& rootNode)
{
	Skeleton skeleton;
	skeleton.root = CreateJoint(rootNode, {}, skeleton.joints);

	for (const Joint& joint : skeleton.joints) {
		skeleton.jointMap.emplace(joint.name, joint.index);
	}

	return skeleton;
}
int32_t Bone::CreateJoint(const Node& node, const optional<int32_t>& parent, vector<Joint>& joints)
{
	Joint joint;

	joint.name = node.name;
	joint.localMatrix = node.localMatrix;
	joint.skeletonSpaceMatrix = MakeIdentity4x4();
	joint.transform = node.transform;
	joint.index = int32_t(joints.size());
	joint.parent = parent;
	joints.push_back(joint);
	for (const Node& child : node.chidren) {
		int32_t childIndex = CreateJoint(child, joint.index, joints);
		joints[joint.index].children.push_back(childIndex);
	}

	return joint.index;
}
void Bone::Update(Skeleton& skeleton)
{
	skeleton.joints;
	for (Joint& joint : skeleton.joints) {

		Vector3 scale = joint.transform.scale;
		Quaternion rotate = joint.transform.rotate;
		Vector3 translate = joint.transform.tranalte;

		Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
		Matrix4x4 rotateMatrix = MakeRotateMatrix(rotate);
		Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

		joint.localMatrix = Multiply(scaleMatrix, Multiply(rotateMatrix, translateMatrix));
		if (joint.parent) {

			Matrix4x4 localMatrix = joint.localMatrix;
			Matrix4x4 spaceMatrix = skeleton.joints[*joint.parent].skeletonSpaceMatrix;
			joint.skeletonSpaceMatrix = Multiply(joint.localMatrix, skeleton.joints[*joint.parent].skeletonSpaceMatrix);
		}
		else {
			joint.skeletonSpaceMatrix = joint.localMatrix;

		}

		Matrix4x4 skeletonSpace1 = skeleton.joints[0].skeletonSpaceMatrix;
		Matrix4x4 skeletonSpace2 = skeleton.joints[1].skeletonSpaceMatrix;
		Matrix4x4 skeletonSpace3 = skeleton.joints[2].skeletonSpaceMatrix;
		Matrix4x4 skeletonSpace4 = skeleton.joints[3].skeletonSpaceMatrix;

	}
	skeleton.joints;



}

void Bone::ApplyAnimation(Skeleton& skeleton, const Animation& animation, float animatiionTime)
{


	skeleton;
	animation;

	for (Joint& joint : skeleton.joints) {
		if (auto it = animation.nodeAnimations.find(joint.name); it != animation.nodeAnimations.end()) {
			animatiionTime = std::fmod(animatiionTime, animation.duration);
			const NodeAnimation& rootNodeAnimation = (*it).second;
			joint.transform.tranalte = LoadObjManagement::Calculatevalue(rootNodeAnimation.translate.keyframes, animatiionTime);
			joint.transform.rotate = LoadObjManagement::QCalculatevalue(rootNodeAnimation.rotate.keyframes, animatiionTime);
			joint.transform.scale = LoadObjManagement::Calculatevalue(rootNodeAnimation.scale.keyframes, animatiionTime);

		}
	}

}