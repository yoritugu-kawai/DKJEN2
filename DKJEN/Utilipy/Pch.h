#pragma once
#include"../Base/Log.h"
#include"../Math/Math.h"
#include"DKJEN/WorldTransform/WorldTransform.h"


#include<Windows.h>
#include <cstdint>
#include<string>
#include<format>
#include<cassert>
#include<cmath>
#include<numbers>
#include<list>
#include<array>
#include<vector>
#include<fstream>
#include<sstream>
#include<chrono>
#include<random>
#include<map>
#include <span>

#pragma comment(lib,"winmm.lib")


#pragma region DirectX
#include<dxgidebug.h>
#include<dxcapi.h>
#include<wrl.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
#define DIRECTINPUT_VERSION 0x0800
#include<dinput.h>
#include<Xinput.h>
#pragma comment(lib,"xinput.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxcompiler.lib")
#include<xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#pragma endregion

using namespace std;
using namespace std::chrono;
using Microsoft::WRL::ComPtr;


