#include "clearScene.h"
/// <summary>
/// 
/// 
/// 全変更保留
/// 
/// 
/// 
/// </summary>
void clearScene::Initialize()
{
	uint32_t tex = TexManager::LoadTexture("GameResource/clear/scol.png");
	sprite = new Sprite;
	sprite->Initialize(tex);

	//プレイヤー
	cameraData = new CameraData;
	cameraData->Create();
	cameraData->Update();
	cameraData->SetRotate({ 0,0,0 });
	cameraData->SetTranslate({ 0,18,-20 });
	cPos = { 0,4,-21 };
	speed = 0.01f;
	playerPos_ = { 0.2f,-4.5f,-12 };
	playerPos2_ = { 0.2f,-4.5f,-12 };
	playerPos3_ = { 0.2f,-4.5f,-12 };
	playerRot = { 0,3.1f,0 };
	//
	worldTransform = new WorldTransform;
	worldTransform->Create();
	worldTransform->SetScale({ 1.0f,1,1 });
	walk3d = make_unique<Animation3D>();
	ModelData modelData_ = LoadObjManagement::NewLoadObjFile("resource/hu", "Run.gltf");
	walk3d->Initialize(modelData_);
	//
	worldTransform2 = new WorldTransform;
	worldTransform2->Create();
	worldTransform2->SetScale({ 1.0f,1,1 });
	walk3d2 = make_unique<Animation3D>();
	walk3d2->Initialize(modelData_);
	///
	worldTransform3 = new WorldTransform;
	worldTransform3->Create();
	worldTransform3->SetScale({ 1.0f,1,1 });
	walk3d3 = make_unique<Animation3D>();
	walk3d3->Initialize(modelData_);
	//ジャンプ
	animatio = lod->LoadAnimationFile("GameResource/clear", "Jump.gltf");
	skeleton = bone->CreateSkeleton(modelData_.rootNode);
	skinCluster = skin->CreateSkinCluster(skeleton, modelData_);

	//あほうどうり
	animatioSilly = lodSilly->LoadAnimationFile("GameResource/clear", "Silly.gltf");
	skeletonSilly = boneSilly->CreateSkeleton(modelData_.rootNode);
	skinClusterSilly = skinSilly->CreateSkinCluster(skeletonSilly, modelData_);

	//HipHop
	animatioHipHop = lodHipHop->LoadAnimationFile("GameResource/clear", "HipHop.gltf");
	skeletonHipHop = boneHipHop->CreateSkeleton(modelData_.rootNode);
	skinClusterHipHop = skinHipHop->CreateSkinCluster(skeletonHipHop, modelData_);

	//Rumba
	animatioRumba = lodRumba->LoadAnimationFile("GameResource/clear", "Rumba.gltf");
	skeletonRumba = boneRumba->CreateSkeleton(modelData_.rootNode);
	skinClusterRumba = skinRumba->CreateSkinCluster(skeletonRumba, modelData_);



	///


	treeData_ = std::make_unique<Obj3D>();
	ModelData treeModel_ = LoadObjManagement::NewLoadObjFile("GameResource/clear", "Green.obj");
	treeData_->Initialize(treeModel_);
	treeWorldTransform_ = new WorldTransform();
	treeWorldTransform_->Create();
	treeSize = { 0.1f,0.1f,0.1f };
	treePos = { -5.0f,-1.5f,14.0f };

	color = { 1,1,1,1 };
}

void clearScene::Update(GameManager* gameManager)
{
	animaionTime += 1.0f / 40.0f;
	cameraData->Update();


	treeWorldTransform_->UpdateMatrix(cameraData);


	////Animation
	bone->ApplyAnimation(skeleton, animatio, animaionTime);
	//Skeleton

	bone->Update(skeleton);
	//SkinCluster

	skin->SkinUpdate(skinCluster, skeleton);

	///馬鹿な踊り
	////Animation
	boneSilly->ApplyAnimation(skeletonSilly, animatioSilly, animaionTime);
	//Skeleton

	boneSilly->Update(skeletonSilly);
	//SkinCluster

	skinSilly->SkinUpdate(skinClusterSilly, skeletonSilly);

	///HipHop
	////Animation
	boneHipHop->ApplyAnimation(skeletonHipHop, animatioHipHop, animaionTime);
	//Skeleton

	boneHipHop->Update(skeletonHipHop);
	//SkinCluster

	skinHipHop->SkinUpdate(skinClusterHipHop, skeletonHipHop);


	///Rumba
	////Animation
	boneRumba->ApplyAnimation(skeletonRumba, animatioRumba, animaionTime);
	//Skeleton

	boneRumba->Update(skeletonRumba);
	//SkinCluster

	skinRumba->SkinUpdate(skinClusterRumba, skeletonRumba);
	///
	if (animaionTime >= 2.0) {
		playerPos2_.x += speed;
		playerPos3_.x -= speed;
	}
	if (animaionTime >= 6.8) {
		speed = 0;
	}
	worldTransform->SetTranslate(playerPos_);
	worldTransform2->SetTranslate(playerPos2_);
	worldTransform3->SetTranslate(playerPos3_);
	worldTransform->SetRotate(playerRot);
	worldTransform2->SetRotate(playerRot);
	worldTransform3->SetRotate(playerRot);
	cameraData->SetTranslate(cPos);

	color.w -= 0.01f;
	worldTransform->UpdateMatrix(cameraData);
	worldTransform2->UpdateMatrix(cameraData);
	worldTransform3->UpdateMatrix(cameraData);
	if (color.w < 0) {
		if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
			gameManager->ChangeState(new StartSeen);

		}
	}
}

void clearScene::Draw()
{
	if (animaionTime <= 2.3) {

		walk3d->Draw({ 1,1,1,1 }, cameraData, worldTransform, skinCluster);

	}
	if (animaionTime <= 2.3) {

		walk3d2->Draw({ 1,1,1,1 }, cameraData, worldTransform2, skinCluster);
	}
	if (animaionTime <= 2.3) {

		walk3d3->Draw({ 1,1,1,1 }, cameraData, worldTransform3, skinCluster);
	}
	//
	if (animaionTime >= 2.3) {

		walk3d->Draw({ 1,1,1,1 }, cameraData, worldTransform, skinClusterSilly);
	}
	if (animaionTime >= 2.3) {

		walk3d2->Draw({ 1,1,1,1 }, cameraData, worldTransform2, skinClusterHipHop);
	}
	if (animaionTime >= 2.3) {

		walk3d3->Draw({ 1,1,1,1 }, cameraData, worldTransform3, skinClusterRumba);
	}

	treeData_->Draw({ 1,1,1,1 }, cameraData, treeWorldTransform_);
	sprite->Draw({ 128,72,0 }, { 0,0,0 }, { 0,0,0 }, {1,1,1,1});
}

void clearScene::ImGui()
{
#ifdef _DEBUG
	ImGui::Begin("Color");
	ImGui::DragFloat4("c", &animaionTime, 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat4("s", &playerPos_.x, 0.1f, -500.0f, 1000.0f);
	ImGui::DragFloat3("p", &cPos.x, 1.0f, -1000.0f, 100.0f);
	
	float flame = ImGui::GetIO().Framerate;
	if (ImGui::TreeNode("System"))
	{


		ImGui::Text("FPS::%f", flame);
		ImGui::TreePop();
	}
	ImGui::End();

#endif // _DEBUG
}
