#pragma once


#include"GameProject/GameManager/GameManager.h"
class GameScene
{
public:
	void Initialize();

	void Update();

	void Draw();

private:
	
	/// <summary>
	/// 
	/// </summary>
	GameManager* gameManager_;

	int time;
	///
	Skinning* skin;
	Bone* bone;
	LoadObjManagement* lod;

	unique_ptr<Animation3D> walk3d;
	Animation animatio;
	Skeleton skeleton;
	SkinCluster  skinCluster;
	CameraData* cameraData;
	//CameraData* cameraAnime;

	unique_ptr<SkyBox> sky;

	WorldTransform* worldTransform;
	WorldTransform* skyWorldTransform;
	float animaionTime;
	Vector3 cRot;
	Vector3 cPos;
};

