#pragma once
#include"../Base/DxCommon.h"
#include"../Base/RenderTextrurePSO.h"
#include"../Management/DescriptorManagement.h"
#include"../Utilipy/Pch.h"
class PostEffect
{
public:
	void Initialize();
	void Call();
protected:
     void Create() {
		// SRV作成
		ComPtr<ID3D12Resource> stv =
			RTVManager::GetRTV("PostEffect")->GetRTVPrope().Resources.Get();
		srv_ = SRVManager::CreatePostEffectSRV(stv);

		// バッファー作成
		mtlBuffer_.CreateResource();
	}
private:
	uint32_t srv_;
};