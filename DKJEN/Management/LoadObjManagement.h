#pragma once
#include"../Type/Obj3D.h"
#include"../Skinning/Animation/Animation.h"
#include"../Utilipy/Pch.h"



class LoadObjManagement
{
public:
      static LoadObjManagement* GetInstance();
      static ModelData NewLoadObjFile(const std::string& directoryPath, const std::string& filename);
     
      static MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);
     
      static Node ReadNode(aiNode* node);
	/*static Animation LoadAnimationFile(const std::string& directoryPath, const std::string& filename);
	static Vector3 Calculatevalue(const std::vector<KeyframeVector3>& keyframes, float time);
	static Quaternion QCalculatevalue(const std::vector<KeyframeQuaternion>& keyframes, float time);*/

private:
	uint32_t tex_;
};
