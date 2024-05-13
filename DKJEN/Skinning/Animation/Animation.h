#pragma once
#include"../../Utilipy/Pch.h"
template<typename tValue>
struct Keyframe {
	float time;
	tValue value;
};
using KeyframeVector3 = Keyframe<Vector3>;
using KeyframeQuaternion = Keyframe<Quaternion>;
template<typename tValue>
struct AnimationCurve
{
	std::vector<Keyframe<tValue>> keyframes;
};
struct NodeAnimation
{
	AnimationCurve<Vector3> translate;
	AnimationCurve<Quaternion> rotate;
	AnimationCurve<Vector3> scale;
};
struct Animation
{
	float duration;
	std::map<std::string, NodeAnimation>nodeAnimations;
};