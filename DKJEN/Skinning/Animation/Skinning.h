#pragma once
#include"Animation.h"
#include"DKJEN/Utilipy/Sc.h"
#include"../../Utilipy/Pch.h"
#include"../../Management/LoadObjManagement.h"

class Skinning
{
public:
	SkinCluster CreateSkinCluster(const Skeleton& skeleton, const ModelData& modelData);
	void SkinUpdate(SkinCluster& skinCluster, const Skeleton& skeleton);
private:

};
